## 开发库

### Sogou C++ Workflow
* https://github.com/sogou/workflow
* 搜狗公司C++服务器引擎: `一个设计轻盈优雅的企业级程序引擎，可以满足大多数C++后端开发需求`
* 不依赖boost和asio实现的网络库+框架，基本无第三方依赖
* 大致了解了设计思路和特点，和3BU Avalon的设计很相似，但比Avalon轻量级，在些非公司的小项目中可以尝试使用
    * 程序=协议+算法+任务流
    * 协议：标准的、非标准的网络协议，用于数据的序列化和反序列化
    * 算法：特定场景下的一套执行流程，可以理解为函数；任何一次边界清晰的复杂计算，都应该包装成算法
    * 任务流：就是实际的业务逻辑，就是把开发好的协议与算法放在流程图里使用起来

## 学习资源

### AI-Expert-Roadmap
* https://github.com/AMAI-GmbH/AI-Expert-Roadmap
* AI的学习路径图

### Mastering_Go_ZH_CN
* https://github.com/hantmac/Mastering_Go_ZH_CN
* 《Mastering GO》中文译本，本书适用于 Golang 程序员。内容包括但不限于并发、网络编程、垃圾回收、组合、GO UNIX 系统编程、基本数据类型（Array、Slice、Map）、GO 源码、反射、接口、类型方法等高级概念。 

## 玩具

### BilibiliTask
* https://github.com/srcrs/BilibiliTask
* Java，借助GitHub Action自动完成B站任务的项目，但是可以借鉴其思路

### beeplay
* https://github.com/watilde/beeplay
* 让你可以用 JS 写一首“歌”的库
* demo: http://watilde.github.io/beeplay/