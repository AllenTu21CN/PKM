### ע������
* ���Ŀ�����û��`certmgr.exe`,��ô���Դ�������ֱ�ӿ���һ��64λ��`certmgr.exe`��ȥ��
* �������������sys�ļ���û���޸�inf�ļ��Ļ�,��ôֻ��Ҫ������sys�ļ����ٴ�ִ�ж������ļ�������ǩ������;����֤���Ŀ¼�ļ�������Ҫ��������;
* ��ö�ʹ�ù���ԱȨ��������WDK/DDK����������;��Ŀ����ϵ�ע��֤��,����дһ��bat�ļ���;
* ����ǩ������ʹ��Ԥ��װ����װ;makecert/Inf2cat/Signtool/certmgr����WDK����;
 
### 1. ��������֤��
1. ����һ��˽��֤��`allenTest.cer`:
`makecert -r -pe -ss PrivateCertStore -n CN=Allen(Test) allenTest.cer`
 
2. ��˽��֤�鵼�뵽ϵͳ�Ŀ��Ÿ�֤����
`certmgr.exe /add allenTest.cer /s /r localMachine root`
 
### 2. �ÿ��Ÿ�֤��Ϊ����ǩ��
1. ����`.INF`�ļ�����`.cat�ļ�,�������ɵ�ƽ̨Ϊ`win7 x64`, `/driver:./`ָ����`.inf`�ļ���Ŀ¼·��,���ظ����ļ���.
"Inf2cat.exe /driver:./ /os:7_X64"
 
2. �õ�һ������ϵͳ�Ĳ���֤��Ϊcat�ļ�ǩ��
`Signtool sign /v /s PrivateCertStore /n Allen(Test) /t http://timestamp.verisign.com/scripts/timestamp.dll XXXX.cat`
 
3. �õ�һ������ϵͳ�Ĳ���֤��Ϊsys�ļ�ǩ��
`Signtool sign /v /s PrivateCertStore /n Allen(Test) /t http://timestamp.verisign.com/scripts/timestamp.dll XXXX.sys`
 
### 3. Ŀ�����װ����ǩ��
* ����һ����֤���ļ�����Ŀ�����
```
certmgr.exe /add  allenTest .cer /s /r localMachine root             #�����εĸ�֤��䷢����
certmgr.exe /add  allenTest .cer /s /r localMachine trustedpublisher #�����εķ�����
```
* Ŀ������ò���ǩ������, ��Ҫ������Ч
```
c:\windows\system32\ bcdedit.exe /set TESTSIGNING ON     # bcdedit.exe /set TESTSIGNING OFF ��Ҫ��ʽ�رղ���ģʽ
```


 