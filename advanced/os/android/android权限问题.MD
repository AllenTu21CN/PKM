## 2022.7.29 Android 8 应用移植到 Android 11报权限错误

### 背景

* 随着产品硬件升级，Android也从8升级到了11，出现了SDK接口、非SDK接口变动，故现有应用需要移植
* 无论何种情况下(卸载、升级、OTA、OTA回滚、系统故障等)，须保证应用的数据(配置文件、数据库、其他资源文件)都不会被自动清除、重置，故通过反射等途径将数据目录移至SDCard下，而非默认的应用数据目录

### 问题描述

* 问题1：应用卸载重新安装后，无法读取sdcard下应用数据
* 问题2：清除所有历史数据后，应用无法在sdcard下创建目录和数据

### 定位过程

略

### 结论和分析

* Android9开始，加强了非SDK接口的分类和限制，日志中会提醒非SDK接口

```
Accessing hidden field Landroid/app/ContextImpl;->mPreferencesDir:Ljava/io/File; (greylist, reflection, allowed)
```

* Android 9开始，加强了基于用户的权限管理，应用只能访问自己的数据(应用卸载重新安装后，用户发生变化)

* Android运行时版本、SDK版本(编译版本/目标版本)都会影响实际的运行效果，可能是SDK的兼容性 > 系统的安全性