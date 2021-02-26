
## NPM命令

```JS
// 查看服务器上指定模块全部可用版本
npm view <module-name> versions

// 查看服务器上指定模块最新版本
npm view <module-name> version

// 查看服务器上指定模块的信息(版本/依赖等)
npm info <module-name>

// 查看本地安装的模块信息
npm ls <module-name> [-g]

// 将模块安装到全局环境下
npm install <module-name> -g

// 将模块安装到当前项目
npm install <module-name>

// 将模块安装到当前项目；
// 且将模块依赖写入package.json的dependencies中,
// npm install初始化整个项目时将被自动下载
npm install <module-name> --save

// 将模块安装到当前项目；
// 且将模块依赖写入package.json的devDependencies中,
// npm install初始化整个项目时将被自动下载
npm install <module-name> --save-dev

// dependencies和devDependencies差别:
// 前者为运行时依赖,打包时会将其打入包中
// 后者为开发时依赖,比如gulp这些开发工具,打包时不会被包含
```

## 调试技巧

1. 参考flv.js，启动NodeJS版的server，直接调试html和JS
2. 打包、压缩js时生成source map，chrome导入后可以还原代码
https://www.jianshu.com/p/ebf0ca8febb2