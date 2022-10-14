# Android Broadcast笔记

## 使用场景

* App内部
* App之间
* 系统和App之间

## 原理

* 使用订阅-发布模型；

* 可以收发**解耦合**

* 流程如下：
    1. 广播接收者通过Binder机制向AMS(Activity Manager Service)进行注册；
    2. 广播发送者通过Binder机制向AMS发送广播；
    3. AMS根据广播发送者的要求（IntentFilter/Permission等），在已注册列表中，寻找合适的广播接收者；
    4. AMS将广播发送到合适的广播接收者相应的消息循环队列中；
    5. 广播接收者 通过消息循环拿到此广播，并回调BroadcastReceiver中的onReceive()；

## 广播类型

### 普通广播(NormalBroadcast)

* sendBroadcast
* 常用于自定义广播
* 一种完全**异步执行**的广播，所有的接收器几乎会同时接收到这条广播消息
* 此类广播效率较高而且**不能截断**

### 有序广播(OrderedBroadcast)

* sendOrderedBroadcast
* 一种**同步执行**的广播，接收器按照优先级顺序接收，高优先级的可以选择截断(`abortBroadcast()`)广播，也可以继续传递
* 静态注册时定义优先级
    ```xml
    <receiver 
        android:name=".MBroadcastReceiver" >
        <!-- priority优先级：数越大优先级越高（取值范围：-1000~10000） -->
        <intent-filter android:priority="2">
            <action android:name="BROADCAST_ACTION2" />
        </intent-filter>
        <intent-filter android:priority="1">
            <action android:name="BROADCAST_ACTION1" />
        </intent-filter>
    </receiver>
    ```
* 动态注册是定义优先级
    ```JAVA
    IntentFilter intentFilter = new IntentFilter();
    intentFilter.setAction(BROADCAST_ACTION2);
    intentFilter.setPriority(2);
    registerReceiver(mBroadcastReceiver, intentFilter);
    ```

### 系统广播(SystemBroadcast)

* 发生各种事件时，系统自动发送
* 常用系统广播如下：
    |系统操作|	action|
    |-|-|
    |监听网络变化|	android.net.conn.CONNECTIVITY_CHANGE|
    |关闭或打开飞行模式|	Intent.ACTION_AIRPLANE_MODE_CHANGED|
    |充电时或电量发生变化|	Intent.ACTION_BATTERY_CHANGED|
    |电池电量低|	Intent.ACTION_BATTERY_LOW|
    |电池电量充足（即从电量低变化到饱满时会发出广播|	Intent.ACTION_BATTERY_OKAY|
    |系统启动完成后|(仅广播一次)	Intent.ACTION_BOOT_COMPLETED|
    |按下照相时的拍照按键|(硬件按键)时	Intent.ACTION_CAMERA_BUTTON|
    |屏幕锁屏|	Intent.ACTION_CLOSE_SYSTEM_DIALOGS|
    |设备当前设置被改变时|(界面语言、设备方向等)	Intent.ACTION_CONFIGURATION_CHANGED|
    |插入耳机时|	Intent.ACTION_HEADSET_PLUG|
    |未正确移除SD卡但已取出来时|(正确移除方法:设置--SD卡和设备内存--卸载SD卡)	Intent.||ACTION_MEDIA_BAD_REMOVAL||
    |插入外部储存装置（如SD卡）|	Intent.ACTION_MEDIA_CHECKING|
    |成功安装APK|	Intent.ACTION_PACKAGE_ADDED|
    |成功删除APK|	Intent.ACTION_PACKAGE_REMOVED|
    |重启设备|	Intent.ACTION_REBOOT|
    |屏幕被关闭|	Intent.ACTION_SCREEN_OFF|
    |屏幕被打开|	Intent.ACTION_SCREEN_ON|
    |关闭系统时|	Intent.ACTION_SHUTDOWN|
    |重启设备|	Intent.ACTION_REBOOT|

### 本地广播(LocalBroadcast)

* LocalBroadcastManager.sendBroadcast
* 为了避免第三方APP恶意发送广播或窃听广播，出现了本地广播，用于应用内广播通讯
* 更高效、更高全
* Android v4兼容包中给出了封装好的LocalBroadcastManager类，用于统一处理App应用内的广播；
* LocalBroadcastManager方式发送的应用内广播，只能通过LocalBroadcastManager动态注册，不能静态注册

