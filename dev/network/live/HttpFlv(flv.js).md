
<!-- TOC -->

- [简介](#%E7%AE%80%E4%BB%8B)
- [FLV文件格式](#flv%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F)
    - [整体格式](#%E6%95%B4%E4%BD%93%E6%A0%BC%E5%BC%8F)
    - [FLV Tag](#flv-tag)
    - [Audio Tag](#audio-tag)
    - [Video Tag](#video-tag)
    - [Script Tag](#script-tag)
- [参考项目](#%E5%8F%82%E8%80%83%E9%A1%B9%E7%9B%AE)
- [flv.js已知问题](#flvjs%E5%B7%B2%E7%9F%A5%E9%97%AE%E9%A2%98)

<!-- /TOC -->

## 1. 简介

* HTTP协议中有个约定：content-length字段，http的body部分的长度
    * 服务器回复http请求的时候如果有这个字段，客户端就接收这个长度的数据然后就认为数据传输完成了，
    * 如果服务器回复http请求中没有这个字段，客户端就一直接收数据，直到服务器跟客户端的socket连接断开。

* SRS 2.0和Nginx都支持RTMP推流，HttpFLV拉流

## 2. FLV文件格式

[参考1](https://www.cnblogs.com/leisure_chn/p/10662941.html)
[参考2](https://zhuanlan.zhihu.com/p/28722048)

### 2.1 整体格式

```
flv
├── header
│  ├── Signature            // byte[3],固定为"FLV"
│  ├── Version              // uint8,固定为1
│  ├── TypeFlags            // uint8 bitmask,0x01=video,0x04=audio, 0x05=audio+video
│  └── HeaderSize           // uint32,对于v1,固定为9
└── body
    ├── PreviousTagSize0    // uint32,总是为0
    ├── Tag1
    ├── PreviousTagSize1    // 为tag1的字节数 = Tag1.DataSize + 11
    ├── Tag2
    ├── PreviousTagSize2
    ├── ...
    ├── TagN
    └── PreviousTagSizeN
```

### 2.2 FLV Tag

```
tag
├── common header
│   ├── Reserved            // bit[2]，保留给FMS，固定为0
│   ├── Filter              // bit[1]，指示packet是否需要预处理：0-不处理 1-加密的
│   ├── TagType             // bit[5]，0x08=audio，0x09=video，0x12=script data
│   ├── DataSize            // uint24，为payload data的长度 = Tag1长度 - 11
│   ├── TimestampLower      // uint24，相对于第一个TAG的解码时间戳(ms)的低24位
│   ├── TimestampUpper      // uint8，上述时间戳的高8位
│   └── StreamID            // uint24，总是0
└── data tag                // 变长，即为payload，Audio/Video/ScriptTag
    ├── header
    └── body
```

另说明：

* 音频DTS和PTS相同
* 对视频帧来说，若含B帧，则PTS和DTS不同，H264视频帧PTS = DTS + CTS，CTS 就是 CompositionTime 字段（后叙）

### 2.3 Audio Tag

```
audio-tag
├── header
│   ├── SoundFormat           // bit[4]，音频格式索引，具体如下
│   ├── SoundRate             // bit[2]，采样率索引，0 = 5.5 kHz；1 = 11 kHz；2 = 22 kHz；3 = 44 kHz；
│   ├── SoundSize             // bit[1]，采样位宽索引，0 = 8位；1 = 16位（一般仅适用未压缩格式，压缩格式总在内部被解码为16位）
│   ├── SoundType             // bit[1]，声道数索引，0 = 单声道；1 = 立体声
│   └── [AACPacketType]       // uint8，if SoundFormat == 10；AAC帧类型：0 = AAC sequence header；1 = AAC raw
└── body
    ├── [AudioSpecificConfig] // if SoundFormat == 10 && AACPacketType == 0，参考ISO 14496-3
    ├── [RawAACFrame]         // if SoundFormat == 10 && AACPacketType == 1
    └── [OtherFrame]          // if SoundFormat != 10
```

* 暂不考虑tag加密的情况
* 主要以AAC为例
* SoundFormat:
    ```
    常用：
    0 = Linear PCM, platform endian
    2 = MP3
    3 = Linear PCM, little endian
    10 = AAC
    11 = Speex
    不常用：
    1 = ADPCM
    4 = Nellymoser 16-kHz mono
    5 = Nellymoser 8-kHz mono
    6 = Nellymoser
    保留的：
    7 = G.711 A-law logarithmic PCM
    8 = G.711 mu-law logarithmic PCM 
    9 = reserved
    14 = MP3 8-Khz
    15 = Device-specific sound
    ```

### 2.4 Video Tag

```
video-tag
├── header
│   ├── FrameType                       // bit[4]，帧类型，1=关键帧，2=内部帧，其他如下
│   ├── CodecID                         // bit[4]，编解码器标识，7=AVC/H.264，其他如下
│   ├── [AVCPacketType]                 // uint8，if CodecID == 7，0=AVC sequence header；1=AVC NALU；2=AVC end of sequence 
│   └── [CompositionTime]               // uint24，if CodecID == 7，CTS，PTS与DTS的时间偏移值(ms)。参考 "ISO 14496-12, 8.15.3"
└── body
    ├── [AVCDecoderConfigurationRecord] // if CodecID == 7 && AVCPacketType == 0，参考 ISO 14496-15中5.2.4.1
    ├── [AVC NALUs]                     // if CodecID == 7 && AVCPacketType == 1，One or more NALUs
    └── [OtherCodecData]                // if CodecID != 7
```

* 暂不考虑tag加密的情况
* 主要以H.264为例，其他类型参见参考连接和SWF文件格式规范
* FrameType：
    ```
    1: keyframe (for AVC, a seekable frame)
    2: inter frame (for AVC, a non-seekable frame)
    3: disposable inter frame (H.263 only)
    4: generated keyframe (reserved for server use only)
    5: video info/command frame
    ```
* CodecID：
    ```
    1: JPEG (currently unused)
    2: Sorenson H.263
    3: Screen video
    4: On2 VP6
    5: On2 VP6 with alpha channel
    6: Screen video version 2
    7: AVC
    ```

### 2.5 Script Tag

* 暂不考虑tag加密的情况
* 略

## 3. 参考项目

* [http-flv](https://github.com/saysmy/http-flv)

## 4. flv.js已知问题

* 播放一段时间后，音视频不同步
* 播放一段时间后，音频模糊
    * 上述两个问题，解决方案：尝试设置 config.fixAudioTimestampGap = false；但控制台将不会输出大量警告信息。经检测，不同的推流客户端，会导致音视频同步问题有不一样的体现。
    * 分别用flvjs的master分支、#136、#354进行10分钟到2小时的测试，总结一下结论：
        * master分支、issue 136 都会出现不同程度主播音画不同步的情况，master分支音画不同步情况尤其严重。
        * #354 pr 可以正常播放所有主播的音视频，均同步。
        * 腾讯云TCPlayerLite和Web 直播播放器 1.0均使用flvjs库进行以html5方式播放flv（猜测使用master分支），经测试也是出现大面积音画不同步现象。

* 暂停后继续播放是接着暂停时的场景继续播，对于直播会产生延迟
    * 临时解决方案：暂停后继续播放时，手动销毁视频再重新加载播放

* 手机端兼容性差
    * 是否支持点播视频：flvjs.getFeatureList().mseFlvPlayback
    * 是否支持httpflv直播流：flvjs.getFeatureList().mseLiveFlvPlayback 
    * 目前测试结果：
        * ios ：均不支持，包括微信和safari
        * 安卓：微信均不支持；其他浏览器部分支持点播，全部不支持直播