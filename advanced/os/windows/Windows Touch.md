[TOC]
 
****
### Resource
  [Programming Guide](https://msdn.microsoft.com/en-us/library/windows/desktop/dd317323\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd317323\(v=vs.85\).aspx)
 
****
### 1. Glossary
[DOC [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/ee236506\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/ee236506\(v=vs.85\).aspx)]
 
  `multitouch`: A real-time, physical action applied to an object on a screen in which multiple contact points are used simultaneously.
  `gesture`: A movement of a pen or fingers on a screen, which the computer interprets as a command.
  `application gesture`: A gesture that a particular application supports.
  `system gesture`: A pen equivalent of a traditional mouse message, such as left-click or double-click.
  `manipulation`: A physical action, such as rotation, applied to an object.
  `digitizer`: A high-resolution hardware device that recognizes input from a pen or fingers.
 
****
### 2. About Windows Touch
[DOC:[EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd371406\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd371406\(v=vs.85\).aspx)]
 
* Message [WM_TOUCH](https://msdn.microsoft.com/en-us/library/windows/desktop/dd317341\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd317341\(v=vs.85\).aspx))
It reports the action (up, down, move), position, and an identifier for touch points.
 
* Message [WM_GESTURE](https://msdn.microsoft.com/en-us/library/windows/desktop/dd353242\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd353242\(v=vs.85\).aspx))
It supports for gestures.
 
* API [IManipulationProcessor](https://msdn.microsoft.com/en-us/library/windows/desktop/dd372579\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd372579\(v=vs.85\).aspx)) and `IInertiaProcessor`.
These added Windows SDK interfaces enable advanced support for touch input so that application developers can easily create natural user interfaces. It interprets `WM_TOUCH` messages to raise events that contain translation, rotation, and scale information about a collection of touch points.
 
* Windows SDK APIs are similar but different with Surface SDK so that the applications targeting oneself do not run well on another one.
 
****
### 3. Architectural Overview
[DOC:[EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd371413\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd371413\(v=vs.85\).aspx)]
 
#### 3.1 Windows Touch & Gestures Message
![](https://msdn.microsoft.com/dynimg/IC504519.png)
 
* Applications receive **gestures by default**. If applications want to receive `WM_TOUCH` messages, they should register for Windows Touch input messages with the [RegisterTouchWindow](https://msdn.microsoft.com/en-us/library/windows/desktop/gg132828\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/gg132828\(v=vs.85\).aspx)) function.
 
* Windows Touch and gesture messages are **greedy** in the sense that after a touch is made or a gesture begins on an application Window, all messages are sent to that application until the gesture completes or the primary touch is completed. (I think it means all touch messages are sent to that window until another window receives focus, after the first touch message is received on a window.)
 
* For **legacy** support, by using [DefWindowProc](http://go.microsoft.com/fwlink/p/?linkid=136637)([CN](http://go.microsoft.com/fwlink/?LinkId=136637)), if `WM_GESTURE` messages are bubbled up, Windows will interpret them and then will SEND or POST appropriate messages that map to the gesture. More information on legacy support refers to [Windows Touch Gestures Overview](https://msdn.microsoft.com/en-us/library/windows/desktop/dd940543\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd940543\(v=vs.85\).aspx)).
 
#### 3.2 Manipulations
* manipulation API: Microsoft provides the APIs to perform the calculations to interpret gestures messages from multiple sources (to associated events) while the gesture taking place.
* manipulation processor: After you connect the input data to the manipulation processor, you can retrieve information pertinent to action that the user makes on the object.
 
![](https://msdn.microsoft.com/dynimg/IC504514.png)
* user touch screen -> driver create touch messages(x,y) -> application find/create the focused object with information in the message -> it has associated manipulation processor -> processor start to be referenced with `WM_TOUCH(TOUCHEVENTF_UP)` message -> subsequent `WM_TOUCH` messages will be sent to processor -> processor raise manipulation events -> processor end be referenced with `WM_TOUCH(TOUCHEVENTF_UP)` message.
* Application needs to implement `_IManipulationEvents` interfaces (named `event sink`) to handle the manipulation evnets raised by processor.
 
#### 3.3 Inertia
* Inertia:  it's common to incorporate simple physics so that objects smoothly come to a stop, rather than abruptly stop when they are no longer being touched.
* Application can perform the calculations for these simple physics by self and alse can use Windows Inertia APIs to do these.
![](https://msdn.microsoft.com/dynimg/IC286535.png)
* (I don't think more about these meaning)Subsequent `WM_TOUCH` messages are sent to the manipulation processor and the manipulation processor performs updates to the application UI. After the manipulation completes, velocity values from the manipulation are used to set up an inertia processor. As illustrated in the middle column, the Process or ProcessTime method is called on the IInertiaProcessor interface using a timer or other loop in a separate thread until the calls indicate the processor is finished processing. While these calls are made, manipulation events are raised, which are handled by a manipulation event sink based on the _IManipulationEvents interface. At the bottom right section of the illustration, this event sink then performs updates to the application UI based on manipulation events when they occur through event handlers in the event sink.
 
****
### 4. Getting Started with Four Ways
[DOC:[EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd562100\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd562100\(v=vs.85\).aspx)]
 
#### 4.1 You want your application to behave as it did in legacy versions of Windows
*omit*
 
#### 4.2 You want custom object rotation, translation, panning, or zoom support
*omit*
 
#### 4.3 You want fine-grained gesture interpretation or custom handling of multiple touch points
1. fine-grained interpretation for gestures
Use `manipulation processor` and `inertia processor` (if you want simple object physics)
2. interpret multiple touch points
Application should create a message handler for the `WM_TOUCH` message. Please refer to section 6,7 and [[Manipulations and Inertia](https://msdn.microsoft.com/en-us/library/windows/desktop/dd317309\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd317309\(v=vs.85\).aspx))](How to enable the most flexible approach to Windows Touch.)
 
#### 4.4 You want to enable Windows Touch input to an application that uses the RealTimeStylus(TabletPC)
* If you want to enable input for multiple contacts on the Tablet PC platform, you must implement a custom RealTimeStylus plug-in that interprets the Windows Touch data.
* You use [ITablet3](https://msdn.microsoft.com/en-us/library/windows/desktop/dd373001\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd373001\(v=vs.85\).aspx)) and [IRealTimeStylus3](https://msdn.microsoft.com/en-us/library/windows/desktop/dd372995\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd372995\(v=vs.85\).aspx)) interfaces in the RealTimeStylus plug-in. These interfaces simplify extending RealTimeStylus plug-ins to support multiple contact points.
* [IsMultiTouch](https://msdn.microsoft.com/en-us/library/windows/desktop/dd373002\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd373002\(v=vs.85\).aspx)): Check whether support for multiple contacts.
* [GetMaximumCursors](https://msdn.microsoft.com/en-us/library/windows/desktop/dd464657\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd464657\(v=vs.85\).aspx)): Check the number of supported contacts.
* [MultiTouchEnabled](https://msdn.microsoft.com/en-us/library/windows/desktop/dd372996\(v=vs.85\).aspx)([CN](https://msdn.microsoft.com/zh-cn/library/dd372996\(v=vs.85\).aspx)): Enable or disable multiple contact support.
* If you don't enable multiple contact points in the RealTimeStylus, you will receive gesture messages such as pan and zoom.
 
****
### 5. Troubleshooting Applications
[DOC: [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd693088\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd693088\(v=vs.85\).aspx)]
* General Troubleshooting
    * Issue: Windows Touch features are not working on Windows Server 2008.
    * Issue: Can't discern between mouse input and Windows Touch input.
* Troubleshooting Manipulations and Inertia
    * My application is freezing for no reason. I'm getting access violations when I initialize my object interfaces.
* Troubleshooting Windows Touch Input
    * After I handle the `WM_TOUCH` message, I stop getting boundary feedback.
    * I am including windows.h, but it still says that `WM_TOUCH` is not defined.
    * My touch input x-coordinates and y-coordinates seem invalid. They are either larger values than I expect or they are negative values.
 
****
### 6. Getting Started with Windows Touch Messages
[DOC: [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd371581\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd371581\(v=vs.85\).aspx)]
The following steps are typically performed when working with Windows Touch messages.
#### 6.1 Testing the Capabilities of the Input Digitizer
* Use [GetSystemMetrics](http://go.microsoft.com/fwlink/p/?linkid=132199) to query the capabilities of the input digitizer by passing in the nIndex value with `SM_DIGITIZER`, and it returns a bitmask. The following table shows the bits for the various fields.
|8|6|5|4|3|1|
|-|-|-|-|-|-|
|Stack Ready|Multi-input|Reserved|Reserved|External Pen|Integrated Pen|External Touch|Integrated Touch|
**Note: There are some inherent limitations for `GetSystemMetrics`. For example, there is no support for plug and play.**
 
#### 6.2 Registering to Receive Windows Touch Input
* After the application registers its window, notifications from the Windows Touch driver are forwarded to the application when input is made on the window.
* When the application shuts down, it unregisters its window to disable notifications.
* `WM_TOUCH` messages are currently **greedy**.
```
RegisterTouchWindow(hWnd, 0);
```
 
#### 6.3 Handling Windows Touch Messages
1. With `WndProc`.
```
LRESULT OnTouch(HWND hWnd, WPARAM wParam, LPARAM lParam ){
    ...
}
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ...
    switch (message)
    {
      // pass touch messages to the touch handler
      case WM_TOUCH:
        OnTouch(hWnd, wParam, lParam);
        break;
      ...
    }
    ...
}
```
 
2. For MFC.
```
  // Message Handler
  LRESULT TestDlg::OnTouch(WPARAM wParam, LPARAM lParam ){
    ...
    MessageBox(L"touch!", L"touch!", MB_OK);
    return 0;
  }
 
  // Message Map
  BEGIN_MESSAGE_MAP()
    ... ... ...
    ON_MESSAGE(WM_TOUCH, OnTouch)
  END_MESSAGE_MAP() 
 
  // Register Touch Message
  BOOL TestDlg::OnInitDialog()
  {
    CDialog::OnInitDialog();
    RegisterTouchWindow(m_hWnd, 0);
    ... ... ...
  }
```
 
****
### 7. Detecting and Tracking Multiple Touch Points
[DOC: [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd744775\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd744775\(v=vs.85\).aspx)]
From this section,you can know how to track multiple touch points using Windows Touch and draw them.
*omit*
 
****
### 8. Samples
[DOC: [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd562199\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd562199\(v=vs.85\).aspx)]
 
* [Manipulation and Inertia Sample](https://msdn.microsoft.com/en-us/library/windows/desktop/dd562174\(v=vs.85\).aspx) ([CN](https://msdn.microsoft.com/zh-cn/library/dd562174\(v=vs.85\).aspx))
* ~~Touch Gesture Sample (MTGestures)~~
* ~~Touch Gestures in C# Sample (MTGesturesCS)~~
* [Touch Manipulation Sample (MTManipulation)](https://msdn.microsoft.com/en-us/library/windows/desktop/dd940545\(v=vs.85\).aspx) ([CN](https://msdn.microsoft.com/zh-cn/library/dd940545\(v=vs.85\).aspx))
* [Touch Scratchpad Sample (MTScratchpadWMTouch)](https://msdn.microsoft.com/en-us/library/windows/desktop/dd940547\(v=vs.85\).aspx) ([CN](https://msdn.microsoft.com/zh-cn/library/dd940547\(v=vs.85\).aspx))
* ~~Touch Scratchpad Sample in C# (MTScratchpadWMTouchCS)~~
* [Touch Scratchpad using the Real-time Stylus Sample (MTScratchpadRTStylus)](https://msdn.microsoft.com/en-us/library/windows/desktop/dd940549\(v=vs.85\).aspx) ([CN](https://msdn.microsoft.com/zh-cn/library/dd940549\(v=vs.85\).aspx))
* ~~Touch Scratchpad using the Real-time Stylus in C# Sample (MTScratchpadRTStylusCS)~~
 
****
### 9. Programming Reference
[DOC: [EN](https://msdn.microsoft.com/en-us/library/windows/desktop/dd562198\(v=vs.85\).aspx) [CN](https://msdn.microsoft.com/zh-cn/library/dd562198\(v=vs.85\).aspx)]