```JAVA
//registerReceiver(mBroadcastReceiver, intentFilter);
//注册应用内广播接收器
localBroadcastManager = LocalBroadcastManager.getInstance(this);
localBroadcastManager.registerReceiver(mBroadcastReceiver, intentFilter);

//unregisterReceiver(mBroadcastReceiver);
//取消注册应用内广播接收器
localBroadcastManager.unregisterReceiver(mBroadcastReceiver);

Intent intent = new Intent();
intent.setAction(BROADCAST_ACTION);
//sendBroadcast(intent);
//发送应用内广播
localBroadcastManager.sendBroadcast(intent);
```

### 粘性广播(StickyBroadcast)

* 已弃用(API 21)(android 5.0)

## 广播接收注册

### 静态注册

* 在AndroidManifest.xml里通过<receive>标签声明
* 当此App首次启动时，系统会自动实例化指定的Receiver类，并注册到系统中

```xml
<receiver 
    <!-- 系统是否自动实例化,默认为true(同时受application的enable属性影响) -->
    android:enabled="true" 

    <!-- 这个属性用于指示该广播接收器是否能够接收来自应用程序外部的消息 -->
    <!-- 如果为false,则表示只接收应用内或用户ID相同的应用发送的广播 -->
    android:exported="true"

    <!-- 广播接收器的图标 -->
    android:icon="drawable resource"

    <!-- 用户可读的懂的文本标签 -->
    <!-- 如果没有设置，会使用application元素的label属性 -->
    android:label="string resource"

    <!-- 广播接收器的实现类的类名 -->
    android:name=".MBroadcastReceiver"

    <!-- 定义把消息发送给该广播接收器的广播器所必须要有的权限。 -->
    android:permission="string"

    <!-- 设置该广播接收器运行的进程名 -->
    <!-- 通常，它与应用程序包名相同的名称 -->
    android:process="string" >

    <!-- 用于接收网络状态改变时发出的广播 -->
    <intent-filter>
          <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
    </intent-filter>
</receiver>
```

### 动态注册

* 接在代码中调用registerReceiver()方法

```JAVA
public class MainActivity extends AppCompatActivity {

    private IntentFilter intentFilter;
    private MBroadcastReceiver mBroadcastReceiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        ...

        // 注册广播
        intentFilter = new IntentFilter();
        intentFilter.addAction("android.net.conn.CONNECTIVITY_CHANGE");
        myBroadcastReceiver = new MBroadcastReceiver();
        registerReceiver(myBroadcastReceiver, intentFilter);
        
        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 发送广播
                Intent intent = new Intent("android.net.conn.CONNECTIVITY_CHANGE");
                sendBroadcast(intent); 
            }
        });
    }

    @Override
    protected void onDestroy() {
        ...

        // 注销广播
        unregisterReceiver(mBroadcastReceiver);
    }
}
```

## 自定义广播权限

### 定义广播

在AndroidManifest.xml中，声明一个权限，名为com.example.receiver.receivebroadcast：

```xml
<permission
       android:name="com.example.receiver.receivebroadcast"
       android:label="权限标签名"
       android:description="权限详细描述"
       android:protectionLevel="signature">
       <!-- protectionLevel： -->
       <!-- normal：默认的，应用安装前，用户可以看到相应的权限，无需用户主动授权 -->
       <!-- dangerous：明确要求用户进行授权。如：网络使用权限，相机使用权限等。 -->
       <!-- signature：要求权限声明应用和权限使用应用使用相同的keystore进行签名；相同时由系统授予权限，且不会通知用户。常用于应用内部 -->
</permission>

<!--声明要使用的权限-->
<users-permission android:name="com.example.receiver.receivebroadcast"/>
```

### 使用广播

* 静态接收

在接收方的AndroidManifest.xml中，声明一个权限

```xml
<receiver
       android:name=".MBroadcastReceiver"
       android:exported="false"
       android:permission="com.example.receiver.receivebroadcast">
       <intent-filter>
            <action android:name="BROADCAST_ACTION"/>
       </intent-filter>
</receiver>
```

* 动态接收

```JAVA
// 注册广播代码
MBroadcastReceiver receiver = new MBroadcastReceiver ();
IntentFilter intentFilter = new IntentFilter();
intentFilter.addAction(BROADCAST_ACTION);
//注册receiver时，直接指定发送者应该具有的权限。不然外部应用依旧可以触及到receiver
registerReceiver(receiver, intentFilter, "com.example.receiver.receivebroadcast", null);
```

* 发送

```JAVA
// 发送广播代码
Intent intent = new Intent();
intent.setAction(BROADCAST_ACTION);
// 可以限制接收者的包名
intent.setPackage(packageName);
sendBroadcast(intent, "com.example.receiver.receivebroadcast");
```
