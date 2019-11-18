# Markdown入门

## 标题
* "# "+ 标题名
* "#"越多等级越低
* 最多6级标题

## 有序列表
1. "1\. 内容"
1. 数字不一定要连续,会自动标序

## 无序列表
* 以'*'开头
- 以'-'开头
+ 以'+'开头

## 加粗/斜体/删除线
* **加粗**
* *斜体*
* ~~删除线~~

## 高亮
* `1个单引号`或者``2个单引号``都可以高亮单词
* 三个单引号可以高亮多行
* Tab键开头也可以高亮整行

## 代码
```
#Start and end with "```"
While True:
    print 'HelloWorld'

```

## 图片
* 绝对路径

    ![图片示例](file:///D:/Documents/PKM/language/Markdown/markdown.png)

* 相对路径

    ![图片示例](markdown.png)

* http路径

    ![图片示例](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1554612506634&di=9be9773881dcd3854c63f43713159d5b&imgtype=0&src=http%3A%2F%2Fwww.mayi888.com%2Fwp-content%2Fuploads%2F2017%2F02%2F15ed000bb2d80328ea69.jpg)

## 链接
[链接描述](file:///D:/Documents/PKM/language/Markdown/markdown.png)


## 引用
> 以">"开头
>> 引用中的引用

## 分割线
* 三个以上的'*'
****

# 进阶

## 表格
* `-`之上是表头,之下是内容
* `:-`左对齐,`-:`右对齐, `:-:`表示居中
* `-`默认

|t1 |t2 |t3 |t4   |
|---|:--|--:|:---:|
|1  |1  |1  |1    |
|22 |22 |22 |22   |
|333|333|333|333  |

## 目录
* 添加"[TOC]"即可自动插入当前目录
* `非标准语法`

## 流程图
* 关键词:start/end/operation/subroutine/condition和inputoutput
* [更多关于流程图的语法说明](http://adrai.github.io/flowchart.js/)
* 以\` \` \`flow开头, 以\` \` \`结尾
``` 
` ` ` flow
st=>start: Start
e=>end: End
op1=>operation: My Operation
sub1=>subroutine: My Subroutine
cond=>condition: Yes or No?
io=>inputoutput: catch something...
st->op1->cond
cond(yes)->io->e
cond(no)->sub1(right)->op1
` ` `
```

```flow
st=>start: Start
e=>end: End
op1=>operation: My Operation
sub1=>subroutine: My Subroutine
cond=>condition: Yes or No?
io=>inputoutput: catch something...
st->op1->cond
cond(yes)->io->e
cond(no)->sub1(right)->op1
```

## 时序图
1. 以\` \` \`sequence开头,以\` \` \`结尾
2. [更多关于时序图的语法说明](http://bramp.github.io/js-sequence-diagrams/)
```
` ` `sequence
Alice->Bob: Hello Bob, how are you?
Note right of Bob: Bob thinks
Bob-->Alice: I am good thanks!
` ` `
```

```sequence
Alice->Bob: Hello Bob, how are you?
Note right of Bob: Bob thinks
Bob-->Alice: I am good thanks!
```

## 数学公式
* 行内公式: $\Gamma(n) = (n-1)!\quad\forall n\in\mathbb N$
* 块级公式:
    $$ x = \dfrac{-b \pm \sqrt{b^2 - 4ac}}{2a} $$








