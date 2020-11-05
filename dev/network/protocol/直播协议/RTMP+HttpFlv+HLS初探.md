# 直播协议RTMP/HttpFlv/HLS初探

## 协议介绍

* FLV，即flash video缩写，是Adobe为网络播放视频文件设计的**码流封装格式**
    * flv码流封装在网页端只能由flash播放，HTML5 video控件不支持直接播放

* RTMP，即flv over RTMP，是Adobe为网络传输音视频码流设计的**网络传输协议**

* HTTPFlv，即flv over HTTP，是将FLV格式的码流通过HTTP传输的方法

* HLS，即HTTP Live Streaming，是苹果推出的直播流播放协议
    * 将直播、点播流分割/缓存为文件分片(ts)，并更新m3u8索引
    * 整体延迟为文件分片时长+网络延迟，文件分片时长一般3-10秒

* DASH，与HLS类似，参考[DASH简介及使用方法](https://blog.csdn.net/yue_huang/article/details/78466537)

## 对比
    
|协议|传输方式|封装格式|延迟|数据分段|可用性|
|:--:|:-----:|:-----:|:--:|:-----:|:----:|
|Rtmp|TCP长连接|FLV-TAG|低|流式，不分段|仅支持Flash播放器；容易被墙；跨域兼容不好|
|HttpFlv|HTTP长连接|FLV-TAG|低|流式，不分段|支持Flash播放器,通过flv.js可以支持H5；防火墙穿透好；支持跨域|
|HLS|HTTP短链接|TS文件|高|文件切片|通过hls.js可以支持H5；兼容性好|
|DASH|http|Mp4/3gp/webm|高|文件切片|Mp4/webm可以直接H5播放|
