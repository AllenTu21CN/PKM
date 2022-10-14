[TOC]
 
****
## 1. HIDClass Driver
### 1.1 Operational features of the HIDClass driver
* Provides and manages the upper-level interface that kernel-mode drivers and user-mode applications use to access the HID collections that an input device supports.
    * The HIDClass driver transparently manages and routes all communication between upper-level drivers and applications and the underlying input devices that support HID collections.
    * It manages the different data protocols that are used by different input devices and input queues that support more than one open file on the same HID collection.
    * The upper-level interface to HID collections consists of the `HIDClass driver IOCTLs`, the `HIDClass support routines`, and `the HIDClass structures`.
 
* Communicates with a HID minidriver by calling the minidriver's standard driver routines.
 
* Creates a functional device object (FDO) for HIDClass input devices enumerated by a lower-level bus or port driver. **[I don't know this meaning]**
 
* Provides the functionality of a bus driver for the child devices (HID collections) supported by an underlying input device. **[I don't know this meaning]**
The HIDClass driver creates a physical device object (PDO) for each HID collection supported by an input device and manages the collection's operation.
 
* The HIDClass driver supplies the following standard driver routines:
    * AddDevice and Unload routines
    * Dispatch routines for the following I/O requests:
        IRP_MJ_CREATE
        IRP_MJ_CLOSE
        IRP_MJ_DEVICE_CONTROL
        IRP_MJ_INTERNAL_DEVICE_CONTROL
        IRP_MJ_PNP
        IRP_MJ_SYSTEM_CONTROL
 
### 1.2 With Minidrivers
* Binding a minidriver to HIDClass
Refer to MsHidKmdf code.
* Communicating with a HID minidriver
1. Calling the AddDevice Routine
2. Calling the Unload Routine
3. Calling the Dispatch Routines
To operate a device, the HIDClass driver primarily calls the HID minidriver dispatch routine for **internal device control requests**.
 
In addition, when the I/O manager sends Plug and Play, power, or system control requests to the HIDClass driver for an FDO, the HIDClass driver processes the request, and calls the HID minidriver's corresponding dispatch routine.
 
The HIDClass driver **does not send** the following requests to the HID minidriver: **create, close, or device control(different with internal device control)**.
 
### 1.3 HIDClass External Interfaces
Routines are listed [here](https://msdn.microsoft.com/en-us/library/windows/hardware/ff538865\(v=vs.85\).aspx).
Note:
* User-mode applications can use the `HidD_Xxx` and `HidP_Xxx` routines.
* Kernel-mode drivers can only call `HidP_Xxx` routines.
* HID minidrivers use only the `HidRegisterMinidriver` routine.
 
### 1.4 HIDClass IOCTLs
#### 1.4.1 HIDClass Driver IOCTLs
https://msdn.microsoft.com/en-us/library/windows/hardware/ff539849(v=vs.85).aspx
 
#### 1.4.2 HID Minidriver IOCTLs
https://msdn.microsoft.com/en-us/library/windows/hardware/ff539926(v=vs.85).aspx
 
### 1.5 HIDClass Structures
#### 1.5.1 HIDClass Driver Structures
https://msdn.microsoft.com/en-us/library/windows/hardware/ff539851(v=vs.85).aspx
 
#### 1.5.2 HID Minidriver Structures
https://msdn.microsoft.com/en-us/library/windows/hardware/ff539934(v=vs.85).aspx
 
****
## 2. Creating KMDF HID Minidrivers
[[EN](https://msdn.microsoft.com/en-us/library/windows/hardware/ff540774\(v=vs.85\).aspx)]
 
The HIDClass driver and the framework provide conflicting WDM dispatch routines to handle some I/O requests (such as Plug and Play and power management requests) for minidrivers. As a result, a HID minidriver cannot link to both the class driver and the framework.
 
Therefore, Microsoft provides an additional driver, called MsHidKmdf.sys, that resides between the class driver and the minidriver, as the following diagram shows.
![](https://msdn.microsoft.com/dynimg/IC490921.png)
 
The MsHidKmdf.sys driver calls the HIDClass driver's `HidRegisterMinidriver` routine to register as the actual minidriver.Although MsHidKmdf.sys acts as the device's function driver, it just passes I/O requests from the class driver to your driver (and is thus sometimes called a pass-through driver).
 
The framework-based driver that you supply is actually a filter driver that resides under MsHidKmdf.sys.
 
The WDK provides several sample framework-based HID minidrivers, including the drivers in the \src\hid\hidusbfx2 and \src\hid\vhidmini subdirectories.
 
If you want to provide a framework-based HID minidriver for earlier versions of Windows(before Win7), you can provide a customized version of the MsHidKmdf.sys driver by source code in src\hid\hidusbfx2\hidkmdf subdirectory.