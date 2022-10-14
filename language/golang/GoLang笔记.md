# GoLang笔记

## 基础

* 参考资料
    * [Go 指南(中文)](https://tour.go-zh.org/list)
    * https://go.dev/

### Hello World

```Go
package main

import "fmt"
// 分组形式导入
import (
    "fmt"
    "math"
)

func main() {
    fmt.Println("Hello World")
}
```

### fmt

```Go
import "fmt"

// 顺序输出变量值，如果是数值或字符，则输出对应的十进制表示+空格
fmt.Print("a", "b", 'a', 'b', 1, 2, "\n") //输出`ab97 98 1 2`

// 类似于java的Println：打印变量值，自动空格分割，自动输出换行符，数值和字符转成十进制表示
fmt.Println("a", "b", 'a', 'b', 1, 2) // 输出`a b 97 98 1 2`

// 类似于C的printf，更多可以见<附录-fmt.Printf>
//  %T: 变量类型: 
//  %v: 变量值
v := 1
fmt.Printf("Type: %T Value: %v\n", v, v)  // 输出`Type: int Value: 1`
```

### 包

* 按照**约定**，包名与导入路径的最后一个元素一致。例如，"math/rand" 包中的源码均以 package rand 语句开始。

* 包里只有大写开头的变量、方法才会被导出，即只能访问包里大写开头的方法、对象

### 基本类型

```Go
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // uint8 的别名

rune // int32 的别名, 表示一个 Unicode 码点

float32 float64

complex64 complex128
```

### 函数

```Go
package main

import "fmt"

// 多值返回
func swap(x, y string) (string, string) {
    return y, x
}

// 直接返回
func split(sum int) (x, y int) {
    x = sum * 4 / 9
    y = sum - x
    return // 这种直接返回的形式在比较复杂的函数中不推荐
}

func main() {
    fmt.Println(split(17))
}
```

### 变量

```Go
// var申明变量
var i int
// var申明变量且初始化，可省略类型
var j = 1
// 函数中使用`:=`可省略var和类型；!!函数外不能使用
x, y, z := 1, false, "no!"

// 未初始化的变量会被设置为默认值
// 数值类型为 0，bool为 false，字符串为 ""

// 分组申明
var (
    ToBe   bool       = false
    MaxInt uint64     = 1<<64 - 1
)

// 显示类型转换
var x, y int = 3, 4
var f float64 = math.Sqrt(float64(x*x + y*y))
var z uint = uint(f)
var w float64 = float64(x)
```

### 常量

* 常量申明和变量类似，但不支持`:=`语法
* 常量可以是字符、字符串、布尔值或数值
* `数值常量`是一个很高精度的类型，能存储比int64还要大很多的值

```Go
const Pi = 3.14
```

### for循环

```Go
sum := 0

// 与C、JAVA类似的for循环
// 条件表达式`()`是非必须的，执行体`{}`是必须的
for i := 0; i < 10; i++ {
    sum += i
}

// 与while类似的for循环
for sum < 1000 {
    sum += sum
}

// 死循环
for {
    sum += sum
}
```

### if判断

```Go
// 条件表达式`()`是非必须的，执行体`{}`是必须的
if x < 0 {
    return
}

// 和for类似，可以有前置语句，变量作用域为if-else之间
if v := math.Pow(x, n); v < lim {
    return v
} else {
    fmt.Printf("%g >= %g\n", v, lim)
}
// 这里开始就不能使用 v 了
```

### swtich分支

```Go
// 和for/if类似，可以有前置语句
switch os := runtime.GOOS; os {
case "darwin":
    fmt.Println("OS X.")
    // 默认包含break 
case "linux":
    fmt.Println("Linux.")
    fallthrough // 显式指定不break
default:
    fmt.Printf("%s.\n", os)
}

// case可以是常量、数字、字符串，甚至可以是表达式(表达式会被从上到下顺序执行，知道匹配为止)
t := time.Now()
switch {
case t.Hour() < 12:
    fmt.Println("Good morning!")
case t.Hour() < 17:
    fmt.Println("Good afternoon.")
default:
    fmt.Println("Good evening.")
}
```

### defer推迟调用

* 推迟调用的函数在外层函数返回后才会被执行，但其参数会立即求值

* 推迟的原理是将函数压栈，所以多个defer的函数会后进先出的被执行

```Go
func main() {
    i := 1
    defer fmt.Println("defer:", i)  // 输出3: 1
    i++
    defer fmt.Println("defer:", i)  // 输出2: 2
    i++
    fmt.Println("", i)  // 输出1: 3
}
```

### 结构体

```Go
type Vertex struct {
    X, Y int
}

var (
    v1 = Vertex{1, 2}  // 创建一个 Vertex 类型的结构体
    v2 = Vertex{X: 1}  // Y:0 被隐式地赋予
    v3 = Vertex{}      // X:0 Y:0
    p  = &Vertex{1, 2} // 创建一个 *Vertex 类型的结构体（指针）
)
```

### 指针

* Go的指针大部分与C一样，但是**没有指针运算**

```Go
type Vertex struct {
    X int
    Y int
}

func main() {
    v := Vertex{1, 2}
    p := &v     // 等同于 var p *Vertex = &v
    p.X = 1e9   // 等同于(*p).X = 1e9，没有->运算符
    fmt.Println(v)
}

// 创建一个 *Vertex 类型的结构体（指针），无须像C/C++一样new
p := &Vertex{2, 3} 
```

### Array 数组

* 数组的默认初始值为：包含n个元素的数组，元素初始值为各类型的初始值

* 可以通过`len()`和`cap()`查看数组的长度和容量，对于数组两者是一样的

```Go
// 定义一个长度为10的int型数组，并初始化为10个0
var a [10]int

primes := [6]int{2, 3, 5, 7, 11, 13}
```

### Slice 切片

* 数组创建后，没法修改其长度，但可以通过切片来更灵活的使用

* 切片共享底层的数组数据

* 本质上slice=ptr(array)+len+cap，更多可参见[Go 切片：用法和本质](https://tour.go-zh.org/moretypes/15)

* 对于切片，`len()`表示当前范围的大小，`cap()`表示底层数组的大小/容量

* 切片的默认初始值为nil，即没有len、cap以及底层数组

#### 创建

```Go
// 创建切片1：从数组上划定
primes := [6]int{2, 3, 5, 7, 11, 13}
var x []int = primes[1:4] // 值为[3, 5, 7]，左开右闭
// 以下等效
z := a[0:6]
z := a[:6]
z := a[0:]
z := a[:]

// 创建切片2: 从整个匿名数组上划定
y := []int{2, 3, 5, 7, 11, 13}

// 创建切片3：make(type, len[, cap])
a := make([]int, 5)     // len=5 cap=5 [0 0 0 0 0]
b := make([]int, 0, 5)  // len=0 cap=5 []

// 创建切片4：空切片nil
var s []int // len=0 cap=0 []

// 二维切片：切片作为切片的元素
board := [][]string{
    []string{"_", "_", "_"},
    []string{"_", "_", "_"},
    []string{"_", "_", "_"},
}
```

#### 扩展

* 切片可以在原本底层数组**范围**内上重新划分边界

```Go
// 数组只有长度，但切片有长度和容量(=切片下届~数组上届)
s := []int{2, 3, 5, 7, 11, 13}  // len=6 cap=6 [2 3 5 7 11 13]
// 截取切片使其长度为 0
s = s[:0]   // len=0 cap=6 []
// 拓展其长度
s = s[:4]   // len=4 cap=6 [2 3 5 7]
// 舍弃前两个值
s = s[2:]   // len=2 cap=4 [5 7]
// 非法操作,切片没法扩展容量超过底层的数组
s = s[:8]
```

* 通过`append`向**切片**中追加元素，当底层数组空间不够时，将自动新建足够大的数组

```Go
var a [4]int
var s []int = a[0:2]    // len=2 cap=4 [0 0]

s = append(s, 0)        // len=3 cap=4 [0 0 0]
s = append(s, 1)        // len=4 cap=4 [0 0 0 1]
s = append(s, 2, 3, 4)  // len=7 cap=8 [0 0 0 1 2 3 4]
```

### Map 映射

* map的默认初始值为nil，即无法添加key

```Go
type Vertex struct {
    Lat, Long float64
}

// 以下为Map<String, Vertex>格式的map

// 创建空map：make(map[key-type]value-type)
var m map[string]Vertex
m = make(map[string]Vertex)

// 创建并初始化：
var m = map[string]Vertex{
    "Bell Labs": Vertex{
        40.68433, -74.39967,
    },
    // Vertex类型名可以省略
    "Google": {
        37.42202, -122.08408,
    },
}

// 插入/修改元素
m["Bell Labs"] = Vertex{
    40.68433, -74.39967,
}

// 删除元素
delete(m, "Bell")

// 获取元素，若key不存在，则返回对应元素类型的默认初始值
elem = m[key]
// ok为bool型，表示key是否存在
elem, ok = m[key]
```

### Range 遍历

* 一般与for配合，可以变量map、array、slice、string等

```Go
var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}
for index, value := range pow {
    fmt.Printf("%d: %d\n", index, value)
}

// 还有几种省略用法

for index := range pow {
    fmt.Printf("%d\n", index)
}

for _, value := range pow {
    fmt.Printf("%d\n", value)
}

for index, _ := range pow {
    fmt.Printf("%d\n", index)
}
```

## 提升

### 值传递和引用传递

* 本质上，所有类型的赋值、传参操作都是**值传递**，即内容复制

* 但从效果上看，如下类型可以达到**引用传递**的效果
    * ptr，本身是值传递，但是指向的内存地址不变，达到了引用的效果
    * slice，包含底层数组的指针，所以数据本身达到了引用效果，但
    * map，与slice类似
    * channel, 与slice类似
    * function，本质就是函数指针

### 函数值(指针)

* 函数本身也是一种值，可以赋值给变量，可以作为其他函数的参数或者返回值

```Go
import (
    "fmt"
    "math"
)

func compute(fn func(float64, float64) float64) float64 {
    return fn(3, 4)
}

func main() {
    hypot := func(x, y float64) float64 {
        return math.Sqrt(x*x + y*y)
    }
    fmt.Println(hypot(5, 12))

    fmt.Println(compute(hypot))
    fmt.Println(compute(math.Pow))
}
```

* 函数闭包：以下示例`adder`返回一个闭包，这些闭包都有各自的`sum`

```Go
import "fmt"

func adder() func(int) int {
    sum := 0
    return func(x int) int {
        sum += x
        return sum
    }
}

func main() {
    pos, neg := adder(), adder()
    for i := 0; i < 10; i++ {
        fmt.Println(
            pos(i),
            neg(-2*i),
        )
    }
}
```

### 函数接收者

* Go只有结构体，没有类，但可以通过`带接收者的函数`来给结构体定义方法

    ```Go
    type Vertex struct {
        X, Y float64
    }

    func (v Vertex) Abs() float64 {
        return math.Sqrt(v.X*v.X + v.Y*v.Y)
    }

    func main() {
        v := Vertex{3, 4}
        fmt.Println(v.Abs())
    }
    ```

* 还可以为非结构体类型设置接收者，但该类型不能是**基础类型、其他包定义的类型**

    ```Go
    type MyFloat float64

    func (f MyFloat) Abs() float64 {
        if f < 0 {
            return float64(-f)
        }
        return float64(f)
    }

    func main() {
        f := MyFloat(-math.Sqrt2)
        fmt.Println(f.Abs())
    }
    ```

* 类型T的接收者和*T的接收者调用方法一致

    ```Go
    type Vertex struct {
        X, Y float64
    }

    func (v *Vertex) Scale(f float64) {
        v.X = v.X * f
        v.Y = v.Y * f
    }

    func (v Vertex) Abs() float64 {
        return math.Sqrt(v.X*v.X + v.Y*v.Y)
    }

    func main() {
        v := Vertex{3, 4}
        v.Scale(2)
        fmt.Println(v.Abs())

        p := &Vertex{4, 3}
        p.Scale(3)
        fmt.Println(p.Abs())
    }
    ```

### 接口

#### 定义和实现

类型只要实现接口的方法，无需像C++/Java一样显示`implements`

```Go
type Abser interface {
    Abs() float64
}

type MyFloat float64

func (f MyFloat) Abs() float64 {
    if f < 0 {
        return float64(-f)
    }
    return float64(f)
}

type Vertex struct {
    X, Y float64
}

func (v *Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    var a Abser
    f := MyFloat(-math.Sqrt2)
    v := Vertex{3, 4}

    a = f  // MyFloat 实现了 Abser
    a = &v // *Vertex 实现了 Abser

    // 但Vertex没有实现 Abser，所以这样是错误的
    // a = v

    fmt.Println(a.Abs())
}
```

#### 接口的值

接口的值可以简单看作所指向目标的值和类型：(value, type)

```Go
type I interface {
    M()
}

type T struct {
    S string
}

func (t *T) M() {
    fmt.Println(t.S)
}

func main() {
    var i I
    i = &T{"Hello"} // (&{Hello}, *main.T)
    i.M()
}
```

#### 空接口

没有申明任何方法的接口(interface{})叫做空接口，可以指向任何类型，类似与`void *`

#### 类型断言

通过类型断言i.(T)，可以访问接口所保存的值和类型

```Go
var i interface{} = "hello"

s := i.(string)
fmt.Println(s)  // hello

s, ok := i.(string)
fmt.Println(s, ok)  // hello true

f, ok := i.(float64)
fmt.Println(f, ok)  // 0 false

f = i.(float64) // 报错(panic)
fmt.Println(f)

var v *int
i = v
ii, ok := i.(*int)
fmt.Println(ii, ok) // <nil> true
```

#### 类型选择

 Go定义了**多类型断言**的特殊结构，用于快速判断类型

```Go
switch v := i.(type) {  // 此行固定，v为接口i保持的目标
case int:
    fmt.Printf("Twice %v is %v\n", v, v*2) 
case string:
    fmt.Printf("%q is %v bytes long\n", v, len(v))
default:
    fmt.Printf("I don't know about type %T!\n", v) 
}
```

* 接口可以指向一个T类型但值为nil的目标，且允许执行接口的方法，但需要在方法内部手动检查接收者的有效性，具体参见[底层值为 nil 的接口值](https://tour.go-zh.org/methods/12)

#### fmt.Stringer接口

fmt包中定义的 Stringer 接口，常用于输出变量的字符串化值，类似与Java中的`toString`

```Go
import "fmt"

type Person struct {
    Name string
    Age  int
}

func (p Person) String() string {
    return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

func main() {
    a := Person{"Arthur Dent", 42}
    fmt.Printf("%T, %v\n", a, a)  // main.Person, Arthur Dent (42 years)
    z := Person{"Zaphod Beeblebrox", 9001}
    fmt.Println(z) // Zaphod Beeblebrox (9001 years)
}
```

#### error接口

内建了error接口，print时也会调用其输出错误信息

```Go
type error interface {
    Error() string
}
```

#### io.Reader接口

* io 包指定了 io.Reader 接口，其包含了一个Read方法：`func (T) Read(b []byte) (n int, err error)`，用于从数据流的末尾进行读取。

* Go 标准库包含了该接口的许多实现，包括文件、网络连接、压缩和加密等等。

```Go
package main

import (
    "fmt"
    "io"
    "strings"
)

func main() {
    r := strings.NewReader("Hello, Reader!")

    b := make([]byte, 8)
    for {
        n, err := r.Read(b)
        fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
        fmt.Printf("b[:n] = %q\n", b[:n])
        if err == io.EOF {
            break
        }
    }
}
```

#### Image接口

image 包定义了 Image 接口：

```Go
package main

import (
    "fmt"
    "image"
)

func main() {
    m := image.NewRGBA(image.Rect(0, 0, 100, 100))
    fmt.Println(m.Bounds())
    fmt.Println(m.At(0, 0).RGBA())
}
```

## 并发

### goroutine 协程

goroutine是Go运行时态的一种轻量级线程

```Go
func say(s string) {
    for i := 0; i < 5; i++ {
        time.Sleep(100 * time.Millisecond)
        fmt.Println(s)
    }
}

func main() {
    go say("world")
    say("hello")
}
```

### chan 信道

#### 基本

信道是带有类型的管道，你可以通过它用信道操作符 <- 来发送或者接收值；和映射与切片一样，信道在使用前必须通过`make`创建

```Go
package main

import "fmt"

func sum(s []int, c chan int) {
    sum := 0
    for _, v := range s {
        sum += v
    }
    c <- sum // 将和送入 c
}

func main() {
    s := []int{7, 2, 8, -9, 4, 0}

    c := make(chan int)
    go sum(s[:len(s)/2], c)
    go sum(s[len(s)/2:], c)
    x, y := <-c, <-c // 从 c 中接收

    fmt.Println(x, y, x+y)
}
```

#### 带缓冲的信道

* 信道可以是带缓冲的。

* 仅当信道的缓冲区填满后，向其发送数据时才会阻塞；当缓冲区为空时，接受方会阻塞。

* 可以通过`cap(ch)`获取信道的缓冲大小

```Go
ch := make(chan int, 2)
fmt.Println(cap(ch))
ch <- 1
ch <- 2
fmt.Println(<-ch)
fmt.Println(<-ch)
```

#### range 和 close

* 发送者可通过 close 关闭一个信道来表示没有需要发送的值了。接收者可以通过为接收表达式分配第二个参数来测试信道是否被关闭

* `for i := range c` 会不断从信道接收值，直到它被关闭。

* **只有发送者才能关闭信道**，而接收者不能。向一个已经关闭的信道发送数据会引发程序恐慌（panic）。

* 信道与文件不同，通常情况下无需关闭它们。只有在必须告诉接收者不再有需要发送的值时才有必要关闭，例如终止一个 range 循环。

```Go
func fibonacci(n int, c chan int) {
    x, y := 0, 1
    for i := 0; i < n; i++ {
        c <- x
        x, y = y, x+y
    }
    close(c)
}

func main() {
    c := make(chan int, 10)
    go fibonacci(cap(c), c)
    for i := range c {
        fmt.Println(i)
    }
}
```

#### select

* select 语句使一个 goroutine 可以等待多个通信操作: 会阻塞到某个分支可以继续执行为止，这时就会执行该分支; 当多个分支都准备好时会随机选择一个执行。

```Go
func fibonacci(c, quit chan int) {
    x, y := 0, 1
    for {
        select {
        case c <- x:
            x, y = y, x+y
        case <-quit:
            fmt.Println("quit")
            return
        }
    }
}

func main() {
    c := make(chan int)
    quit := make(chan int)
    go func() {
        for i := 0; i < 10; i++ {
            fmt.Println(<-c)
        }
        quit <- 0
    }()
    fibonacci(c, quit)
}
```

#### select的default

当 select 中的其它分支都没有准备好时，default 分支就会执行

```Go
package main

import (
    "fmt"
    "time"
)

func main() {
    tick := time.Tick(100 * time.Millisecond)
    boom := time.After(500 * time.Millisecond)
    for {
        select {
        case <-tick:
            fmt.Println("tick.")
        case <-boom:
            fmt.Println("BOOM!")
            return
        default:
            fmt.Println("    .")
            time.Sleep(50 * time.Millisecond)
        }
    }
}
```

### 同步

通过`sync.Mutex`可以实现互斥

```Go
package main

import (
    "fmt"
    "sync"
    "time"
)

// SafeCounter 的并发使用是安全的。
type SafeCounter struct {
    v   map[string]int
    mux sync.Mutex
}

// Inc 增加给定 key 的计数器的值。
func (c *SafeCounter) Inc(key string) {
    c.mux.Lock()
    // Lock 之后同一时刻只有一个 goroutine 能访问 c.v
    c.v[key]++
    c.mux.Unlock()
}

// Value 返回给定 key 的计数器的当前值。
func (c *SafeCounter) Value(key string) int {
    c.mux.Lock()
    // Lock 之后同一时刻只有一个 goroutine 能访问 c.v
    defer c.mux.Unlock()
    return c.v[key]
}

func main() {
    c := SafeCounter{v: make(map[string]int)}
    for i := 0; i < 1000; i++ {
        go c.Inc("somekey")
    }

    time.Sleep(time.Second)
    fmt.Println(c.Value("somekey"))
}
```

## 附录

### fmt.Printf速查

更多可参见[Package fmt](https://golang.org/pkg/fmt/)

```Go
type Human struct {
    Name string
}

var people = Human{"张三"}
```

* 普通

|占位符|说明|举例|输出|
|-|-|-|-|
|%v|值的默认格式|fmt.Printf("%v\n", people)|{张三}|
|%+v|打印结构体的字段名|fmt.Printf("%+v\n", people)|{Name:张三}|
|%#v|值的Go语法格式|fmt.Printf("%#v\n",people)|main.Human{Name:"张三"}|
|%T|值的类型|fmt.Printf("%T\n",people)|main.Human|
|%%|%本身|fmt.Printf("%%\n")|%|
|%t|打印bool类型的值|fmt.Printf("%t\n", true)|true|
|%p|指针地址，十六进制表示，前缀 0x(可用于切片)|fmt.Printf("%p\n", &people)|0xc00009e220|
|%#p|指针地址，不带前缀 0x(可用于切片)|fmt.Printf("%#p\n", &people)|c00009e220|

* %v的默认格式
    * bool:                    %t
    * int, int8 etc.:          %d
    * uint, uint8 etc.:        %d, %#x if printed with %#v
    * float32, complex64, etc: %g
    * string:                  %s
    * chan:                    %p
    * pointer:                 %p

* 字符串/切片

|占位符|说明|举例|输出|
|-|-|-|-|
|%s|输出字符串表示（string类型或[]byte)|fmt.Printf("%s\n", []byte("oldboy"))|oldboy|
|%10s|输出字符串最小宽度为10(右对齐)|fmt.Printf("%10s\n", "oldboy")|&nbsp;&nbsp;&nbsp;&nbsp;oldboy|
|%-10s|输出字符串最小宽度为10(左对齐)|fmt.Printf("%-10s\n", "oldboy")|oldboy&nbsp;&nbsp;&nbsp;&nbsp;|
|%.5s|输出字符串最大宽度为5|fmt.Printf("%.5s\n", "oldboy")|oldbo|
|%5.10s|输出字符串最小宽度为5，最大宽度为10|fmt.Printf("%5.10s\n", "oldboy")|oldboy|
|%-5.10s|输出字符串最小宽度为5，最大宽度为10(左对齐)|fmt.Printf("%-5.10s\n", "oldboy")|oldboy|
|%5.3s|输出字符串宽度为5,如果原字符串宽度大于3,则截断|fmt.Printf("%5.3s\n", "oldboy")|&nbsp;&nbsp;old|
|%010s|如果宽度小于10，就会在字符串前面补零|fmt.Printf("%010s\n", "oldboy")|0000oldboy|
|<B>%q|双引号围绕的字符串，由Go语法安全地转义|fmt.Printf("%q\n", "oldboy")|"oldboy"|
|%x|十六进制，小写字母，每字节两个字符|fmt.Printf("%x\n", "oldboy")|6f6c64626f79|
|%X|十六进制，大写字母，每字节两个字符|fmt.Printf("%X\n", "oldboy")|6F6C64626F79|

* 整数

|占位符|说明|举例|输出|
|-|-|-|-|
|%b|二进制表示|fmt.Printf("%b\n", 5)|101|
|%o|八进制表示|fmt.Printf("%o\n", 10)|12|
|%O|八进制表示，0o开头|fmt.Printf("%O\n", 10)|0o12|
|%d|十进制表示|fmt.Printf("%d\n", 0x12)|18|
|%x|十六进制表示(小写)(可用于浮点)|fmt.Printf("%x\n", 13)|d|
|%X|十六进制表示(大写)(可用于浮点)|fmt.Printf("%X\n", 13)|D|
|%c|相应Unicode码点所表示的字符|fmt.Printf("%c\n", 0x4E2D)|中|
|<b>%q|单引号围绕的字符字面值，由Go语法安全地转义|fmt.Printf("%q\n", 0x4E2D)|'中'|
|%U| Unicode格式：U+1234，等同于 "U+%04X"|fmt.Printf("%U\n", 0x4E2D)|U+4E2D|

* 浮点数

|占位符|说明|举例|输出|
|-|-|-|-|
|%e|6位小数点,科学计数法(小写),|fmt.Printf("%e\n", 10.2)|1.020000e+01|
|%E|6位小数点,科学计数法(大写)|fmt.Printf("%E\n", 10.2)|1.020000E+01|
|%f %F|6位小数点,无指数|fmt.Printf("%f\n", 10.2)|10.200000|
|%g|根据情况选择 %e 或 %f 以产生更紧凑的（无末尾的0）输出|fmt.Printf("%g\n", 10.20)|10.2|
|%G|根据情况选择 %E 或 %f 以产生更紧凑的（无末尾的0）输出|fmt.Printf("%G\n", 10.20+2i)|(10.2+2i)|
