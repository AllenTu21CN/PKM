
## I帧和IDR帧

* I（Intra）帧:帧内编码帧，是一种自带全部信息的独立帧，无需参考其它图像便可独立进行解码，视频序列中的第一个帧始终都是I帧。 

* IDR（Instantaneous Decoding Refresh）帧，即时解码刷新帧，也是I帧；

* IDR一定是I帧，I帧不一定是IDR；往往首个I帧是IDR；

* IDR有I帧没有的随机访问的能力：遇到IDR，解码器会清空DPB（DecodedPictureBuffer 参考帧列表）（同时会更新PPS 和 SPS）：
    * 即IDR帧之后的所有帧都不能引用任何IDR帧之前的帧的内容
    * 与此相反，对于普通的I帧来说，位于其之后的B和P帧可以引用位于普通I帧之前的I帧

## GOP

*TODO*

## Slice

*TODO*