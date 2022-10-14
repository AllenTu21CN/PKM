## Camera1

### SurfaceView+Camera.setPreviewCallback

* 方法：
    1. 创建一个android.hardware.Camera对象
    2. 创建一个SurfaceView用于原始preview的显示
    3. 在SurfaceCreated回调函数中用 Camera.setPreviewDisplay（）将自己设置成preview的View
    4. 设置preview的数据格式，以及尺寸
    5. 调用Camera.startPreview（）开始预览
    6. 调用Camera.setPreviewCallback()或者Camera.setPreviewCallbackWithBuffer(）注册回调函数
* 代码 android-camera-preview
* 参考 **http://tangzm.com/blog/?p=18**
* 参考 https://www.jianshu.com/p/9e0f3fc5a3b4
* 默认输出NV21
* VIA820：1080p@30fps    4k@N/A
* 三星S7(820)：4k@30fps
* 可以把SurfaceView的尺寸设为 1x1，让其不可见
* setPreviewCallbackWithBuffer效率更高，省去每次分配buffer的时间：
    * setcallback之前Camera.addCallbackBuffer添加buff
    * 每次callback使用完buff之后再add回去
    * 预先add的buff最好≥2

### SurfaceTexture+Camera.setPreviewTexture+GLES

* 代码？
* 参考 http://tangzm.com/blog/?p=20

## Camera2

### TextureView::(SurfaceTextureListener+getBitmap)

* 代码 camera2basic::Camera2BasicFragment_getBitmap
* 默认输出ARGB
* 在main thread
* VIA820：preview-1080p@22fps dump-1080p@[15-17]fps
* getBitmap耗时巨大，**且无解**

### CameraDevice.createCaptureSession+Alloction.getSurface(RenderScript)

* 代码 camera2basic::Camera2BasicFragment_Allocation  or  MediaEngine
* 参考 https://github.com/googlesamples/android-HdrViewfinder
* 默认输出NV21
* 在new thread
* VIA820: 1080p@22fps  preview/dump-1080p@15fps

### CameraDevice.createCaptureSession+ImageReader.getSurface

* 代码 MediaEngine
* 默认输出YUV420_888
* 在camera background thread
* VIA820: preview/dump-1080p@15fps  preview/dump-4k@5fps 
* OnImageAvailable耗时不大，**但性能低**

### EGLSurface+GLES20.glReadPixels

* 代码 MediaEngine
* 参考 https://bigflake.com/mediacodec/ExtractMpegFramesTest_egl14.java.txt 和 MediaEngine::EglSurfaceBase
* 默认输出ARGB_888
* 在new render thread
* VIA820: preview-1080p@30fps   dump/render-1080p@5fps
* **glReadPixels耗时600/1000ms，性能低**
