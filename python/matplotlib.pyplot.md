# matplotlib.pyplot

## 前期准备工作

```py
import matplotlib.pyplot as plt
import numpy as np
import math
# 生成数据 sin 和 cos
COS, SIN = [[],[]], [[],[]]
Begin, End = -math.pi, math.pi
while Begin < End:
    COS[0].append(Begin), COS[1].append(math.cos(Begin))
    SIN[0].append(Begin), SIN[1].append(math.sin(Begin))
    Begin += 0.1
COS = np.array(COS) # 转化为np方便使用其方法
SIN = np.array(SIN)
```

## 绘图

```py
# plt.figure(figsize=(6,8), dpi=80) 设置图片大小， dpi表示分辨率，dpi越高分辨率越高
plt.figure
use = plt.gca() # 相当于取出到底要绘制哪一个图， 如果只画一张的画，不用取也行，但有多个子图则需取出
use.plot(COS[0], COS[1]), use.plot(SIN[0], SIN[1]) # 自变量	因变量
plt.show() # 将图形显示出来
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/Figure_1.png" alt="Figure_1" style="zoom:80%;" />

## 其他操作

```py
use = plt.gca()
use.plot(COS[0], COS[1], color='red', linewidth=1.0, linestyle='-.') # color设置颜色，linewidth设置线宽
use.plot(SIN[0], SIN[1], color='blue', linewidth=3.0, linestyle='-') # linestyle设置画线的样式
plt.xlim(-math.pi, math.pi) # x坐标轴的起点和端点
plt.xticks(list(range(int(-math.pi), int(math.pi + 1)))) # x轴上的标注
plt.ylim(-1,1) # 同理
plt.yticks(np.arange(-1,1.2,0.2))
# plt.savefig('name.png', dpi=80) 保存图片
plt.show()
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/2.png" alt="2" style="zoom: 80%;" />

## 一种更优的布局

```py
xmin, xmax = COS[0].min(), COS[0].max()
ymin, ymax = COS[1].min(), COS[1].max()
dx, dy = (xmax - xmin) * 0.1, (ymax - ymin) * 0.1
plt.xlim(-math.pi - dx, math.pi + dx)
plt.xticks(list(range(int(-math.pi), int(math.pi + 1))))
plt.ylim(-1 - dy, 1 + dy)
plt.yticks(np.arange(-1,1.2,0.2))
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/3.png" alt="3" style="zoom:80%;" />

## 在坐标轴上设置标签

```py
plt.xticks([-math.pi, -math.pi/2, 0, math.pi/2, math.pi], # 可以使用Latex公式
           [r'$-\pi$', r'$-\frac{\pi}{2}$', r'$0$', r'$\frac{\pi}{2}$', r'$\pi$'])
plt.yticks([-1,-0.5,0,0.5,1]) # 也可以简单的用数字表示
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/4.png" alt="4" style="zoom:80%;" />

## 设置脊柱

```py
# 脊柱可以理解为一个图形的四个边框，一个图有四个边框
use.spines['top'].set_color('none') # 把最顶上的脊柱隐藏掉
use.spines['right'].set_color('none')
use.spines['bottom'].set_position(('data', 0)) # 设置其他脊柱的位置
use.spines['left'].set_position(('data', 0))
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/5.png" alt="5" style="zoom:80%;" />

## 添加图例

```py
use.plot(COS[0], COS[1], color='red', linewidth=1.0, linestyle='-.', label='cos(x)') #label是要标注的信息
use.plot(SIN[0], SIN[1], color='blue', linewidth=3.0, linestyle='-', label='sin(x)')
plt.legend(loc='upper left') # 设置方位
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/6.png" alt="6" style="zoom:80%;" />

## 特殊点标记

```py
point1 = (2/3)*math.pi
plt.scatter([point1],[math.cos(point1)], 50, color='black') # 绘制标注点
plt.plot([0,point1], [math.cos(point1), math.cos(point1)], # 辅助线1
         linewidth='1.0', linestyle='--',color='black')
use.plot([point1,point1], [0, math.cos(point1)], # 辅助线2
         linewidth='1.0', linestyle='--', color='black')
plt.annotate(r'$(\frac{2\pi}{3}, -\frac{1}{2})$', xy=(point1, math.cos(point1)), # 绘制标注， xy表示指示点坐标
             xytext=(point1 - 1.5, math.cos(point1) - 0.3), fontsize=13, # xytext表示标注所在坐标
             arrowprops=dict(arrowstyle='->', connectionstyle="arc3,rad=.2")) # 指向箭头的样式
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/7.png" alt="7" style="zoom:80%;" />

## 标签美化

```py
use.plot(COS[0], COS[1], color='red', linewidth=1.0, linestyle='-.', label='cos(x)', zorder=1)
use.plot(SIN[0], SIN[1], color='blue', linewidth=3.0, linestyle='-', label='sin(x)', zorder=1)
# zorder表示图层循序，zonder越小越底层
for label in use.get_xticklabels() + use.get_yticklabels():
    label.set_bbox(dict(facecolor='white', edgecolor='none', alpha=0.65)) # 加入雾化效果
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/8.png" alt="8" style="zoom:80%;" />

## 其他类型图

### 散点图

```py
import matplotlib.pyplot as plt
import numpy as np
import random
Point = [[], [], [], []]
COLOR = ['red', 'black', 'pink', 'yellow', 'green', 'purple']
for times_ in range(1000):
    Point[0].append(random.uniform(0, 100))
    Point[1].append(random.uniform(0, 100))
    Point[2].append(random.uniform(10,50))
    Point[3].append(random.choice(COLOR))
plt.scatter(Point[0], Point[1], Point[2], color=Point[3])
plt.show()
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/9.png" alt="9" style="zoom:80%;" />

### 饼状图

```py
import matplotlib.pyplot as plt
import random
DIV = []
for times_ in range(15):
    DIV.append(random.random())
plt.pie(DIV)
plt.show()
```

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/74.png" alt="74" style="zoom:80%;" />