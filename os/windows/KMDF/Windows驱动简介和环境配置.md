[TOC]
****
### 1.  概述
微软在`WDK7600`以后就不再提供独立的内核驱动开发包了,而是必须首先安装微软集成开发环境VisualStudio,然后再从微软官网下载集成的WDK开发包/或者离线安装包,但是安装后Visual Studio就集驱动程序开发/编译/安装/部署/调试于一身,使得Windows驱动程序开发会变得更容易. 对于Windows 10和Visual Studio2015驱动开发WDK环境变量的配置,与其它版本的Windows和WDK环境的配置有很大不同.
 
****
### 2. WDF驱动模型
VxD(Windows 95/98) -> WDM(2000) ->WDF(Vista)
 
设备驱动程序是硬件设备连接到计算机系统的软件接口,任何设备都必须有相应的驱动程序才能在计算机系统上正常工作. 设备驱动程序的优劣直接关系到整个系统的性能和稳定性,因此,设计和开发稳定高效的驱动程序具有重要意义.
 
早期的Windows 95/98的设备驱动是VxD(Virtual DeviceDriver),其中x表示某一类设备. 从Windows 2000开始,开发驱动程序必以WDM(Windows Driver Model)为基础的,但是,如果使用DDK来开发WDM,其开发难度之大,根本不能奢望像用户模式应用程序开发那样容易,因此,一般用户都是使用WinDriver/DriverStudio之类的第三方工具.
 
为改善这种局面,从Vista开始,微软推出了新的驱动程序开发环境WDF(Windows Driver Foundation ). WDF(WindowsDriver Foundation)是微软提出的下一代全新的驱动程序模型,它是在WDM(windowsDriver Model)的基础上发展而来的,支持面向对象/事件驱动的驱动程序开发,提供了比WDM更高层次抽象的高度灵活/可扩展/可诊断的驱动程序框架. WDF框架管理了大多数与操作系统相关的交互,实现了公共的驱动程序功能(如电源管理/PnP支持),隔离了设备驱动程序与操作系统内核,降低了驱动程序对内核的影响.
 
WDF提供了两个框架:KMDF(内核模式驱动程序框架)和UMDF(用户模式驱动程序框架):
* 内核模式驱动程序 KMDF(Kernel-Mode DriverFramework):
这类驱动程序作为内核模式操作系统组件的一部分执行,它们管理I/O/即插即用/内存/进程和线程/安全等. 内核模式驱动程序通常为分层结构. KMDF是Windows系统底层驱动,文件名为:`*.SYS`. 关于KMDF更多的内容,可参阅 MSDN中`Getting Started with Kernel-ModeDriver Framework`.
* 用户模式驱动程序 UMDF(User-Mode DriverFramework):
这类驱动程序通常提供 Win32 应用程序与内核模式驱动程序或其他操作系统组件之间的接口. 用户模式驱动程序支持基于协议或基于串行总线(如摄像机和便携音乐播放器)的设备. UMDF是用户层驱动,文件名为:`*.DLL`. 关于KMDF更多的内容,可参阅 MSDN中`Introduction to UMDF`.
 
无论内核模式的驱动程序或者用户模式的驱动程序,都使用同一环境进行构建,这一环境称为WDK; 都采用同一套对象模型构建,采用同一个基础承载,这个基础就是WDF.
 
由于WDF驱动模型提供了面向对象和事件驱动的驱动程序开发框架,大大降低了开发难度. 从现在开始,掌握Windows设备驱动程序的开发人员,由过去的`专业`人士,将变为`普通`大众. 因此,像WinDriver/DriverStudio之类的第三方工具也随之退出历史舞台.
 
更重要的,也是微软反复炫耀的是封装了驱动程序中的某些共同行为:例如即插即用和电源管理就属于这种共同行为. 因为大多数驱动程序中都需要处理即插即用和电源管理问题,据说这大概要上千行的代码,况且,没有相当水平还不一定能处理好. 为了一劳永逸,WDF干脆将即插即用和电源管理封装了进了对象之内,一举成了对象的默认行为.
 
WDF将驱动程序与操作系统内核之间进行了分离,驱动程序与操作系统交互工作交给框架内封装的方法(函数)完成,这样驱动开发者只需专注处理硬件的行为即可. 这不仅避免了顾此失彼两面不周的弊端,也由于双方的分离,对操作系统内的某些改动,硬件制造商配套驱动程序的开发都有莫大的好处.
 
****
### 3. 用户模式和内核模式
运行 Windows 的计算机中的处理器有两个不同模式:`用户模式`和`内核模式`. 根据处理器上运行的代码的类型,处理器在两个模式之间切换. 应用程序在用户模式下运行,核心操作系统组件在内核模式下运行. 多个驱动程序在内核模式下运行时,某些驱动程序可能在用户模式下运行.
 
