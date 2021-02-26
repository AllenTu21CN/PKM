
* 更多参考`--help`和[说明](http://blog.csdn.net/thomashtq/article/details/44940457)

* 参数说明

```
# 主要参数：
-i              # 设定输入流
-f              # 设定输出格式
-ss             # 开始时间
-formats        # 查看所有支持的容器格式
-codecs         # 查看所有编解码器
-filters        # 查看所有可用的filter
-pix_fmts       # 查看所有支持的图片格式
-sample_fmts    # 查看所有支持的像素格式
-i input_file   # 查看媒体文件input_file的信息（注意后面不再接其它参数，例如: ffmpeg -i test.mp4，查看 test.mp4视频信息）

# 视频参数：
-b              # 设定视频流量，默认为200Kbit/s
-r              # 设定帧速率，默认为25
-s              # 设定画面的宽与高
-aspect         # 设定画面的比例
-vn             # 不处理视频
-vcodec         # 设定视频编解码器，未设定时则使用与输入流相同的编解码器
-vf             # 旋转视频

# 音频参数：
-ar             # 设定采样率
-ac             # 设定声音的Channel数
-acodec         # 设定声音编解码器，未设定时则使用与输入流相同的编解码器
-an             # 不处理音频
```

* 示例

```
# 输入换成yuv
./ffmpeg -i ~/test/speed1.png  -pix_fmt yuv420p ~/test/speed1.yuv
./ffmpeg -i input_file -vcodec rawvideo -an output_file_yuv  

# yuv转h264
./ffmpeg -s 1920x1080 -pix_fmt yuv420p -i ~/test/test.yuv -an -vcodec libx264 -b:v 10000k -r 1 -s 1920x1080 ~/test/test.h264

# YUV序列转出AVI文件
./ffmpeg -s w*h -pix_fmt yuv420p -i input.yuv -vcodec mpeg4 output.avi  

# 转换成H264编解码
# 其中 -i 表示输入文件， -vcodec  h264 表示视频编解码方式为 H264。
ffmpeg -i input_file -vcodec h264 output_file

# 转换成H265编解码
# 其中 -i 表示输入文件， -vcodec  hevc 表示视频编解码方式为 H265，注意ffmpeg 中名称为 hevc，不是H265！
ffmpeg -i input_file -vcode hevc output_file  

# 可视化帧信息
./ffprobe -show_packets -of xml -i test_mix.mp4

# 设置输出分辨率
ffmpeg -i input_file -vcodec h264 -s 1280x720 output_file  

# 设置输出文件的音视频比特率
# 其中 -b:v 10M 表示视频码率为10Mbps， -b:a 128K 表示音频码率为 128Kbps，注意FFMPEG对于码率控制，有时候不太准确，跟输入源有一定关系。
ffmpeg -i input_file  -vcodec h264 -b:v 10M -b:a 128K output_file  

# 剪切某段视频
# 下面的两种方式等价，时间格式支持 HH:MM:SS或者秒数。 -ss 开始时间， -t 持续时间， -vcodec copy 保持原视频编码， -acodec copy 保持原音频编码。
ffmpeg -ss 0:05:00 -t 0:1:30 -i input_file -vcodec copy -acodec copy output_file  [-y 覆盖存在文件]
ffmpeg -ss 300 -t 90  -i input_file -vcodec copy -acodec copy output_file  

# 分离音视频流保存为不同文件
# 其中 -an 表示不处理音频， -vn 表示不处理视频。
ffmpeg -i input_file -vcodec copy -an output_file_video　　//提取视频流  
ffmpeg -i input_file -acodec copy -vn output_file_audio　　//提取音频流  

# 合并多个音视频文件为一个文件
ffmpeg –i video_file –i audio_file –vcodec copy –acodec copy output_file  

# 提取视频图像保存为图片文件
# 其中 -r 表示提取图像的频率，-f 表示输出格式， %3d 表示文件命名方式（也即生成的图片名为 image-001.jpeg, image-002.jpeg, ...., image-999.jpeg）。
ffmpeg –i input_file –r 1 –f image2 image-%3d.jpeg        //提取图片  

# 控制关键帧间隔和B帧
# 其中-bf 控制B帧数目，-g 控制关键帧间隔， -f 控制文件格式（format，注意与codec的区别）。
ffmpeg –i input_file  –vcodec h264 –bf 0 –g 25 –s 854x480 –an –f m4v output_file  

# 录制rtsp网络数据流
# 将rtsp的网络视频流文件保存为 out.avi 本地文件
ffmpeg –i rtsp://192.168.1.100:5555/test_stream –vcodec copy out.avi  

# 多个视频文件拼接
# 首先创建一个需要拼接的文件，例如 concat.txt，内容如下：
file 'orig_20160616113303_0.avi'
file 'orig_20160616113303_1.avi'
# 然后执行如下命令 
ffmpeg  -f concat -i concat.txt  -c copy orig_20160616113303_merge.avi 

# 读取文件持续推rtmp流
ffmpeg -re -stream_loop -1 -i Trouble.Maker.1080P.avi -vcodec copy -acodec aac -f flv -y rtmp://10.1.0.249:11935/live/test1

# windows下查看音频采集设备
ffmpeg -list_devices true -f dshow -i dummy

# 旋转视频
#   0=逆时针90° and 垂直翻转  (default) 
#   1=顺时针90°
#   2=逆时针90°  
#   3=顺时针90° and 垂直翻转  
fmpeg -i inputfile.mp4 -vf "transpose=1" outputfile.mp4

```