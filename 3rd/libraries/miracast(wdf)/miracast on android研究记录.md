## 目标

* 在RK3399和qc820上能够实现投屏，并集成到现有教学应用中

## 记录

### 2021.6.29

* 了解目前Android机顶盒硬件和QC820的投屏现状

    * AMLogic(S905X2/ ？、Android 9)
        * 自带被投屏APK启动后，手机、win10都能投屏成功；
        * 有固件、apk源码
        * 源码中有Qcom qca6174无线网卡的驱动

    * Rockchips(RK3399/AP6356S ，Android 7)
        * 自带被投屏APK启动后，手机、win10都能投屏成功；
        * 有固件源码；apk源码尚未知道 [这个?](https://gitlab.com/TeeFirefly/firenow-oreo-rk3399/-/tree/master/vendor/rockchip/common/apps/WifiDisplay)

    * Allwinner(？/？、Android 10)
        * 自带被投屏APK启动后，手机、win10都能投屏成功；

    * Qcom(QC820/qca6174 ，Android 8)
        * 运行RK的被投APK，手机、win10能够搜索成功，但连接和投屏失败
        * wpa_supplicant初始化和链接报错

* 查看amlogic的被投屏apk源码，确认其整体方案
    * 通过SDK（WifiP2pManager/WifiP2pDevice/WifiP2pInfo/WifiP2pWfdInfo）完成搜索和建立P2P连接（该SDK部分为hidden，需要依赖固件编译）
    * 通过jni调用wfdSink（为2012年时的aosp源码，后被移除，amlogic引入该部分代码），实现RTSP相关的协商和码流传输

* 计划1：大致了解wpa_supplicant内部逻辑和使用流程

* 计划2：使用amlogic的wpa_supplicant替代Qcom中的wpa，有必要再将amlogic中qca6174驱动编译后替换qcom，尝试是否能够解决投屏连接问题

### 2021.6.30

* Qcom (QC820/qca6174 ，Android 8)
    * 由于测试硬件没有安装WIFI天线，所以信号不稳，导致连接容易失败，重新测试后：
    * 使用RK Android 7上的apk测试，能够连接成功
    * 使用RK Android 8上的apk，再手动push wfd jni动态库后，能够投屏成功

* 由于RK apk在QC820上试用成功，证明wpa及以下没有问题，故**放弃计划1和2**

* 继续深入学习amlogic apk 源码，寻找获取投屏码流的切入口
    * 似乎在jni层直接创建了surface，解码并显示，暂未明白如何获取码流
    * **暂停深入**，不确定该apk能否能迁移到820，所以参考价值不确定

* 因为rk apk能够在820上直接运行，所以尝试获取rk wfd的源码，用于对照实际流程和日志
    * 未找到源码，尝试反编译apk，获取到不完善的源码
    * 且未找到rk wfd sink 动态库的源码，未知是否修改了aosp7.0中的sink
    * **暂停深入**

* 计划：将amlogic apk移植到QC820上，统一代码和可执行物

### 2021.7.1

* 邮件给苏总，求助rk miracast apk和lib源码
    * 暂无答复

* 尝试将amlogic的源码移植到QC820上

    * 对比amlogic的wfd-source和aosp，发现其基于8.0修改

    * 在固件里编译并把so放入固件 vs 提取出源码单独编译并放入apk？
        * amlogic apk本身不包含任何库，依赖固件中库：
            * /system/lib/libstagefright.so 包含wdf基础功能（source等）
            * /system/lib/libstagefright_wfd_sink.so wdf的sink功能
            * /product/lib/libwfd_jni.so apk的jni库，wfd功能的组织、解码显示等
        * rk apk本身也不包含任何库
            * android 7版
                * 反编译apk中未见任何动态库加载，只看通过设置系统属性启动wfd sink，猜测：
                * 固件中包含了wfd sink的功能和应用封装，通过系统属性通讯
            * android 8版
                * /system/lib/libstagefright_wfd.so 包含了wfd基础、source功能 
                * libwfdsink_jni.so apk的jni库和sink实现，应该在/system/lib/下
        * allwinner apk自带 wfd rtsp、player、manager、jni库
            * 似乎自己实现了wfd sink等

    * 调研了android4.2、github上3个实现、amlogic的sink，发现改动相差比较大，而且代码结构比较乱，且以来一堆native的代码，后续维护不方便，所以**暂停**将android wfd sink移植到QC820上

* 大胆猜测，P2P连接已经建立完成，wfd sink仅rtsp协商、连接、传输码流的工作，相对独立，故打算使用intel的wds项目来完成该部分
    * 大致了解wds项目代码结构，理论上仅使用libwds即可，仅包含sink session相关的解析和状态机，不包含具体的网络传输、编解码、线程模型等。
    * 根据sink-test示例，深入理解libwds

### 2021.7.2

* 继续libwds的深入理解

* 编写sink-test2：基于libwds和avalon-network，实现rtsp协商和码流传输
    * 开发完成、初步联通，但仍有bug，未完成

### 2021.7.3-4

* 解决码流接收的bug，能够通过miracast sink apk + wds sink2接收到码流
    * rtsp play自动触发，但是没有自动调用SinkMediaManager.play方法,需要手动调用，封装时调整逻辑

### 2021.7.27

* 恢复记忆和工作环境

* 尝试解码TS over RTP视频码流
    * ffmpeg 命令行转存为mp4文件，播放成功
    * 且发现音频、视频数据都在同一个端口中，声音正常

* 发现win10投屏失败，P2P建立连接成功率很低、RTSP协商失败

### 2021.7.28

* 在rk上运行wds sink-test2，以暂时规避P2P建立失败的问题

* 继续定位RTSP协商失败的问题
    * 通过测试，发现wds对win10的rtsp setup reply 不兼容，尝试修改yacc脚本

### 2021.7.29

* 修改wds源码，解决win10投屏时，rtsp setup reply 不兼容的问题

* 切换回VT6105环境，定位P2P建立连接失败的问题
    * 开机后第一次投屏成功，之后每次触发总是失败，仅当超时重连时才能成功

### 2021.8.23

* miracast连接邀请确认对话框
    * 目前每次收到邀请时弹出确认对话框，代码无法控制应答
    * 对话框样式和测试APP主题不一致，且APP代码中无弹出对话框的逻辑，所以猜测为系统服务弹出
    * 查看framework源码发现如下通路：
        [wpa_supplicant]
        wpas_go_neg_req_rx -> wpas_notify_p2p_go_neg_req -> wpas_hidl_notify_p2p_go_neg_req ->
        HidlManager.notifyP2pGoNegReq
        ---> 
        [WifiP2pService]
        SupplicantP2pIfaceCallback.onGoNegotiationRequest ->
        WifiP2pMonitor.broadcastP2pGoNegotiationRequest -> 
        WifiP2pServiceImpl.transitionTo(mUserAuthorizingNegotiationRequestState) -> notifyInvitationReceived() -> AlertDialog
    * 相关源码：
        * external/wpa_supplicant_8/wpa_supplicant
            * p2p_supplicant.c
            * notify.c
            * hidl/1.0/hidl.cpp
            * hidl/1.0/hidl_manager.cpp
        * frameworks/opt/net/wifi/service/java/com/android/server/wifi/p2p/
            * WifiP2pServiceImpl.java
            * WifiP2pMonitor.java
            * SupplicantP2pIfaceCallback.java
    * 修改方案TODO
