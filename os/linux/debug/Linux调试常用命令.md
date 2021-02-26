
* 查看进程打开的文件: `lsof -p <PID>`

* 查看进程资源: `cd /proc/<PID>`，其中包含：打开的文件描述符、共享内存、进程限制等等

* 查看库文件信息
    * `nm`, `ar`

    * `objdump`：显示目标文件中的详细信息
        * 另 `objdump -d <target>`，可以查看目标的汇编代码

    * `ldd`：查看目标的动态库依赖

    * `readelf` 显示ELF文件的信息 
        * `-r`(重定位的) `-d`(动态的)
        * 查看目标的动态库依赖：`readelf -d <target> | grep NEEDED`

* 查看进程内存信息: `cat /proc/<PID>/status`

    |Name|Desc|
    |--|--|
    |1|2|
    |VmHWM|  物理内存: 分配到的峰值|
    |VmLck|  物理内存: 锁住的物理内存的大小.锁住的物理内存不能交换到硬盘(locked_vm)|
    |VmRSS|  物理内存: 现在使用的物理内存,ps命令的参数rss的值(rss)|
    |VmPeak| 虚拟地址空间: 运行过程中占用内存的峰值|
    |VmSize| 虚拟地址空间: 正在占用的内存,与pmap pid的值基本一致(total_vm-reserved_vm)|
    |VmData| 虚拟地址空间: 数据段的大小(total_vm-shared_vm-stack_vm),存放全局变量、常数以及动态分配的数据空间(malloc/new等); 动态申请的内存属于堆区(heap),堆区一般是程序员自已分配释放的，属于数据段|
    |VmStk|  堆栈段的大小(stack_vm),存放子程序、函数返回地址、子程序的参数及局部变量; 堆栈段代表的是程序中的栈区(stack),栈区一般是编译器自动分配释放的|
    |VmExe|  代码的大小,不包括使用的库(end_code-start_code),可被相同进程共享|
    |VmLib|  使用LIB库的大小(exec_lib)|
    |VmPTE|  占用的页表的大小|
    |VmSwap| 占用Swap的大小|

* 程序内存管理(泄露)测试：`valgrind`

* 查看进程代码栈：`gstack <PID>`