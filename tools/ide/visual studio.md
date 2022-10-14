# VS小技巧

## MFC程序标准输出到控制台

* 通过如下方法使用 printf 或者 std::cout 可以在控制台中输出

* VS Project -> Setting... -> 选项 Post-builder step -> 新建command, 输入如下, 其中 filename 为可执行文件名: 

```editbin /SUBSYSTEM:CONSOLE $(OUTDIR)\$(TargetFileName)```
