
<!-- TOC -->

- [GL APIs](#gl-apis)
    - [glVertexAttribPointer](#glvertexattribpointer)
    - [glDrawArrays](#gldrawarrays)
    - [glDrawElements](#gldrawelements)
    - [glGenTextures](#glgentextures)
    - [glBindTexture](#glbindtexture)
    - [glPixelStorei](#glpixelstorei)
    - [glReadPixels](#glreadpixels)
    - [glTexImage?D 1D/2D/3D](#glteximaged-1d2d3d)
    - [glTexSubImage?D 1D/2D/3D](#gltexsubimaged-1d2d3d)
- [EGL APIs](#egl-apis)
    - [eglMakeCurrent](#eglmakecurrent)
- [Android APIs](#android-apis)
    - [SurfaceTexture.updateTexImage](#surfacetextureupdateteximage)
- [Grafika lib](#grafika-lib)
    - [Sprite2d](#sprite2d)
    - [Matrix](#matrix)

<!-- /TOC -->

# GL APIs

* 参考[OpenGL ES 2.0 中文API](https://blog.csdn.net/flycatdeng/article/details/82588903)、zeal等

## glVertexAttribPointer

```Java
/**
* 设置顶点属性
*
* @param indx: 顶点属性索引(ID/别名)，常用属性：位置、纹理坐标、法向量、颜色等等
* @param size: 每个顶点属性需要关联的分量个数(必须为1、2、3或者4。初始值为4。) ；即属性的size
* @param type: 数组元素类型：GL_BYTE/GL_UNSIGNED_BYTE/GL_SHORT/GL_UNSIGNED_SHORT/GL_INT/GL_UNSIGNED_INT/GL_FLOAT/GL_DOUBLE,默认值GL_FLOAT
* @param normalized: 是否需要规范化fixed-point data
* @param stride: 顶点属性间的偏移量，若单一属性则可以为0，若类似AAABBAAABB这样多属性存一个数组中时，则为5*(bytes of type)
* @param ptr: 顶点数据
*/
public static void glVertexAttribPointer(
        int indx,
        int size,
        int type,
        boolean normalized,
        int stride,
        java.nio.Buffer ptr
    );
```

## glDrawArrays

```C
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
```

* 根据之前输入的顶点数组来渲染图元，参数说明
    * mode，图元类型和构造方式，假设顶点数组中有A、B、C、D、E、F顺序的6个点
        |参数|图元|作用|示例|
        |-|-|-|-|
        |GL_POINTS|点|绘制独立的点|A、B、C、D、E、F|
        |GL_LINES|线段|每2个点构成一条线段|AB、CD、EF|
        |GL_LINE_LOOP|线段|按顺序将所有的点连接起来，包括首位相连|AB、BC、CD、DE、EF、FA|
        |GL_LINE_STRIP|线段|按顺序将所有的点连接起来，不包括首位相连|AB、BC、CD、DE、EF|
        |GL_TRIANGLES|三角形|每3个点构成一个三角形|ABC、DEF|
        |GL_TRIANGLE_STRIP|三角形|相邻3个点构成一个三角形,不包括首位两个点|ABC、BCD、CDE、DEF|
        |GL_TRIANGLE_FAN|三角形|第一个点和之后所有相邻的2个点构成一个三角形|ABC、ACD、ADE、AEF|
    * first，顶点数组的起始索引
    * count，从顶点数组中读取的顶点数量

* 通过该方法可以用更少的调用绘制多种图元：可以预先(`glVertexAttribPointer`)为顶点、线条和颜色指定各自数组，然后只需要调用一次draw就可以构造出图元序列（否则渲染时需要多次调用GL方法分别传递顶点、线条、纹理坐标、边缘标志或颜色等数据）

* 调用此方法之前，需要调用`glEnableVertexAttribArray`启用顶点属性数组（否则将不会生成图元）并通过`glVertexAttribPointer`设置顶点属性数组

* `glDrawArrays`执行结束后，被其修改的顶点属性将变成未指定状态，反之将保留当前值

* `glDrawArrays`会加入到**显示列表(Display list)**，且只要加入，其必要的（由上述enable和pointer指定的）数组数据和enable状态也会加入到显示列表中：*因为这些数据是client-side的状态，display list创建时就已经加入，而不是执行的时候*

## glDrawElements

```JAVA
/**
* 顶点索引法画元素
*
* @param mode: 图形绘制方式，同glDrawArrays的mode
* @param count: 绘制的顶点数
* @param type: 索引(indices)的数据格式，GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT
* @param indices: 顶点索引数组
*/
public static native void glDrawElements(
    int mode,
    int count,
    int type,
    java.nio.Buffer indices
);
```

## glGenTextures

```C
void glGenTextures(	GLsizei  	n,
 	GLuint *  	textures);
```

* 生成texture列表

## glBindTexture

```C
void glBindTexture(GLenum target, GLuint texture);
```

* 将指定的texture name（id）绑定到指定的texturing target上
* 这种绑定关系可以理解为target是所绑定texture的一个别名
* target为：(GL_TEXTURE_1D/GL_TEXTURE_2D/GL_TEXTURE_3D/GL_TEXTURE_CUBE_MAP)
* 之前的绑定关系将自动解除
* 0号texture name为系统保留，表示GL初始化时的默认texture
* 对于当前渲染context，texture name和其内容是共享的，*因为他们共享显示列表；同样只有共享显示列表的两个context才能共享texture*
* *通过`glGenTextures`生成的texture是空的*,只有当这个texture第一次绑定时,将会设置为对应target的默认texture的状态,比如一个texture初次绑定到`GL_TEXTURE_2D` target，那么这个texture就会成为一个2d texture，且状态为GL初始化时的默认2d texture状态
* *texturing target理解为纹理类型，在一个context中每个target同时只会有一个绑定的texture name*
* 有两种方式可以解除绑定关系：1）target绑定其他texture；2）调用`glDeleteTextures`
* 一个texture可以重复多次绑定到**同一个**target上，而且通常`glBindTexture`会比`glTexImage?D`加载texture image快很多（此外通过`glPrioritizeTextures`可以更好的控制性能）

## glPixelStorei

* 设置像素存储模式，会影响后续操作
    * GL_PACK_ALIGNMENT：影响像素（从帧缓冲区）到内存的打包方式（`glReadPixels`）
        * 指定内存中每个像素行开头的对齐要求。允许值为1（字节对齐），2（行与偶数字节对齐），4（字对齐）和8（行从双字边界开始），0（不对齐）；默认为4
    * GL_UNPACK_ALIGNMENT：影响从内存解压像素的方式（`glTexImage2D/glTexSubImage2D`）
        * 指定内存中每个像素行开头的对齐要求，取值同上

## glReadPixels

* 从帧缓冲区中读取一个像素块（到内存）

## glTexImage?D (1D/2D/3D)

* 从内存加载（解压）一个texture image到texture

## glTexSubImage?D (1D/2D/3D)

* 从内存加载（解压）一个texture image到texture的指定偏移位置

# EGL APIs

## eglMakeCurrent

```Java
    public static native boolean eglMakeCurrent(
        EGLDisplay dpy,
        EGLSurface draw,
        EGLSurface read,
        EGLContext ctx
    );
```

* 指定渲染线程当前使用的context、display和渲染/显示surface


# Android APIs

## SurfaceTexture.updateTexImage

* 从Image流中更新最新的一帧texture

# Grafika lib

## Sprite2d

* 2D对象基本类，包含位置, 大小, 旋转, 平面阴影颜色等.

## Matrix

* orthoM：计算/生成`正交投影`矩阵

```Java
    /**
     * Computes an orthographic projection matrix.
     *
     * @param m：返回的矩阵
     * @param mOffset：结果矩阵起始的偏移量
     * @param left：x的最小值
     * @param right：x的最大值
     * @param bottom：y的最小值
     * @param top：y的最大值
     * @param near：z的最小值
     * @param far：z的最大值
     */
    public static void orthoM(float[] m, int mOffset,
        float left, float right, float bottom, float top,
        float near, float far);
```