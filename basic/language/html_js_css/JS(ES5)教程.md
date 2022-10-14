# JS入门教程(ES5)

* [参考教程](https://wangdoc.com/javascript/index.html)
* 本文前提: 了解JAVA或C/C++的语法

## 1. 简述

### 1.1 什么是JS

* 轻量级脚本语言、嵌入式语言，依赖宿主环境：浏览器、Node等
* 支持面向对象和面向函数

### 1.2 优势

* 前端开发必不可少
* 跨平台支持，应用领域广
* 简单易学
* 语法强大，表达力强
* 支持编译运行
    * 还支持WebAssembly格式 (预编译成类.pyc中间代码)
* 支持事件驱动和非阻塞模式
* 社区和文档支持丰富
* 开发和测试环境方便

### 1.3 学什么

* 基本语法
* 标准库
* 浏览器API
    * 浏览器控制类
    * DOM类，操作网页资源
    * Web类，实现网络功能
* Node API：略

### 1.4 历史

* 完整历史略
* JS与JAVA相似点：JS参考了JAVA的基本语法和对象体系，但并没有用JAVA的静态类型； 故当初从LiveScript改名为JavaScript；
* JS和JAVA的最大区别：
    * JS的函数是一种独立数据类型
    * 采用基于原型对象（prototype）的继承链
    * JS可以由解释器直接执行
* JS与ECMAScript
    * 微软模仿JS提出JScript，并在IE中支持，威胁到了JS的主导权
    * JS所有者Netscape将JS提交给ECMA来标准化以抗衡微软，所以产生了ECMAScript标准
    * 所以，ECMAScript标准化了JS的**基本语法结构**，JS实现了ECMAScript标准和其他部署环境相关的标准（如W3C的DOM标准）
* 1999年12月，ECMAScript 3.0版发布，成为 JavaScript 的通行标准，得到了广泛支持
* 2007年10月，ECMAScript 4.0版草案发布，但是由于目标过于激进，以 Yahoo、Microsoft、Google 为首的大公司反对，该标准作废，2008年7月，将ES4中兼容ES3的部分改动发布为3.1
* 2009年12月，ES3.1改名ECMAScript 5.0，正式发布，其与ES3基本保持兼容
* 2011年6月，ECMAScript 5.1版发布，并且成为 ISO 国际标准。到了2012年底，所有主要浏览器都支持 ECMAScript 5.1版的全部功能。
* 2015年6月，ECMAScript 6 正式发布，其包含了当初ES4中部分比较激进的改动
* 更多历史和相关技术的编年史可[参考](https://wangdoc.com/javascript/basic/history.html)

## 2. 语法

### 2.1 标识符

* 用于标识各种值的名称，有和JAVA/C/C++类似的限制，但允许中文等其他语言的字符、允许`$`
* 如下关键词不能作为标识符
    ```
    arguments、break、case、catch、class、const、continue、debugger、default、delete、do、else、enum、eval、export、extends、false、finally、for、function、if、implements、import、in、instanceof、interface、let、new、null、package、private、protected、public、return、static、super、switch、this、throw、true、try、typeof、var、void、while、with、yield
    ```

### 2.2 变量

* 通过`var`在当前的作用域内声明一个变量
    * ES5中，只有`函数作用域`和`全局作用域`
    * 没有`块作用域`(包括`{}`，`if/switch(){}`，`while/for(){}`)，ES6才引入块作用域
    * 所以语句块中`var`申明的变量属于上层作用域

    ```JS
    // 申明、并初始化变量
    // 变量名区分大小写
    var a = 1;

    // 申明变量但未初始化,则为undefined
    var a;

    // 同一变量多次申明,仅第一次生效,
    // 但赋值会保留，因为申明并初始化操作总会被自动拆成申明和赋值两条语句
    var a = 1;
    var a;      // 无作用,无报错
    var a = 2;  // a=2生效

    // 申明多个变量
    var a,b,c
    var a=1, b=2

    // JS是动态类型语言，变量的类型可以多次变化
    var a = 1
    a = "1"
    ```

* JS特有的"链式作用域"结构（chain scope）
    * 子对象（作用域）会一级一级地向上寻找所有父对象（作用域）的变量
    * 所以，父对象（作用域）的所有变量，对子对象（作用域）都是可见的，反之则不成立。
    * **疑问？：** 特有吗？java/C/C++/python不都这样？
    
    ```JS
    var v = 1;
    function f(){
        var v = 2;
        console.log(v);
    }
    f() // 2
    v // 1
    ```

* 如果直接初始化变量而不使用`var`关键词，相当于对全局对象`window`属性赋值
    * `delete`操作符只能删除对象的属性，不能删除变量

    ```JS
    var a = 1;
    b = 2;          // 等同于 window.b = 2

    console.log(a); // 1
    console.log(b); // 2

    (function varFun() {
        console.log(a); // 1
        console.log(b); // 2

        var c = 3;
        d = 4;          // 等同于 window.d = 4
        console.log(c); // 3
        console.log(d); // 4
    })();
    console.log(c); // c is not defined
    console.log(d); // 4

    delete a;
    console.log(a); // 1

    delete b;       // 等同于 delete window.b
    console.log(b); // b is not defined

    delete d;       // 等同于 delete window.d
    console.log(d); // d is not defined
    ```
    
* `未定义`和`未初始化`含义不同，前者解释器引发`ReferenceError`异常，后者的值为`undefined`
    * 访问值为`undefined`的变量的子成员，会引发`TypeError`异常

* `变量提升`
    * 注：要避免触发`变量提升`：为了避免人为的理解障碍，建议所有的变量申明都放在作用域的前部

    * `变量提升`：`函数声明`和`变量声明`总是会被解释器自动提升到作用域的最顶部
        ```JS
        x = 5;
        var x;

        // 等同如下

        var x;
        x = 5;
        ```

    * `申明变量并初始化`时仅提升了申明操作,初始化操作被保留原处
        ```JS
        var s = x;
        var x = "test";

        // 等同如下

        var x;
        var s = x; // x = undifined
        x = "test";
        ```

    * `隐含申明`的变量,并不会被提升
        ```JS
        var s = x; // 并没有提升x的隐含申明,所以Chrome上执行报错ReferenceError
        x = "test"; 
        ```

### 2.3 数据类型

#### 分类

* 基础数据类型
    * `number`数值（整型、小数）
    * `string`字符串
    * `boolean`布尔值（`true`、`false`）
        * 在需要使用boolean时，会自动将`undefined null 0 "" '' NaN`自动转为`false`，其他为`true`
* 复合类型
    * `object`对象：数组(`[]，Array`)，自定义对象（`{}，Object`）
    * `function`函数，本质上也是一种对象
* 特殊类型
    * `undefined`，未定义
    * `null`，空值

#### 类型判断

* `typeof`运算符，返回值的类型名
    * 例如：`typeof "123"` 返回 `"string"`
    * 只会返回大类型名称，例如`typeof []`返回`"object"`而不是`"Array"`
    * 历史原因，`typeof null`返回`"object"`
* `instanceof`运算符
* `Object.prototype.toString`方法

#### `undefined`与`null`

* if判断时，`undefined`与`null`都会自动转为`false`
* `undefined==null`为`true`
* 算术运算时，`null`会自动转为`0`
* 如下场景下为`undefined`
    * 变量申明但不确定类型未初始化,即类型不确定时
    * 函数调用未传入对应参数时
    * 访问对象中未定义的成员时
    * 函数中没有`return`时，返回值默认为未定义

### 2.4 数值

* 数值为：整数或者小数

#### 存储、范围、精度

* 都以64位浮点数形式储存，故`1 === 1.0`为`true`

* 因为浮点数不是精确值，所以涉及小数运算时有些坑
    ```JS
    0.1 + 0.2 === 0.3
    // false

    0.3 / 0.1
    // 2.9999999999999996

    (0.3 - 0.2) === (0.2 - 0.1)
    // false
    ```

* **未理解：** 数值范围：(2^1024, 2^-1023)，可精确表示的浮点数范围： [-2^53, 2^53]，原因参见[3.1 数值精度](#f31)

#### 进制

* 十进制：`1`, 十六进制：`0xaa`, 二进制：`0b11 或 0B11`

* 八进制有些特殊
    ```JS
    777     // 777
    0777    // 511
    00777   // 511
    0o777   // 511

    888     // 888
    0888    // 888
    00888   // 888
    0o888   // 报错
    ```

#### 几个相关全局方法

* `parseInt()`：将字符串转为整数，
    * `parseInt('123')`为 `123`
    * 可以指定字符串的进制，默认为十进制，如`parseInt('10', 16)`为 `16`
    * 支持传入“浮点数”，自动去掉小数位
    * 自动去除空格、回车换行、制表符等不可见字符
    * 从左往右解析直到第一个非数字为止（类似0x除外）
    * 如果字符串完全无法解析为数字，则返回`NaN`
    * 注意：`parseInt('010')`为 `10`而不是`8`
    * 注意：不支持解析科学计数法，会简单当作字符串处理，如`parseInt('1e+21')`为`1`
    * 更多参见[3.3 parseInt其他说明](#f33)

* `parseFloat()`与`parseInt()`类似，但又如下差别
    * 支持科学计数法表示的字符串

* `Number()`是上面2个方法的结合，将值转成数字，更严格(更多边界需要测试)
    * `Number('123abc')`为`NaN`
    * 参数为对象或多值数组时，为`NaN`
    * 参数为单值数组时，为那个单值

* `isNaN()`用于判断`数字`是否为NaN，若传入非数字类型，会先通过`Number`转换成数字
    * 更推荐`value !== value`来判断是否为NaN

#### 几个特殊值

* 存在`-0`和`+0`，大部分场景都一样，都当作普通`0`处理，唯一的差别：`(1 / +0) === (1 / -0)`为`false`

* `NaN`是特殊的数字
    * 含义为“Not a Number”，常表示结果为非法数字
    * 它不等于任何值，包括它本身
    * 它与任何值运算的结果还是`NaN`

* `Infinity`表示无穷大，具体参见[3.2 Infinity](#f32)

### 2.5 字符串

* 单双引号的使用和python类似；

* 可以类似C/C++一样，行尾加`\`来分多行来书写一个单行字符串；也可以用`+`的方式来多行书写

* 注意：由于 HTML 语言的属性值使用双引号，所以很多项目约定 JS 字符串只使用单引号；不管怎样，尽量避免风格不统一，单双引号混用

* 字符串可以当作const的字符数组，并使用下标运算访问

* 内置base64转码方法
    * `btoa()`：任意值转为 Base64 编码
    * `atob()`：Base64 编码转为原来的值
    * 上述两方法仅支持ASCII字符，否则报错
    * 如果是非ASCII字符，需要如此：
    ```JS
    function b64Encode(str) {
    return btoa(encodeURIComponent(str));
    }

    function b64Decode(str) {
    return decodeURIComponent(atob(str));
    }

    b64Encode('你好') // "JUU0JUJEJUEwJUU1JUE1JUJE"
    b64Decode('JUU0JUJEJUEwJUU1JUE1JUJE') // "你好"
    ```

* 参见[3.4 字符集](#f34)

### 2.6 对象

* 定义/访问/赋值
    * key名是字符串，有没有引号都可以

    * 若key名为数值，会通过`Number`自动转为字符串

    * key没有引号的标识符，则需要符合标识符规范
    ```JS
    var obj = {};
    // 等同
    var obj = new Object();

    var obj = {
        foo: 'Hello',    // 可以没有引号
        'bar': 'World',  // 也可以又引号
        '1foo': 'Hello', // 不满足标识符规范时只能用引号
        // 1bar: 'World', 不合法
        1: "A",
        1.2: "B",
    };

    obj.foo;        // Hello
    obj.bar;        // World
    obj["foo"];     // Hello
    obj["1foo"];    // Hello
    obj["1"+"foo"]; // Hello
    // obj.1foo 不合法
    obj["1"];       // A
    obj[1.2];       // B,对于object会自动将数值key转成字符串

    obj.foo = 'Hello1'
    obj['foo'] = 'Hello2'
    ```

* 对象的属性/成员可以动态添加，类似python

* 判断属性是否存在
    ```JS
    var obj = { p: 1 };

    // in 运算符不能区分本身还是父类的属性
    'p' in obj // true
    'toString' in obj // true

    // hasOwnProperty用于判断自身的属性
    obj.hasOwnProperty('toString') // false
    ```

* 遍历属性
    ```JS
    var obj = { p: 1 };

    // 获取obj本身的所有属性名列表，不包含父类
    Object.keys(obj) // ["p"]
    // 然后遍历

    // for遍历obj所有属性(包含父类);且会跳过不可遍历的属性(如toString)
    // 可以通过hasOwnProperty过滤出自身属性
    for (var i in obj) {
        console.log('键名：', i);
        console.log('键值：', obj[i]);
    }
    ```

* 删除属性：`delete obj.foo`可以删除obj的foo属性
    * 可以通过`Object.defineProperty`方式定义属性，并设置为不可修改(删除)，`提高`笔记中详述
    * 只能删除当前对象的属性，无法删除父类的属性
    * 删除成功、属性不存在、删除父类属性等，都返回true，实际没参考价值

* 对象转换成基础数据类型，在一些操作中（比如`+`运算），会自动按如下规则转换
    * 一般将先`obj.valueOf()`获取对象原始值，如果值为基础数据类型，那么返回，
    * 若依然为非基础类型，则执行`obj.valueOf().toString()`返回字符串
    * 有个特例，对于`Date`对象的实例，将优先执行`toString()`
    * 可以自定义重载`valueOf()`和`toString()`修改这个转换值

* 有时候，一段代码可以解释为对象的定义（表达式），也可以是一段代码块（语句），JS引擎一般一律按语句块解释
    * `({ foo: 123 })`类似这样加上`()`就可以强制让JS引擎解释为表达式
    * 这个问题在使用`eval`语句执行动态代码时经常遇到

* 更多对象说明参见[Object](https://wangdoc.com/javascript/stdlib/object.html)
    * Object.xxx 属于Object的静态方法和属性
    * Object.prototype.xxx 属于实例的方法和属性

* 更多参见[对象属性的描述](https://wangdoc.com/javascript/stdlib/attributes.html)
    * `Object.defineProperty和defineProperties()`
    * 修改属性描述
    * 拷贝对象
    * 控制对象属性状态

* **不推荐使用:** 通过`with`语句可以更便捷的操作同一个对象的多个属性
    ```JS
    with (document.links[0]){
        console.log(href);
        console.log(title);
        console.log(style);
    }
    // 等同于
    console.log(document.links[0].href);
    console.log(document.links[0].title);
    console.log(document.links[0].style);
    ```
    * 注意，如果with区块内部有变量的赋值操作，必须是当前对象已经存在的属性，否则会创造一个当前作用域的全局变量。
        ```JS
        var obj = {};
        with (obj) {
            p1 = 4;
            p2 = 5;
        }

        obj.p1 // undefined
        p1 // 4
        ```
    * 上述因为with区块没有改变作用域，它的内部依然是当前作用域。这造成了with语句的一个很大的弊病，就是绑定对象不明确。这非常不利于代码的除错和模块化，编译器也无法对这段代码进行优化，只能留到运行时判断，这就拖慢了运行速度。因此，不建议使用with语句

### 2.7 数组

* 任何类型都可以放到数组中，成员类型可以不一致

* 支持多维数组

* 数组的本质也是对象，只是key名是0，1，...：
    ```JS
    var arr = ['a', 'b', 'c'];

    Object.keys(arr)
    // ["0", "1", "2"]
    ```

* `length`属性,返回数组中最大整数key+1
    * 设置`length`属性值可以修改数组的大小和内容

    ```JS
    var arr = ['a', 'b', 'c']
    arr.length; // 3
    Object.keys(arr) // ["0", "1", "2"]

    var arr = [];
    arr[100] = 1;
    arr.length; //101
    Object.keys(arr) // ["100"]

    var arr = ['a', 'b', 'c'];
    arr.length = 2;
    arr; // ["a", "b"]
    arr.length = 3;
    arr; // ["a", "b", empty]

    var arr = [];
    arr[2.1] = 'abc';
    arr.length // 0
    ```

* 可以像对象一样给数组添加属性，但是`length`仅和最大整数key相关；
    * 合法的key为：0~4294967295
    * 不合法的key都会转成字符串当作属性添加

* 数组也支持`in`运算符，用于判断是否有指定key：不存在的key，或者key为`undefined`则返回`false`

* 数组遍历
    * `for...in`或`Object.keys()`可以像对象一样遍历数组，**包括那些非数字key**（**会自动跳过空位**）
        ```JS
        var a = [1, 2, 3];
        a.foo = true;

        for (var key in a) {
            console.log(key);
        }

        // 0
        // 1
        // 2
        // foo
        ```
    
    * 可用通用的`for`或`while`仅遍历数字键

    * 数组特有的`forEach`遍历，（**会自动跳过空位**）
    ```JS
    var colors = ['red', 'green', 'blue'];
    colors.forEach(function (color) {
        console.log(color);
    });
    // red
    // green
    // blue
    ```

* 空位，如下情况会产生空位
    ```JS
    // 定义时
    var arr = [1, , 3];
    arr; // [1, empty, 3]

    // 修改length扩容
    var arr = [1];
    arr.length = 2;
    arr; // [1, empty]

    // 不连续插值
    var arr = [];
    arr[1] = 2;
    arr; // [empty, 2]

    // delete删除成员
    var arr = [1, 2];
    delete arr[1];
    arr; // [1, empty]
    ```

* `类似数组`: 有`length`属性，但属性不会动态变化的对象，如下都是假数组: 函数`arguments`对象、大多数 DOM 元素集、字符串
    * 可以通过Array的方法将类似数组转成数组
        ```JS
        var arr = Array.prototype.slice.call(arrayLike);
        ```
    * 通过call()把数组的方法放到对象上面，也可以使伪数组使用数组方法; 注意，这种方法比直接使用数组原生的forEach要慢
        ```JS
        function print(value, index) {
            console.log(index + ' : ' + value);
        }

        Array.prototype.forEach.call(arrayLike, print);
        ```

### 2.8 函数

#### 函数申明

```JS

// 方法一：命名函数
function print(s) {
  console.log(s);
}

// 方法二：函数表达式(匿名函数)
var print = function(s) {
  console.log(s);
};

// 方法二(2)：函数表达式（命名函数），函数名仅在函数体内有效；
// 调试时便于根据调用栈找到函数名
var print = function x(){
  console.log(typeof x);
};
x // ReferenceError: x is not defined
print() // function

// 方法三（几乎无人使用）：Function 构造函数
var add = new Function(
  'x',
  'y',
  'return x + y'    // Function构造函数的最后一个参数是定义的函数的函数体，以上都是函数参数
);
// 等同于
function add(x, y) {
  return x + y;
}

// 方法四：IIFE，定义并立即调用函数
(function(){ /* code */ }());
// 或者
(function(){ /* code */ })();
```

#### 重要说明

* JS中函数本质还是一种数据类型，可以理解为`函数指针`
    * 因此函数名和变量名一样，存在变量提升的情况

* JS不存在函数重载，所以同一个函数被多次声明，后面的声明就会覆盖前面的声明
    ```JS
    function f() {
    console.log(1);
    }
    f() // 2

    function f() {
    console.log(2);
    }
    f() // 2
    ```

* JS也支持闭包，作用和效果类似java和C++的lambda表达式

#### 函数的属性和方法

* `name`属性：返回函数的名称（`属于函数的静态属性`）

    ```JS
    function f1() {}
    f1.name // "f1"

    var f2 = function () {};
    f2.name // "f2"

    var f3 = function myName() {};
    f3.name // 'myName'
    ```

* `length`属性：返回函数预期传入的参数个数；常用作模仿函数重载（`属于函数的静态属性`）

    ```JS
    function f(a, b) {}
    f.length // 2
    ```

* `toString()`方法：返回一个字符串：函数的源码（`属于函数的静态属性`）
    * 但只有自定义函数有效，内置的原生函数返回"function (){[native code]}"
    * 返回的字符串包含函数中的注释，所以这可以作为“获取多行字符串”的小技巧
        ```JS
        var multiline = function (fn) {
            var arr = fn.toString().split('\n');
            return arr.slice(1, arr.length - 1).join('\n');
        };

        function f() {/*这是一个
        多行注释
        */}

        multiline(f);
        // " 这是一个
        //   多行注释"
        ```

* `arguments`属性：返回函数执行中，实际传入的参数列表（`属于函数的运行时属性`）
    * 必然只能在函数体内访问
    * `正常模式`下可以运行中修改该属性，`严格模式`下运行中忽略该属性修改
        ```JS
        var f = function(a, b) {
            'use strict'; // 开启严格模式
            arguments[0] = 3;
            arguments[1] = 2;
            return a + b;
        }

        f(1, 1) // 2
        ```
    * 该属性的数据类型是"受限制的"数组，即无法使用数组的`slice`、`forEach`等方法，通过如下方法可以将其转成正常数组
        ```JS
        var args = Array.prototype.slice.call(arguments);
        // 或者
        var args = [];
        for (var i = 0; i < arguments.length; i++) {
            args.push(arguments[i]);
        }
        ```
    * **不推荐使用**： `arguments.callee`表示这些参数属于哪个方法
        ```JS
        var f = function () {
            console.log(arguments.callee === f);
        }

        f() // true
        ```
#### 其他

* 如果函数有多个同名参数，仅最后一个同名参数有效

* **不推荐使用**： `eval()`，将传入的字符串当作语句执行
    * 在当前作用域内执行，`正常模式下`可以修改当前作用域的变量的值，`严格模式`可以不会添加变量到当前作用域，但是可以修改
    * 如果参数不是字符串，那么会原样返回
    * 由于安全问题和JS引擎无法优化执行，所以不推荐使用
    * 其他使用注意点参见[3.5 eval的别名调用](#f35)

### 2.9 运算符

#### 算术运算符

* `+`表示`加法`或者`连接`运算，根据运算子和顺序（从左往右执行）决定语义
    * 如果运算子为对象，则将其转换成基础类型值后才执行操作

* `- * /`运算为纯粹算术运算,强制将运算子转换为数值

* `%`余数运算，有个注意点
    ```JS
    1 % 2  // 1
    -1 % 2 // -1
    1 % -2 // 1
    ```
* `+`和`-`是数值运算符，为一元运算符，将任何值转为数值，和`Number`功能一样，只是`-`取负
    ```JS
    +true // 1
    +[] // 0
    +{} // NaN
    ```

* `**`指数运算符，且为**右结合**运算符
    ```JS
    2 ** 4 // 16
    2 ** 3 ** 2 // 512 相当于 2 ** (3 ** 2)
    ```

#### 比较运算符

* `> >= < <= == === != !==`，共8种比较运算符，其实分两类：相等比较和非相等比较

* 对于`非相等的比较`(`>`等)，算法是先看两个运算子是否**都是**字符串，如果是的，就按照字典顺序比较（实际上是比较 Unicode 码点）；否则，将两个运算子都转成数值(`Number()`)，再比较数值的大小

* 对于`==`，将它们转换成同一个类型，再用`===`进行比较
    * 都是基础数据类型，都转换成数值（`Number()`）
    * 复合类型与基础类型比较，则将复合类型转换成相同的基础类型（`Number()/String()`）

* 对于`===` （**推荐使用**）
    * 类型不同，则`false`
    * 对于基础数据类型，则比较值
    * 对于复合类型(数组、对象、函数)，则比较对象地址

* 对于`!==`和`!=`则是`== ===`的取反

#### Boolean运算符

* `! && || ?:`，将表达式转换成布尔值

* 利用`||`短路机制，可以用于设置默认值
    ```JS
    function saveText(text) {
        text = text || '';
        // ...
    }

    // 或者写成
    saveText(this.text || '')
    ```

#### 位运算符

* `| & ~ ^ << >>` 常用的位运算

* `>>>`为头部补零的右移运算符

* 详细参见[二进制位运算符](https://wangdoc.com/javascript/operators/bit.html)

#### 其他运算符

* `void`运算符，作用是执行一个表达式，然后返回undefined
    ```JS
    var x = 3;
    void (x = 5) //undefined
    x // 5
    ```
    * 经常用作浏览器的书签工具（Bookmarklet），以及在超级链接中插入代码防止网页跳转，具体参见[3.6 void的应用](#f36)
    
* `,`运算符，用于对两个表达式求值，并返回后一个表达式的值
    ```JS
    var x = 0;
    var y = (x++, 10);
    x // 1
    y // 10
    ```
    * 一个用途是，在返回一个值之前，进行一些辅助操作
    ```JS
    var value = (console.log('Hi!'), true);
    // Hi!

    value // true
    ```
#### 运算符优先级

* 参见[运算顺序](https://wangdoc.com/javascript/operators/priority.html#%E8%BF%90%E7%AE%97%E9%A1%BA%E5%BA%8F)

### 数据类型转换

* 自动、强制转换参见[数据类型的转换](https://wangdoc.com/javascript/features/conversion.html)

### 错误处理

* 基础错误对象`Error`
    * `message`属性为必选，表示错误描述
    * `name`和`stack`属性为非JS标准属性，但一般引擎都会实现

* JS派生出6大错误对象
    * `SyntaxError`，语法错误，代码解析错误
    * `ReferenceError`，引用一个不存在的变量时发生的错误；或将一个值分配给无法分配的对象，比如对函数的运行结果赋值
    * `RangeError`，一个值超出有效范围时发生的错误。主要有几种情况，一是数组长度为负数，二是Number对象的方法参数超出范围，以及函数堆栈超过最大值。
    * `TypeError`是变量或参数不是预期类型时发生的错误
    * `URIError`是 URI 相关函数的参数不正确时抛出的错误
    * `EvalError`，已经作废

* 自定义错误
```JS
function UserError(message) {
  this.message = message || '默认信息';
  this.name = 'UserError';
}

UserError.prototype = new Error();
UserError.prototype.constructor = UserError;

throw new UserError('这是自定义的错误！');
```

* `throw`，中止程序，可以是抛出错误以及其他任何值

* `try...catch...finally`，捕获并处理错误

### console对象和控制台

* 参见[console对象](https://wangdoc.com/javascript/features/console.html)

* `console.log()，console.info()，console.debug()，console.warn()，console.error()`

* `console.count()`

* `console.dir()，console.dirxml()`

* `console.time()，console.timeEnd()`

* `console.trace()，console.clear()`

* `debugger`

### 其他注意点

* `switch`语句的值和`case`值为严格相等比较(`===`)

* 代码标签(label)，与`break`或`continue`搭配使用可以实现`goto`的部分效果
    * `<label>+break`：跳出`<label>`所标记的(紧跟的循环、判断、普通)代码块
        ```JS
        top:
        for (var i = 0; i < 3; i++){
            for (var j = 0; j < 3; j++){
            if (i === 1 && j === 1) break top;
            console.log('i=' + i + ', j=' + j);
            }
        }
        // 输出:
        // i=0, j=0
        // i=0, j=1
        // i=0, j=2
        // i=1, j=0
        ```
    * `<label>+continue`：会跳过当前循环，直接进入下一轮外层循环
        ```JS
        top:
        for (var i = 0; i < 3; i++){
            for (var j = 0; j < 3; j++){
            if (i === 1 && j === 1) continue top;
            console.log('i=' + i + ', j=' + j);
            }
        }
        // 输出:
        // i=0, j=0
        // i=0, j=1
        // i=0, j=2
        // i=1, j=0
        // i=2, j=0
        // i=2, j=1
        // i=2, j=2
        ```

* **注释**和JAVA、C/C++类似，但有如下差别
    ```JS
    ;<!-- 兼容HTML的单行注释 --> 
    ```

## 3. 附加

### 3.1 数值精度(IEEE 754) <span id="f31"></span>

根据国际标准 IEEE 754，JavaScript 浮点数的64个二进制位，从最左边开始，是这样组成的。

* 第1位：符号位，0表示正数，1表示负数
* 第2位到第12位（共11位）：指数部分（决定了数值的大小）
* 第13位到第64位（共52位）：小数部分（即有效数字）（决定了数值的精度）

指数部分一共有11个二进制位，因此大小范围就是0到2047。IEEE 754 规定，如果指数部分的值在0到2047之间（不含两个端点），那么有效数字的第一位默认总是1，不保存在64位浮点数之中。也就是说，有效数字这时总是1.xx...xx的形式，其中xx..xx的部分保存在64位浮点数之中，最长可能为52位。因此，JavaScript 提供的有效数字最长为53个二进制位。

`(-1)^符号位 * 1.xx...xx * 2^指数部分`

上面公式是正常情况下（指数部分在0到2047之间），一个数在 JavaScript 内部实际的表示形式。

精度最多只能到53个二进制位，这意味着，绝对值小于2的53次方的整数，即-253到253，都可以精确表示。

```JS
Math.pow(2, 53)
// 9007199254740992

Math.pow(2, 53) + 1
// 9007199254740992

Math.pow(2, 53) + 2
// 9007199254740994

Math.pow(2, 53) + 3
// 9007199254740996

Math.pow(2, 53) + 4
// 9007199254740996
```

上面代码中，大于2的53次方以后，整数运算的结果开始出现错误。所以，大于2的53次方的数值，都无法保持精度。由于2的53次方是一个16位的十进制数值，所以简单的法则就是，JavaScript 对15位的十进制数都可以精确处理。

```JS
Math.pow(2, 53)
// 9007199254740992

// 多出的三个有效数字，将无法保存
9007199254740992111
// 9007199254740992000
```

上面示例表明，大于2的53次方以后，多出来的有效数字（最后三位的111）都会无法保存，变成0。

### 3.2 Infinity <span id="f32"></span>

* 含义，Infinity表示“无穷”
    ```JS
    // 场景一:表达式的计算结果太大，超出了能够表示的范围
    Math.pow(2, 1024)
    // Infinity

    // 场景二:0除以0会得到NaN，而非0数值除以0，会返回Infinity
    0 / 0 // NaN
    1 / 0 // Infinity

    // Infinity有正负之分，Infinity表示正的无穷，-Infinity表示负的无穷。
    Infinity === -Infinity // false

    1 / -0 // -Infinity
    -1 / -0 // Infinity

    // Infinity大于一切数值（除了NaN），-Infinity小于一切数值（除了NaN）。
    Infinity > 1000 // true
    -Infinity < -1000 // true

    // Infinity与NaN比较，总是返回false。
    Infinity > NaN // false
    -Infinity > NaN // false

    Infinity < NaN // false
    -Infinity < NaN // false
    ```

* Infinity的四则运算，符合无穷的数学计算规则。
    ```JS
    5 * Infinity // Infinity
    5 - Infinity // -Infinity
    Infinity / 5 // Infinity
    5 / Infinity // 0

    // 0乘以Infinity，返回NaN；0除以Infinity，返回0；Infinity除以0，返回Infinity。
    0 * Infinity // NaN
    0 / Infinity // 0
    Infinity / 0 // Infinity

    // Infinity加上或乘以Infinity，返回的还是Infinity。
    Infinity + Infinity // Infinity
    Infinity * Infinity // Infinity

    // Infinity减去或除以Infinity，得到NaN。
    Infinity - Infinity // NaN
    Infinity / Infinity // NaN

    // Infinity与null计算时，null会转成0，等同于与0的计算。
    null * Infinity // NaN
    null / Infinity // 0
    Infinity / null // Infinity

    // Infinity与undefined计算，返回的都是NaN。
    undefined + Infinity // NaN
    undefined - Infinity // NaN
    undefined * Infinity // NaN
    undefined / Infinity // NaN
    Infinity / undefined // NaN
    ```

* 由于数值正向溢出（overflow）、负向溢出（underflow）和被0除，JavaScript 都不报错，所以单纯的数学运算几乎没有可能抛出错误。

### 3.3 parseInt其他说明 <span id="f33"></span>

* 如果第二个参数不是数值，会被自动转为一个整数。这个整数只有在2到36之间，才能得到有意义的结果，超出这个范围，则返回NaN。如果第二个参数是0、undefined和null，则直接忽略。
    ```JS
    parseInt('10', 37) // NaN
    parseInt('10', 1) // NaN
    parseInt('10', 0) // 10
    parseInt('10', null) // 10
    parseInt('10', undefined) // 10
    ```

* 如果字符串包含对于指定进制无意义的字符，则从最高位开始，只返回可以转换的数值。如果最高位无法转换，则直接返回NaN。
    ```JS
    parseInt('1546', 2) // 1
    parseInt('546', 2) // NaN
    ```

* 如果parseInt的第一个参数不是字符串，会被先转为字符串。这会导致一些令人意外的结果。
    ```JS
    parseInt(0x11, 36)  // 43
    parseInt(0x11, 2)   // 1

    // 等同于
    parseInt(String(0x11), 36)
    parseInt(String(0x11), 2)

    // 等同于
    parseInt('17', 36)  // 43
    parseInt('17', 2)   // 1
    ```

* 这种处理方式，对于八进制的前缀0，尤其需要注意。JavaScript 不再允许将带有前缀0的数字视为八进制数，而是要求忽略这个0。但是，为了保证兼容性，大部分浏览器并没有部署这一条规定。
    ```JS
    parseInt(011, 2) // NaN

    // 等同于
    parseInt(String(011), 2)

    // 等同于
    parseInt(String(9), 2)
    ```

### 3.4 字符集 <span id="f34"></span>

* JS 使用 Unicode 字符集。JavaScript 引擎内部，所有字符都用 Unicode 表示。

* 可以通过码点值表示一个Unicode字符
    * `\HHH`，反斜杠后面紧跟三个八进制数（000到377），代表一个字符。HHH对应该字符的 Unicode 码点，比如\251表示版权符号。显然，这种方法只能输出256种字符。
    * `\xHH`，\x后面紧跟两个十六进制数（00到FF），代表一个字符。HH对应该字符的 Unicode 码点，比如\xA9表示版权符号。这种方法也只能输出256种字符。
    * `\uXXXX`，\u后面紧跟四个十六进制数（0000到FFFF），代表一个字符。XXXX对应该字符的 Unicode 码点，比如\u00A9表示版权符号。
    ```JS
    '\251' // "©"
    '\xA9' // "©"
    '\u00A9' // "©"

    '\172' === 'z' // true
    '\x7A' === 'z' // true
    '\u007A' === 'z' // true
    ```

* 不仅可以用码点值定义字符，JS代码也可以用码点值表示；解析代码的时候，JS 会自动识别一个字符是字面形式表示，还是 Unicode 形式表示。输出给用户的时候，所有字符都会转成字面形式。
    ```JS
    var f\u006F\u006F = 'abc';
    foo // "abc"
    ```

* 我们还需要知道，每个字符在 JavaScript 内部都是以16位（即2个字节）的 UTF-16 格式储存。也就是说，JavaScript 的单位字符长度固定为16位长度，即2个字节。

但是，UTF-16 有两种长度：对于码点在U+0000到U+FFFF之间的字符，长度为16位（即2个字节）；对于码点在U+10000到U+10FFFF之间的字符，长度为32位（即4个字节），而且前两个字节在0xD800到0xDBFF之间，后两个字节在0xDC00到0xDFFF之间。举例来说，码点U+1D306对应的字符为𝌆，它写成 UTF-16 就是0xD834 0xDF06。

JavaScript 对 UTF-16 的支持是不完整的，由于历史原因，只支持两字节的字符，不支持四字节的字符。这是因为 JavaScript 第一版发布的时候，Unicode 的码点只编到U+FFFF，因此两字节足够表示了。后来，Unicode 纳入的字符越来越多，出现了四字节的编码。但是，JavaScript 的标准此时已经定型了，统一将字符长度限制在两字节，导致无法识别四字节的字符。上一节的那个四字节字符𝌆，浏览器会正确识别这是一个字符，但是 JavaScript 无法识别，会认为这是两个字符。

```JS
'𝌆'.length // 2
```

上面代码中，JavaScript 认为𝌆的长度为2，而不是1。

总结一下，对于码点在U+10000到U+10FFFF之间的字符，JavaScript 总是认为它们是两个字符（length属性为2）。所以处理的时候，必须把这一点考虑在内，也就是说，JavaScript 返回的字符串长度可能是不正确的。

### 3.5 eval的别名调用 <span id="f35"></span>

前面说过eval不利于引擎优化执行速度。更麻烦的是，还有下面这种情况，引擎在静态代码分析的阶段，根本无法分辨执行的是eval。

```JS
var m = eval;
m('var x = 1');
x // 1
```

上面代码中，变量m是eval的别名。静态代码分析阶段，引擎分辨不出m('var x = 1')执行的是eval命令。

为了保证eval的别名不影响代码优化，JavaScript 的标准规定，凡是使用别名执行eval，eval内部一律是全局作用域。

```JS
var a = 1;

function f() {
  var a = 2;
  var e = eval;
  e('console.log(a)');
}

f() // 1
```

上面代码中，eval是别名调用，所以即使它是在函数中，它的作用域还是全局作用域，因此输出的a为全局变量。这样的话，引擎就能确认e()不会对当前的函数作用域产生影响，优化的时候就可以把这一行排除掉。

eval的别名调用的形式五花八门，只要不是直接调用，都属于别名调用，因为引擎只能分辨eval()这一种形式是直接调用。

```JS
eval.call(null, '...')
window.eval('...')
(1, eval)('...')
(eval, eval)('...')
```

上面这些形式都是eval的别名调用，作用域都是全局作用域。

### 3.6 void的应用 <span id="f36"></span>

这个运算符的主要用途是浏览器的书签工具（Bookmarklet），以及在超级链接中插入代码防止网页跳转。请看下面的代码：

```HTML
<script>
function f() {
  console.log('Hello World');
}
</script>
<a href="http://example.com" onclick="f(); return false;">点击</a>
```

上面代码中，点击链接后，会先执行onclick的代码，由于onclick返回false，所以浏览器不会跳转到`example.com`。void运算符可以取代上面的写法:

```HTML
<a href="javascript: void(f())">点击</a>
```

下面是一个更实际的例子，用户点击链接提交表单，但是不产生页面跳转。

```HTML
<a href="javascript: void(document.form.submit())">
  提交
</a>
```