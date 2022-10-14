
```SHELL
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

## dump系统服务的各种状态 
dumpsys -l # 查询系统服务列表,类似 <service list> 具体可参见附录1
```

## 附录

### 1. 系统服务列表

具体说明可以参见[官方dumpsys](https://www.jianshu.com/p/e710fe2410ca) 和 [dumpsys命令用法](https://www.jianshu.com/p/e710fe2410ca)

|服务名|功能|类名|
|-|-|-|
|activity|	AMS相关信息|	ActivityManagerService|
|package|	PMS相关信息|	PackageManagerService|
|window|	WMS相关信息|	WindowManagerService|
|input|	IMS相关信息|	InputManagerService|
|power|	PMS相关信息|	PowerManagerService|
|batterystats|	电池统计信息|	BatterystatsService|
|battery|	电池信息|	BatteryService|
|alarm|	闹钟信息|	AlarmManagerService|
|dropbox|	调试相关|	DropboxManagerService|
|procstats|	进程统计|	ProcessStatsService|
|cpuinfo|	CPU|	CpuBinder|
|meminfo|	内存|	MemBinder|
|gfxinfo|	图像|	GraphicsBinder|
|dbinfo|	数据库|	DbBinder|
|SurfaceFlinger|	图像相关||
|appops|	app使用情况||
|permission|	权限||
|processinfo|	进程服务||
|batteryproperties|	电池相关||
|audio|	查看声音信息||
|netstats|	查看网络统计信息||
|diskstats|	查看空间free状态||
|jobscheduler|	查看任务计划||
|wifi|	wifi信息||
|diskstats|	磁盘情况||
|usagestats|	用户使用情况||
|devicestoragemonitor|	设备信息||
|…|	…||
