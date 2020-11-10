
```
## 设置ntp服务器
settings get global ntp_server
settings put global ntp_server ntp1.aliyun.com

## logcat命令
logcat -v color --pid=$(pidof -s com.sanbu.app_tsbox) *:D -e "^(?!.*(jitter_buffer.cc|audio_engine.cc|timer.cc|jitter_buffer_h264.cc|media_engine.cpp|rmsi|capture_width|session_manager)).*$"

## 启动/停止应用
am start -n com.sanbu.app_tsbox/.MainActivity
am start -n com.android.settings/.TetherSettings
am start -n com.android.settings/.wifi.WifiSettings 
am start -n com.android.settings/.Settings
am force-stop sanbu.hdv_aio

## 启动unittest
adb shell am instrument -w -r   -e debug false -e class 'com.sanbu.app_tsbox_test.Tsbox2Test' com.sanbu.app_tsbox_test.test/android.support.test.runner.AndroidJUnitRunner

## 启停网络调试
setprop service.adb.tcp.port 5555
settings put global adb_enabled 0
settings put global adb_enabled 1
```