当启动用户模式的应用程序时,Windows 会为该应用程序创建`进程`. 进程为应用程序提供专用的`虚拟地址空间`和专用的`句柄表格`. 由于应用程序的虚拟地址空间为专用空间,一个应用程序无法更改属于其他应用程序的数据. 每个应用程序都孤立运行,如果一个应用程序损坏,则损坏会限制到该应用程序. 其他应用程序和操作系统不会受该损坏的影响.
 
用户模式应用程序的虚拟地址空间除了为专用空间以外,还会受到限制. 在用户模式下运行的处理器无法访问为该操作系统保留的虚拟地址. 限制用户模式应用程序的虚拟地址空间可防止应用程序更改并且可能损坏关键的操作系统数据.
 
在内核模式下运行的所有代码都共享单个虚拟地址空间. 这表示内核模式驱动程序未从其他驱动程序和操作系统自身独立开来. 如果内核模式驱动程序意外写入错误的虚拟地址,则属于操作系统或其他驱动程序的数据可能会受到损坏. 如果内核模式驱动程序损坏,则整个操作系统会损坏.
 
此图说明了用户模式组件与内核模式组件之间的通信.
![](http://www.th7.cn/d/file/p/2016/03/11/77a358360e67c0b6396520d05f027b8c.jpg)
 
****
### 4. 驱动模型特点
UMDF和传统的驱动程序差异非常大,简要说来,UMDF是这样的: `UMDF是基于COM思想的,运行于用户模式(RING3)的驱动程序模块`.
 
那么,这种驱动模型带来什么变化呢？
* 基于COM思想,引入接口机制,可以把相关联的函数分门别类进行组织,使得驱动代码清晰明了;
* 运行在RING3的驱动,大幅度降低了驱动程序在稳定性和安全性上面的风险,UMDF驱动崩溃不会导致BSoD(蓝屏);
* UMDF驱动的宿主进程是在受限的用户身份下运行的,不是受信任的系统内核模块.
* 在UMDF里面使用Win32 API.
 
运行于RING3的UMDF对于程序员开说至少带来两个额外好处:
* 驱动程序不需要强制数字签名,因为UMDF驱动不是系统信任模块,所以在x64下面的部署更加方便. 特别是个人开发者可能无法承受WHQL的费用,或者其他原因暂时无法WQHL的情况下,使用UMDF是一个较好的选择.
* 调试难度大幅降低,不再需要SoftICE和Syser之类的单机内核调试器或者WinDBG之类的双机调试,我们可以用WinDBG或者VS调试器attach到UMDF宿主进程即可进行调试. 可以参考调试UMDF驱动.
 
而KMDF内核模式驱动程序中的错误会损坏系统地址空间,并可能会导致计算机失败. 由于这些驱动模型的特点,在构建驱动程序的开发调试环境是也会有所区别,一般在做KMDF驱动的开发调试时都选择双机或搭建虚拟机环境进行,而UMDF驱动可以进行单机调试,**下面的环境搭建主要以更为复杂的KMDF模式为例**.
 
****
### 5. 开发调试环境配置
#### 5.0 内核日志查看
Enable DbgPrint/KdPrint Output 
1. [HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Debug Print Filter] add “DEFAULT”=dword:0000000f 
2. then reboot and run DbgView.(there is no need to reboot at most time)


#### 5.1 工具及平台环境
平台:Windows 10操作系统
开发环境:Visual Studio 2015 Enterprise和Windows WDK/Windows SDK
调试环境:Oracle VM VirtualBox 5.0.14虚拟机
 
#### 5.2 方法/步骤
##### 5.2.1 安装/配置主机和测试机
1. 主机安装
本次搭建环境主机操作系统使用win10,首先安装Visual Studio 2015 Enterprise,然后安装Wdk 10.
`注意:WDK10一定要在vs2015后面安装,安装完后,启动vs2015在界面菜单上会出现driver菜单,如下图. 另外,一般VisualStudio 2015 Enterprise是已经内带windows SDK,但是如果不是和安装的WDK一致的版本,建议在单独安装windows SDK 10,使得WDK和SDK版本一致.`
![](http://www.th7.cn/d/file/p/2016/03/11/b8495c539a34e61864e7fd04483dd908.jpg)
![](http://www.th7.cn/d/file/p/2016/03/11/a0f118db224f49797997535c94c9ead1.jpg)
 
2. 测试机安装
本次测试机采用Oracle VM VirtualBox 5.0.14虚拟机.首先在主机上安装Oracle VM VirtualBox5.0.14虚拟机,然后在虚拟机上安装win10操作系统.
 
3. 联通主机和目标机
 
4. 目标机允许内核调试
在测试机上用系统管理员账户打开CMD命令窗口,输入下面命令:
```
C:/> bcdedit /set {default} DEBUG YES
C:/> bcdedit /set TESTSIGNING ON
```
 
##### 5.2.2 使用WinDbg调试
由于调试方式有好多种,我们选择常用的串口调试和网络调试两种方式进行讨论.
 
###### 5.2.2.1 串口调试方式
a. 在虚拟机上设置串口
首先关闭虚拟机上的操作系统,在虚拟机上设置. 对于普通的VirtualBox中的虚拟机,默认配置情况下,是没有开启对应的串口的,其配置对应的是这样的:
![](http://www.th7.cn/d/file/p/2016/03/11/9e2882d60b580e00734ca2b89b52760c.jpg)
把串口设置成主机上的一个管道pipe(pipe是个软件上的概念),pipe名: `//./pipe/<name>`
 
b. 在测试机上设置串口调试
在测试机上用系统管理员账户打开CMD命令窗口,输入下面命令:
```
C:/> bcdedit /debug on
C:/> bcdedit /dbgsettings serial debugport:1 baudrate:115200
```
其中debugport:1,表示选择串口com1.
 
然后重启操作系统,在测试机上打开CMD命令窗口,输入下面命令,就可以看到刚才配置的参数:
```
C:/> bcdedit / bcdedit /dbgsettings
```
![](http://www.th7.cn/d/file/p/2016/03/11/283ce2c72c01ae1e805c9bfee5a0d522.jpg)
 
c. 在主机启动WinDbg调试程序
在主机上打开CMD命令窗口,进入到WinDbg程序的文件夹,一般在如下的路径:
```
C:/>cd C:/Program Files (x86)/Windows Kits/10/Debuggers/x64
C:/> windbg -k com:pipe,port=//./pipe/vmbox,resets=0,reconnect
```
Windbg程序正常运行,效果如下,说明配置正确,可以通过串口调试驱动程序了.
![](http://www.th7.cn/d/file/p/2016/03/11/fe1d0fafa686557f85156e45c11ccfdf.jpg)
 
d. 问题:
现像:打开虚拟机后无法连接,提试无法打开连接端口.
故障原因:WMWare7.x及以后的版本在添加Serial Port时默认为Serial Port2,即COM2端口,而习惯了用WMWare6.x的朋友们升级7.x时习惯了按旧有设置(COM1)来进行双机调试,就会连接不上了.
解决方案:
* 在添加Serial Port时将虚拟机硬件配置中的打印机删除,再创建SerialPort时就是SerialPort1了,其它不用改变,直接可以按原有方式进行双调试的设置.
* 虚拟的硬件设置不变,在虚拟OS中添加调试引导项时(bcdedit里),把端口设为COM2,也是可行的.
以上两个方案任选其一可解决.
 
###### 5.2.2.2 网络调试方式
1. 在测试机上设置网络调试
在测试机上用系统管理员账户打开CMD命令窗口,输入下面命令:
```
C:/> bcdedit /debug on
C:/> bcdedit /dbgsettings net hostip:192.168.12.109 port:50000 key:1.2.3.4
```
其中hostip:192.168.12.109,表示主机ip地址,port:50000制定通讯端口,key参数指定通讯使用的加密密钥key.
 
然后重启操作系统,在测试机上打开CMD命令窗口,输入下面命令,就可以看到刚才配置的参数:
```
C:/> bcdedit / bcdedit /dbgsettings
```
![](http://www.th7.cn/d/file/p/2016/03/11/94102a725e66a7a23144b4ef778ca6b0.jpg)
 
2. 在主机启动WinDbg调试程序
在主机上打开CMD命令窗口,进入到WinDbg程序的文件夹,一般在如下的路径:
```
C:/>cd C:/Program Files (x86)/Windows Kits/10/Debuggers/x64
C:/> WinDbg –k net:port=50000,key=1.2.3.4
```
Windbg程序正常运行,效果如下,说明配置正确,可以通过串口调试驱动程序了.
![](http://www.th7.cn/d/file/p/2016/03/11/9150446ec3b92db9423c63d053c96119.jpg)
 
##### 5.2.3 设置Visual Studio 2015调试方式
Visual Studio 2015本身集驱动程序开发/编译/安装/部署/调试于一身,使得Windows驱动程序开发会变得更容易. Visual Studio 2015作为调试/部署界面和使用WinDbg作为调试界面在配置上有一些不同.
 
###### 5.2.3.1 串口调试方式
1. 配置虚拟机,参见`5.2.2.1(1-2)`
 
2. 设置测试机为WDKRemoteUser
在目标机上,运行与目标机平台匹配的WDK测试目标安装程序 MSI. 可以在安装过WDK10的主机的WDK10安装目录下找到该MSI.
 
例如:`C:/Program Files (x86)/WindowsKits/10/Remote/x64/WDK Test Target Setup x64-x64_en-us.msi`
 
![](http://www.th7.cn/d/file/p/2016/03/11/2396fd545a44e2c0656658f45ac6a766.jpg)
 
`注意:如果该程序没有安装,则下一步在vs2015上面做的配置就不能成功,我就在这一步上被卡住很久,一直找不到原因.`
 
3. 在主机设置Visual Studio 2015
在主机上,在 Visual Studio 的`Driver`菜单中,选择`Test>Configure Deivce`. 单击`Add New Device`.
![](http://www.th7.cn/d/file/p/2016/03/11/d61f0815475c41775c90c8d0e7e95175.jpg)
 
`注意:如果vs2015的版本是vs2015 Update 1版本,这时候会出现一个错误提示窗口,不能进行相应的设置,提示如下:`
![](http://www.th7.cn/d/file/p/2016/03/11/bc875548b70bd672a2c0fa65fcb1600b.jpg)
 
这是可以从驱动程序的项目点右键->选择属性菜单->选择调试选项->在右边要启动的调试器上选择Debugging Tools for windows – Kernel Debugger->在Remote Computer Name上点击配置,就会出现配置窗口,界面如下:
![](http://www.th7.cn/d/file/p/2016/03/11/f8d323632faa90ae9ebde3342a92d80b.jpg)
 
点击`Add New Devide`添加提个测试主机,在出现的界面上填写测试目标主机的显示名称,设备类型(计算机设备或移动设备),测试目标主机的主机名(我测试填IP地址也可以),在Provision Options选项中建议选择第一项`Provision Deviceand choose debugger setting`,这样vs2015就能就行自动部署测试的驱动程序,但是设置的时候测试目标主机会自动多次重启以完成设置. 选择第二项的话,测试目标主机不会重启,但是需要手工部署测试的驱动程序.
![](http://www.th7.cn/d/file/p/2016/03/11/3170aace6626b42f3571815276f3925a.jpg)
 
点击下一步,出现连接类型(可以选择串口/网络等),然后填写在测试目标主机上设置的参数,设置界面如下:
![](http://www.th7.cn/d/file/p/2016/03/11/00f181685ce6a4c2a754e86a89430cba.jpg)
 
设置完成,点击下一步,则会在测试目标主机上进行相应的环境设置,期间测试目标主机会有多次重启. 显示界面如下:
![](http://www.th7.cn/d/file/p/2016/03/11/ae822a7917c862747f59c49871c6b293.jpg)
 
`注意:如果在设置过程中在Creaing system restorepoint出现错误的话,需要在测试目标主机的C盘上打开系统还原点. 设置的步骤为:开始右键->系统->系统保护->配置->启动并设置C盘还原点.`
 
设置完成后显示如下界面,提示配置成功:
![](http://www.th7.cn/d/file/p/2016/03/11/1a0b26c36dbebfc39b78f52f293f7171.jpg)
 
点击完成,显示如下界面:
![](http://www.th7.cn/d/file/p/2016/03/11/8fef349bc85b2f542950207a594efabb.jpg)
点击Apply应用,然后选择OK.
 
4. 在主机Visual Studio 2015测试配置
最后在主机的VS2015的调试菜单中->选择附加到进程-->在传输(P)下拉框中选择Windows Kernel ModelDebugger,在限定符(Q)下拉框中选择刚才配置的测试目标主机名称->在可用进程中选择Kernel->最后点击附加按钮.
![](http://www.th7.cn/d/file/p/2016/03/11/e26c9eb2e768729fc8abcf629365ce5c.jpg)
 
点击附加按钮后出现调试界面表示配置成功,可以进行驱动调试了.
 
`注意:这里如果点击附加按钮后Vs2015出现崩溃现象请检查Win10的版本,如果win10的版本还是10240版本的话请升级到10586版本. 可以点击VS2015的帮助菜单->关于Microsoft Visual Studio->系统信息可以查看到系统的版本. 本人在这里折腾了将近两天的时间,最后才找到是由于版本不匹配的问题.`
 
###### 5.2.3.2 网络调试方式
1. 设置测试机为WDKRemoteUser
参见`5.2.3.1(2)`
 
2. 在主机设置Visual Studio 2015
参见`5.2.3.1(3)`
 
3. 在主机Visual Studio 2015测试配置
参见`5.2.3.1(4)`
![](http://www.th7.cn/d/file/p/2016/03/11/2179a5a5c9e9b762439ebe511a377d82.jpg)