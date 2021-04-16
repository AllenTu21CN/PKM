
# 简介

* GDB: GNU symbolic debugger

# 常用命令

* gdb命令参数，详细查看 `gdb --help` 和 `man gdb`

```C
// 运行程序并调试
gdb <file-path>
run <command-params>

// attach到指定进程
gdb --pid <pid>
// or
gdb -x <gdb-script> -p <pid>
// or
gdb
attach pid
```

* gdb内部命令，更多在gdb中执行`help all`

```C
// 设置代码搜索路径(即符号表中的代码路径和本地路径不一致时，设置路径的转移)
set substitute-path <from_path> <to_path>

// 设置动态库搜索路径
set solib-search-path <path>

// 打断点
break filename:number 
break filename:funname
break namespace::classname::funname
// 动态库加载时检查断点
set breakpoint pending on

// 运行控制
run/r       # 开始运行
continue/c  # 继续执行到下个断点
step/s      # 单步执行
next/n      # 单步执行

// 打印变量值
print/p

// 查看所有线程栈
info threads

// 查看当前线程的调用栈
info stack

// 切换线程栈
thread/t <index>

// 切换当前线程的调用栈
ftrace/f <index>

// 显示当前行后面的源程序
list   
// 显示当前行前面的源程序
list -         
// 显示程序第linenum行的周围的源程序
list <linenum>
// 显示从first行到last行之间的源代码
list <first>, <last> 
// 显示从当前行到last行
list , <last>
// 显示函数名为function的函数的源程序
list <function>
// 设置一次显示源代码的行数。一般是打印当前行的上5行和下5行，如果显示函数是是上2行下8行
set listsize <count>
show listsize
```