### 注意事项
* 如果目标机上没有`certmgr.exe`,那么可以从主机上直接拷贝一个64位的`certmgr.exe`过去的
* 如果重新生成了sys文件而没有修改inf文件的话,那么只需要在生成sys文件后再次执行对驱动文件的重新签名即可;测试证书和目录文件都不需要重新生成;
* 最好都使用管理员权限来启动WDK/DDK环境命令行;在目标机上的注册证书,可以写一个bat文件的;
* 测试签名可以使用预安装来安装;makecert/Inf2cat/Signtool/certmgr都在WDK中有;
 
### 1. 制作测试证书
1. 制作一个私有证书`allenTest.cer`:
`makecert -r -pe -ss PrivateCertStore -n CN=Allen(Test) allenTest.cer`
 
2. 将私有证书导入到系统的可信根证书中
`certmgr.exe /add allenTest.cer /s /r localMachine root`
 
### 2. 用可信根证书为驱动签名
1. 利用`.INF`文件生成`.cat文件,这里生成的平台为`win7 x64`, `/driver:./`指明了`.inf`文件的目录路径,不必给出文件名.
"Inf2cat.exe /driver:./ /os:7_X64"
 
2. 用第一步导入系统的测试证书为cat文件签名
`Signtool sign /v /s PrivateCertStore /n Allen(Test) /t http://timestamp.verisign.com/scripts/timestamp.dll XXXX.cat`
 
3. 用第一步导入系统的测试证书为sys文件签名
`Signtool sign /v /s PrivateCertStore /n Allen(Test) /t http://timestamp.verisign.com/scripts/timestamp.dll XXXX.sys`
 
### 3. 目标机安装测试签名
* 将第一步的证书文件导入目标机中
```
certmgr.exe /add  allenTest .cer /s /r localMachine root             #受信任的根证书颁发机构
certmgr.exe /add  allenTest .cer /s /r localMachine trustedpublisher #受信任的发布者
```
* 目标机启用测试签名功能, 需要重启生效
```
c:\windows\system32\ bcdedit.exe /set TESTSIGNING ON     # bcdedit.exe /set TESTSIGNING OFF 需要显式关闭测试模式
```


 