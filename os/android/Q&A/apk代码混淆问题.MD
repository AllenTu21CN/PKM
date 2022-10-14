* 代码中直接`@Keep`注解，可是整个class或指定方法、成员不被混淆

* 在app工程中添加规则文件: `proguard-rules.pro`
```JAVA
// 使com.xxx.xxx包(不含子包)下的public class的名字不被混淆(内部类、成员、方法依然混淆)
-keep public class com.xxx.xxx.*

// 在上面基础上,子包也不会被混淆
-keep public class com.xxx.xxx.**

// 在上面基础上,内部public/protected的内部类、成员、方法也不会被混淆
-keep public class com.xxx.xxx.** {
  public protected *;
}
```