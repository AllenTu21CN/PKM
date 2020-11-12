## 1. 介绍

* OBS(Open Broadcaster Software)；
* 实现桌面窗口、游戏、网页、RTMP流、图像等的录制直播；
* 完全开源，任意使用
* OBS Studio是当前正在维护的版本，采用微内核+插件的形式（老版本叫做OBS Classic）
* OBS Studio本身内置了一些常用的插件，如窗口捕获、视频捕获设备、文本、图像、媒体源等，以动态库形式提供，可见OBS安装目录中的obs-plugins
 
## 2. 编译

* 参考[官方文档](https://github.com/jp9000/obs-studio/wiki/Install-Instructions)

## 3. 代码结构

* obs (OBS UI)
* plugins (OBS core plugins)
    * win-capture
        * duplicator-/monitor-capture.c **显示器**源的捕获
        * window-capture.c **窗口**源的捕获
        * game-capture.c **游戏模式**的捕获
    * image-source 
        * image-source.c 使用**图片**作为源
        * obs-slideshow.c **幻灯片**模式
    * obs-ffmpeg 使用ffmpeg解码的**媒体文件**作为源
    * win-dshow 使用**视频输入设备**作为源
    * text-freetype2 使用**文本**作为源
    * win-wasapi **音频输入输出设备**
* libobs (OBS core)
    * obs.h (everything, UI, and modules)
    * obs-module.h (creating modules/plugins)
    * obs-source.h (creating sources)
    * obs-output.h (creating outputs)
    * obs-encoder.h (creating encoders)
    * obs-service.h (creating services)
    * graphics/graphics.h (graphics API)

## 4. 代码阅读

* 源类型
monitor_capture 显示器捕获
window_capture 窗口捕获
text_ft2_source 文本 (FreeType 2)
ffmpeg_source   媒体源
browser_source BrowserSource    * -- 外挂的,在core和plugins中没有发现 *
image_source 图像
slideshow 图像幻灯片放映
dshow_input 视频捕获设备
game_capture 游戏捕获
wasapi_input_capture 音频输入捕获
wasapi_output_capture 音频输出捕获