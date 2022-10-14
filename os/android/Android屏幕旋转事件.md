# 监听横竖屏变化

* 限制: 
    * 仅监听横竖屏变化; 屏幕旋转180°的情况无法监听
    * 故，强制屏幕方向后，将无法收到旋转事件
    `setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE)`

* 配置事件(AndroidManifest.xml)
```XML
<activity android:name="cn.lx.mbs.ui.MainActivity"
    android:configChanges="screenSize|orientation">
    ...
</activity>
```

* 事件处理
```JAVA
@Override
public void onConfigurationChanged(Configuration newConfig) {
    super.onConfigurationChanged(newConfig);
    int rotation = getWindowManager().getDefaultDisplay().getRotation();
    ...
}
```

# 监听屏幕垂直角度变化

* 限制: 通过传感器获取到屏幕垂直方向的实时度数,所以回调频繁,性能消耗大

* 启用和处理
```JAVA
 mOrientationListener = new OrientationEventListener(this) {
    @Override
    public void onOrientationChanged(int orientation) {
        Log.d(TAG, "onOrientationChanged: " + orientation);
        if (orientation == OrientationEventListener.ORIENTATION_UNKNOWN) {
            return; // 手机平放时，检测不到有效的角度
        }
        // 只检测是否有四个角度的改变
        if (orientation > 350 || orientation < 10) {
            // 0度：手机默认竖屏状态（home键在正下方）
            Log.d(TAG, "下");
        } else if (orientation > 80 && orientation < 100) {
            // 90度：手机顺时针旋转90度横屏（home建在左侧）
            Log.d(TAG, "左");
        } else if (orientation > 170 && orientation < 190) {
            // 180度：手机顺时针旋转180度竖屏（home键在上方）
            Log.d(TAG, "上");
        } else if (orientation > 260 && orientation < 280) {
            // 270度：手机顺时针旋转270度横屏，（home键在右侧）
            Log.d(TAG, "右");
        }
    }
};
```

* 开启调用mOrientationListener. enable(), 关闭调用mOrientationListener. disable()；

# 监听显示变化

* 原理：使用监听DisplayManager方式，手机切换方向会导致UI 显示的改变

* 注册和监听
```JAVA
DisplayManager.DisplayListener mDisplayListener = new DisplayManager.DisplayListener() {
    @Override
    public void onDisplayAdded(int displayId) {
        android.util.Log.i(TAG, "Display #" + displayId + " added.");
    }

    @Override
    public void onDisplayChanged(int displayId) {
        android.util.Log.i(TAG, "Display #" + displayId + " changed.");
    }

    @Override
    public void onDisplayRemoved(int displayId) {
        android.util.Log.i(TAG, "Display #" + displayId + " removed.");
    }
};

DisplayManager displayManager = (DisplayManager) mContext.getSystemService(Context.DISPLAY_SERVICE);
displayManager.registerDisplayListener(mDisplayListener, UIThreadHandler);
```