# VSС����

## MFC�����׼���������̨

* ͨ�����·���ʹ�� printf ���� std::cout �����ڿ���̨�����

* VS Project -> Setting... -> ѡ�� Post-builder step -> �½�command, ��������, ���� filename Ϊ��ִ���ļ���: 

```editbin /SUBSYSTEM:CONSOLE $(OUTDIR)\$(TargetFileName)```
