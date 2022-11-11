## 概述

当前的webrtc项目是由Google收购的GIPS项目和libjingle项目融合而成。其中GIPS部分主要提供媒体的处理的功能。libjingle项目部分主要提供P2P传输部分的功能。项目支持的平台包括windows，linux，mac，android。 不提供对IOS的完整支持。

## 参考

* google webrtc官方资料 http://www.webrtc.org/reference

* W3C工作草案 http://www.w3.org/TR/webrtc/

* W3C作者草案 http://dev.w3.org/2011/webrtc/editor/webrtc.html

* Google chrome上JS示范
    * 常规的呼叫过程
    * data channel的创建
    * file:///D:/read/chrome'webrtc/manual/peerconnection.html

* webrtc4all，扩展程序，使Safari, Firefox, Opera and IE9+支持webrtc
    * https://code.google.com/p/webrtc4all/

## sipml5解决方案

* 功能：
    * 实现浏览器与SIP或者IMS网络的视讯连接
    * 通过webrtc2sip可以使浏览器与PSTN或者SIP-legacy网络视频通讯

* 开源 HTML5-sip clinet 

* JS编写

* media stack基于webrtc

* 包含webrtc2sip, click-to-call and webrtc4all四大组件

* 特色：音视频、多浏览器支持、及时消息、列席、呼叫保持、呼叫转移、多行和多账户、DTMF

* 提供client app、源码和API

* google官方站点：https://code.google.com/p/sipml5/
* Demo站点：http://www.sipml5.org/call.htm?svn=179

## 源码目录

### libjingle

* libjingle：原libjingle项目的一些基础功能类。如线程，队列，消息等。

* libjingle_media：原libjingle项目的媒体相关类。提供了基本的设备管理管理功能以及部分媒体抽象类。其中的webrtc目录为webrtc项目上为了匹配GIPS加入的继承类。这些类用GIPS的相关类实现媒体处理功能并匹配原libjingle接口。

* libjingle_P2P：原libjingle的P2P传输相关类。

* libjingle_peerconneciton：webrtc项目加入的，提供简单的外部接口， 方便使用。

* third_party/webrtc：原GIPS的媒体处理相关功能类。

### webrtc

WebRTC的视频部分，包含采集、编解码(I420/VP8)、加密、媒体文件、图像处理、显示、网络传输与流控(RTP/RTCP)等功能。

* 视频采集---video_capture
    * 源代码在webrtc\modules\video_capture\main目录下，包含接口和各个平台的源代码。
    * 在windows平台上，WebRTC采用的是dshow技术，来实现枚举视频的设备信息和视频数据的采集，这意味着可以大多数的视频采集设备；对那些需要单独驱动程序的视频采集卡（比如海康高清卡）就无能为力了。
    * 视频采集支持多种媒体类型，比如I420、YUY2、RGB、UYUY等，并可以进行帧大小和帧率控制。

* 视频编解码---video_coding
    * 源代码在webrtc\modules\video_coding目录下。
    * WebRTC采用I420/VP8编解码技术。VP8是google收购ON2后的开源实现，并且也用在WebM项目中。VP8能以更少据提供更高质量的视频，特别适合视频会议这样的需求。

* 视频加密--video_engine_encryption
    * 视频加密是WebRTC的video_engine一部分，相当于视频应用层面的功能，给点对点的视频双方提供了数据上全保证，可以防止在Web上视频数据的泄漏。
    * 视频加密在发送端和接收端进行加解密视频数据，密钥由视频双方协商，代价是会影响视频数据处理的性能；以不使用视频加密功能，这样在性能上会好些。
    * 视频加密的数据源可能是原始的数据流，也可能是编码后的数据流。估计是编码后的数据流，这样加密代价会些，需要进一步研究。

* 视频媒体文件--media_file
    * 源代码在webrtc\modules\media_file目录下。
    * 该功能是可以用本地文件作为视频源，有点类似虚拟摄像头的功能；支持的格式有Avi。
    * 另外，WebRTC还可以录制音视频到本地文件，比较实用的功能。

* 视频图像处理--video_processing
    * 源代码在webrtc\modules\video_processing目录下。
    * 视频图像处理针对每一帧的图像进行处理，包括明暗度检测、颜色增强、降噪处理等功能，用来提升视频质量。

* 视频显示--video_render
    * 源代码在webrtc\modules\video_render目录下。
    * 在windows平台，WebRTC采用direct3d9和directdraw的方式来显示视频，只能这样，必须这样。

* 网络传输与流控
    * 对于网络视频来讲，数据的传输与控制是核心价值。WebRTC采用的是成熟的RTP/RTCP技术。

WebRTC的音频部分，包含设备、编解码(iLIBC/iSAC/G722/PCM16/RED/AVT、NetEQ)、加密、声音文件、声音处理、声音输出、音量控制、音视频同步、网络传输与流控(RTP/RTCP)等功能。

* 音频设备---audio_device
    * 源代码在webrtc\modules\audio_device\main目录下，包含接口和各个平台的源代码。
    * 在windows平台上，WebRTC采用的是Windows Core Audio和Windows Wave技术来管理音频设备，还提供了一个混音管理器。
    * 利用音频设备，可以实现声音输出，音量控制等功能。

* 音频编解码---audio_coding
    * 源代码在webrtc\modules\audio_coding目录下。
    * WebRTC采用iLIBC/iSAC/G722/PCM16/RED/AVT编解码技术。
    * WebRTC还提供NetEQ功能---抖动缓冲器及丢包补偿模块，能够提高音质，并把延迟减至最小。
    * 另外一个核心功能是基于语音会议的混音处理。

* 声音加密--voice_engine_encryption
    * 和视频一样，WebRTC也提供声音加密功能。

* 声音文件
    * 该功能是可以用本地文件作为音频源，支持的格式有Pcm和Wav。
    * 同样，WebRTC也可以录制音频到本地文件。

* 声音处理--audio_processing
    * 源代码在webrtc\modules\audio_processing目录下。
    * 声音处理针对音频数据进行处理，包括回声消除(AEC)、AECM、自动增益(AGC)、降噪处理等功能，用来提升声音质量。

* 网络传输与流控
    * 和视频一样，WebRTC采用的是成熟的RTP/RTCP技术。