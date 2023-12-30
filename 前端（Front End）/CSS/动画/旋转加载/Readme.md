#! https://zhuanlan.zhihu.com/p/618498640

![Image](https://pic4.zhimg.com/80/v2-f131d8d9a21b41c50fd9695a26115684.jpg)


# CSS-动画-旋转加载

想算法想的脑阔痛.......来玩点CSS娱乐一下:smile:

动画源码及来源：[192个CSS加载动画 bilibili](https://www.bilibili.com/video/BV1bS4y177dx/?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click&vd_source=8838e4a19bf1a6234c3eef010864f3cf)

emmmm......一开始看源码也看不懂，于是各大网站学习了一下，顺便把笔记附上

不会有人学CSS不想学动画吧

### 效果预览


![Image](https://pic4.zhimg.com/80/v2-c72642f731a04e1d942e555bfa81548d.gif)


### **原型代码**

> html 源代码

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=<device-width>, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet", href="one.css">
</head>
<body>
    <section>
        <div class="loader">
            <span style="--i:1"></span>
            <span style="--i:2"></span>
            <span style="--i:3"></span>
            <span style="--i:4"></span>
            <span style="--i:5"></span>
            <span style="--i:6"></span>
            <span style="--i:7"></span>
            <span style="--i:8"></span>
            <span style="--i:9"></span>
            <span style="--i:10"></span>
            <span style="--i:11"></span>
            <span style="--i:12"></span>
            <span style="--i:13"></span>
            <span style="--i:14"></span>
            <span style="--i:15"></span>
            <span style="--i:16"></span>
            <span style="--i:17"></span>
            <span style="--i:18"></span>
            <span style="--i:19"></span>
            <span style="--i:20"></span>
        </div>
    </section>
</body>
</html>
```

> css源代码

```css
*{
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}
section{
    display:flex;
    justify-content: center;
    align-items: center;
    min-height: 100vh;
    background-color: black;
    animation: animateBg 10s linear infinite;
}
@keyframes animateBg{
    0%{
        filter: hue-rotate(0deg);
    }
    100%{
        filter:hue-rotate(360deg);
    }
}
section .loader{
    position: relative;
    width:120px;
    height:120px;
}
section .loader span{
    position: absolute;
    top:0;
    left:0;
    width:100px;
    height:100px;
    transform: rotate(calc(18deg * var(--i)));
}
section .loader span::before{
    content:'';
    position: absolute;
    top: 0;
    left:0;
    width:15px;
    height:15px;
    border-radius: 50%;
    background-color: yellow;
    box-shadow: 0 0 10px yellow,
                0 0 20px yellow,
                0 0 40px yellow,
                0 0 60px yellow,
                0 0 80px yellow,
                0 0 1000px yellow;
    animation : size 2s linear infinite;
    animation-delay : calc(0.1s * var(--i));
}
@keyframes size{
    0%{
        transform: scale(1);
    }
    80%, 100%{
        transform: scale(0);
    }
}
```



### 解释：

> ```css
> section{
>     display:flex;
>     justify-content: center;
>     align-items: center;
>     min-height: 100vh;
>     background-color: black;
>     animation: animateBg 10s linear infinite;
> }
> ```
>
> `display : flex`
>
> * 弹性排序：
>
>   > **把父元素设为 flex ， 那么就可以控制里面的子元素**
>   >
>   > 如果父亲设为flex， 那么子元素的float， clear， vertical-align失效
>   >
>   > > *控制父亲*
>   >
>   > `flex-direction` : column / row
>   >
>   > 设置主轴是x轴还是y轴， 默认是x轴
>   >
>   > `justify-content` : ..... 
>   >
>   > 设置主轴子元素的排列
>   >
>   > > `flex-start` 从头开始排列
>   > >
>   > > `flex-end` 从尾部开始排列
>   > >
>   > > `center` 让元素居中排列
>   > >
>   > > `space-around` 平分剩余位置
>   > >
>   > > `space-between` 先两边贴边， 后平均分配
>   >
>   > `flex-wrap` : nowrap / wrap
>   >
>   > flex布局默认不换行，如果装不下就会缩小子元素的宽度
>   >
>   > > `nowrap` 不换行
>   > >
>   > > `wrap` 换行
>   >
>   > `align-items` ：centre.....
>   >
>   > 设置侧轴的排列方式，只能在子项为**单行**的时候使用
>   >
>   > `align-content`
>   >
>   > 于 `justify-content` 类似， 只不过是设置侧轴
>   >
>   > > *设置子元素*
>   >
>   > > `flex` ：分配子项目的剩余空间
>   >
>   > 也就是改变宽来适应屏幕和剩余面积
>   >
>   > `align-self` 
>   >
>   > 于`justify-content`  类似， 仅对自己进行排列
>   >
>   > `order`
>   >
>   > 数值越小，排列越靠前
>
> * `animation: animateBg 10s linear infinite;`
>
>   > 动画稍后讲解



> ```css
> section .loader span{
>     position: absolute;
>     top:0;
>     left:0;
>     width:100px;
>     height:100px;
>     transform: rotate(calc(18deg * var(--i)));
> }
> ```
>
> * `transform`
>
>   > `transform:translate(水平移动的距离, 垂直移动的距离)`
>   >
>   > 取值可以为 px， 也可以为百分比
>   >
>   > translate如果只给出一个值,表示x轴方向移动距离
>   >
>   > 平移还在原来的文档流，平移后的位置也可以重叠
>
>   > `transform:rotate(角度deg)`
>   >
>   > 取值正负均可 , 取值为正, 顺时针旋转 , 取值为负 , 逆时针旋转
>   >
>   > 默认原点是盒子中心
>   >
>   > transform-origin : 原点水平位置 原点垂直位置; 改变转换原点
>
>   > 以上两个分开写只生效一个，两个同时使用需使用:
>   >
>   > `transform: translate(600px) rotate(360deg);`
>
>   > `transform: scale(x轴缩放倍数,y轴缩放倍数);`
>   >
>   > 一般情况下,只为scale设置一个值,表示x轴和y轴等比例缩放
>   >
>   >  `transform:scale(缩放倍数)` 
>   >
>   > scale值大于1 表示放大  scale值小于1 表示缩小
>
>   > 其余操作遇到再说
>
> * `calc`
>
>   > CSS的计算属性
>   >
>   > $(+, -)$要求这两个数都是长度
>   >
>   > `margin: calc(100px + 100px);`
>   >
>   > 除法$(/)$要求第二个数字是无单位的
>   >
>   > `margin: calc(30px / 3);`
>   >
>   > 乘法$(*)$要求其中一个数是无单位的。
>   >
>   > `margin: calc(10px * 3);`
>
> * `var`
>
>   > **该函数用于插入 CSS 变量的值。var()**
>   >
>   > var(--name, value)
>   >
>   > 变量名称必须以两个短划线 （--） 开头，并且区分大小写！
>   >
>   > var() 的值就是style冒号后面的值



> ```css
> section .loader span::before{
>     content:'';
>     .....
> }
> ```
>
> * `::before ` /  `::after`
>
>   > 伪元素
>   >
>   > 可以再box的上面或者下面创建一个div，可以进行自定义
>   >
>   > 必须带有content属性，可以为空



> ```css
> /*animation: animateBg 10s linear infinite;*/
> @keyframes animateBg{
>     0%{
>         filter: hue-rotate(0deg);
>     }
>     100%{
>         filter:hue-rotate(360deg);
>     }
> }
> ```
>
> `animation` 常见属性
>
> > `animation-name` ：该动画的名称
> >
> > `animation-duration` ：动画持续时间
> >
> > `transition-timing-function` ：设置动画的过渡类型
> >
> > * linear：线性过渡
> > * ease：平滑过渡
> > * ease-in：由慢到快
> > * ease-out：由快到慢
> > * ease-in-out：由慢到快再到慢
> >
> > `animation-delay` ：动画的延迟时间
> >
> > `animation-iteration-count` ：设置动画的循环次数
> >
> > * infinite：无限循环
> > * number: 循环的次数（具体的数字）
>
> `@keyframes` ：设置动画关键帧
>
> `filter`
>
> * `filter: grayscale(100%);`	将图像转换为灰度图像(置灰)
> * `filter: brightness(100%)` 	把图片变得更亮或者更暗。(亮度)
> * `filter: opacity(30%); `         转化图像的透明程度
> * `filter: sepia(70%); `           将图像转换为深褐色
> * `filter: contract(50%) `           调整图像的对比度
> * `filter: blur(8px);`                给图像设置高斯模糊（近视眼） 
> * `filter: invert(30%);`               反向输出图像(反色)
> * `filter: hue-rotate(80deg); `            给图像应用色相旋转



