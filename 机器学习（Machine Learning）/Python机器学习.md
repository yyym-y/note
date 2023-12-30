## 数据预测于预测建模

### 回归预测模型

**回归预测模型常规形式**
$$
y = \beta_0 + \beta_1X_1 + \beta_2X_2+\cdots+\beta_pX_p + \varepsilon 
$$
其中 $y$ 为输出变量，即经过这个模型后输出的结果

$X_i$ 表示有多少个变量，比如对于一个房子销售问题，$X_i$ 可能就是房子的面积，地段等等可能的影响

$\beta_i$ 表示回归系数，可以理解为某个影响的程度，越大影响的程度越大

$\varepsilon$ 表示随机误差，即那些无可预料的事情带来的影响或者模型没有考虑的情况带来的影响

我们可以那上述的式子改写为：
$$
y = f(X) + \varepsilon
$$
$f(x)$ 表示真实情况下各个情况的实际拟合，我们是不能知道的

但是我们可以求出$f(x)$ 的预测值 $\hat{f}(x)$

所以最终回归预测所求出的模型为：
$$
y = \hat{f}(X) + \varepsilon
$$

### 分类预测模型

我们先介绍适合于 $0$ , $1$ 分类的模型： $Logistic$ 模型,  形式如下：
$$
\ln(\frac{P}{1-P}) = \beta_0 + \beta_1X_1 + \beta_2X_2 + \cdots + \beta_pX_p + \varepsilon
$$
$P$ 为类别取 $1$ 的概率

与上同理：我们用 $f(x)$ 表示：
$$
\ln(\frac{P}{1-P}) = f(x) + \varepsilon
$$
我们约定函数 $\exp(x)$ 为 $e^x$ ，然后我们可以通过上式推出 $P$ 的表达式：
$$
P = \frac{1}{1 + \exp(-f(X))}
$$
**一些概念**

> 一般我们将 $\ln(\frac{P}{1-P})$ 称为 $LogitP$ , 意思是对 $P$ 做二元 $Logistic$ 变换
>
> 其中 $\frac{P}{1-P}$ 称为 **优势** （$odds$）
>
> 其中也可以叫 **优势比** （$OR$ ) ，意为某事发生的概率比上某事不发生的概率，利用 $OR$ 可以进行风险评估
>
> 进一步的： $OR = e^{\beta_i}$



## 损失函数

**预测建模的最终目标一般是使得损失函数最小，通常采用有监督学习**

**建模的参数一般是采用特定的搜索来完成**

> 损失函数 $L$ 是误差 $e$ 的函数， $L(e)$ 于 $e$ 成正比
>
> $e = (y_i  - \hat{y_i}) (i = 1, 2, \cdots, N)$

### 平方损失函数

这是一个常见的损失函数，适用于回归模型：
$$
L(e) = L(y_i, \hat{y_i}) = (y_i - \hat{y_i})^2
$$
对于全体数据的拟合误差也成为总损失，为:
$$
\sum_{i = 1}^NL(y_i, \hat{y_i}) = \sum_{i=1}^N(y_i - \hat{y_i})^2
$$

### 交互熵

这个好好讲讲，这个适用于分类模型

首先明白啥事熵（$Entropy$）

熵是用来形容不确定性的数学概念。，其数学定义为：
$$
Entropy = \sum -P\ln P
$$
其中的 $P$  是某一个情况的概率， 而 $Entropy$ 就是遍历所有的 $P$ ，并且按照上面的规则相加起来

我们来举一个例子，拿硬币来说：

> * 如果两面都是 花色 ，那么投掷这枚硬币，结果是肯定的，所以不确定度应该为 $0$
>   * 计算一下熵值：$P_1 = 1$ 表示 投出花色的概率， $P_2 = 0$ 表示投出数字的概率
>   * $Entropy = -1\ln 1 - 0\ln0 = 0$ (虽然最后 $\ln$ 是未定义的，但无关紧要)
> * 如果一面花色，一面数字，那么不确定度肯定不为 $0$
>   * 计算一下熵值：$P_1 = 0.5$ 表示 投出花色的概率， $P_2 = 0.5$ 表示投出数字的概率
>   * $Entropy = -0.5\ln 0.5 - 0.5\ln0.5 \ne 0$

**接下来介绍交互熵**

交叉熵是对由于实际输出的可能性与我们认为的可能性之间区别而产生不匹配，而产生的输出不确定性的一个指标。

可以理解为我们会不会为我们模型输出的结果感到震惊，交互熵就是这个震惊的程度

如果交互熵小，说明模型给出这个结果在意料之中，反之则不在，交互熵越小越好

**交互熵的数学定义**
$$
CrossEntropy = \sum -y\ln x
$$
其中 $x$ 是观测到的各分类的概率，而 $y$ 是各分类的实际概率。

交互熵的特点是：

对于非常错误的输出，交叉熵将会更大，而对正确的输出，交叉熵 将会更小

这也是可以将交叉熵用于损失函数的重要原因。

**一个更加严谨(~~复杂~~)的表达式**
$$
L(y_i, \hat{y_i}) = -\sum_{k=1}^N I(y_i = k)\ln(\hat{p_k}(X_i)) = -\ln \hat p_{y_i}(X_i)
$$
$I(\cdot)$ 为示性函数，仅有两个取值 $0$ , $1$ ，如果括号里面的条件成立，取值为 $1$ ，否则为 $0$ 

### 二项偏差损失函数

二项偏差函数是对应着只有两种分类的情况， 我们将交互熵改写：
$$
L(y_i, \hat P_k(X_i)) = -y_i\ln(\hat P(X_i) - (1-y_i)\ln(1-\hat P(X_i))
$$
我们再将之前分类预测模型的结论套在上述公式中得：
$$
\begin{cases}
	&\ln(\frac{P}{1-P}) = \beta_0 + \beta_1X_1 + \beta_2X_2 + \cdots + \beta_pX_p + \varepsilon\\\\
	&P = \frac{1}{1 + \exp(-f(X))}\\\\
	&L(y_i, \hat P_k(X_i)) = -y_i\ln(\hat P(X_i) - (1-y_i)\ln(1-\hat P(X_i))
\end{cases}
$$

$$
\Rightarrow L(y_i, \hat f(X_i)) = -y_i\hat f(X_i) + \ln[1 + \exp(\hat f(X_i))]
$$



## 模型的评价指标

### 回归模型的评价指标

对于一个回归模型，我们需要它的均方误差越小越好：

均方误差（$MSE$ ） = 总误差 / 数量
$$
MSE = \frac{1}{N} \sum_{i - 1}^N (y_1 - \hat y_i)^2
$$

### 二分类模型的评价指标

**混淆矩阵**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/99.png" alt="image-20230313103731611" style="zoom: 80%;" />

> **TP  (Ture Positive)**  实际值为 $1$ ，预测值为 $1$
>
> **FN  (False Negative)** 实际值为 $1$ ，预测值为 $0$
>
> **FP  (False Positive)** 实际值为 $0$ ，预测值为 $1$
>
> **TN  (Ture Negative)** 实际值为 $0$ ，预测值为 $0$



**一些指标**

> **总正确率** ： $\frac{TP + TN}{N}$ 		 预测正确的/总数
>
> **总错判率** ：$\frac{FN + FP}{N}$ 		  预测错误的/总数
>
> **敏感性** ：$\frac{TP}{TP + FN}$ 			  正确判断为 1 / 实际为 1 总数
>
> **特异性** ：$\frac{TN}{TN + FP}$ 			  正确判断为 0 / 实际为 0 总数
>
> * **查准率(P)** ：$\frac{TP}{TP + FP}$ 		正确判断为 1 / 被判断为 1 的数量
> * **查全率(R)** ：$\frac{TP}{TP + FN}$ 	    正确判断为 1 / 实际为 1 总数（敏感性）
>
> **TPR** ：于查全率和敏感性等价
>
> **FPR** ：$\frac{FP}{FP + TN}$  		错误检测为 1 / 实际为 0 的总数

一般情况下我们希望 $P$ 和 $R$ 都尽量大， 但不能直接满足，所以我们引入了**F1分数**



**F1分数**

F1分数是查准率和查重率的调和平均值

调和平均值也称为倒数平均数，是两者倒数的平均值得倒数
$$
Score = \frac{2\times P \times R}{P + R} = \frac{2\times TP}{N + TP - TN}
$$
如果我们想侧重在某一方面上， 我们引入概念 $\beta$

**权重 F1分数**
$$
Score^\prime = \frac{(1 + \beta^2)\times P \times R}{\beta^2 \times P + R}
$$
$\beta < 1$ 侧重于$R$ ，$\beta > 1$ 侧重于$P$ ，$\beta = 1$ ,$R$ 和 $P$ 等价，

### 多分类模型的评价指标

对于多分类，我们将其转化为双分类

* 一对一策略
  * 在 $K$ 个数据中选择两个，一个记为 $1$ , 另一个为 $0$ ，一共有 $M = C_K^2$ 个二分预测模型
* 一对多策略
  * 选择一个数据，令他为 $1$ ，剩下的全为一类，为 $0$ ，一共有 $M = K$ 个二分预测模型

我们算出 $M$ 个混淆矩阵后，可以有两种计算方式：

* 算出所有 $TP\quad FP \quad TN \quad FN$  之后取平均值 $\overline{TP} \quad\overline{FP}\quad\overline{TN}\quad \overline{FN} $, 这样的指标叫做微平均
* 计算出所有矩阵的 $P_i$ 和 $R_i$ ，然后取平均， 这种叫做宏平均 



## 模型的图形化评价指标

### ROC曲线和PR曲线

首先我们先引入一个阈值的概念：

在我们的模型中，会生成一个值，这个值是数据为 $1$ 的概率，那么我们到底如何判断这个数据到底属于哪一类呢

这就引入了阈值 $P_c$ 的概念，大于阈值的选择某个值，小于等于的选择另一个值

我们要如何确定阈值的大小呢？

如果我们选择不同的阈值，那么我们就会有不同的混淆矩阵，同时有不同的$TP\quad FP \quad TN \quad FN$ 

也有不同的 $TPR(敏感性)$ ， $FPR(假正率)$

**ROC曲线**

ROC曲线是以 $FPR$ 为横坐标， $TPR$ 为纵坐标

因为我们希望 $FPR$ 越大， $TPR$ 越小，所以 ROC值越靠近左上方的阈值越好

**PR曲线**

PR曲线是以 $R$ 为横坐标， $P$ 为纵坐标

因为我们希望 $P$ 越大， $R$ 越大，所以 PR值越靠近右上方的阈值越好

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/66.png" alt="Figure_1" style="zoom:80%;" />



[绘图代码点这里](#code1)



**复杂度对拟合程度的影响**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/kl.png" alt="kl" style="zoom: 80%;" />

[绘图代码点这里](#code2)



**MP2.5预测**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/predict2.5.png" alt="predict2.5" style="zoom:72%;" />

[绘图代码点这里](#code3)



## 代码专区

<span id='code1'>**ROC曲线和PR曲线代码**</span>

```py
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 读取数据
data = pd.read_csv("D:\MachineLearning\data\类别和概率.csv")
Label, info = data['label'], data['prob']
pos, neg = np.sum(Label == 1), np.sum(Label == 0)
InfoSort = np.sort(info)[::-1]
Index = np.argsort(info)[::-1]
NewLabel = Label[Index]
P, R, TPR, FPR = [], [], [], []
print(InfoSort.size)
for point in range(InfoSort.size):
    tem = np.sum(NewLabel[:point] == 1)
    TP, TN = tem, np.sum(NewLabel[point:] == 0)
    FP, FN = point - tem, np.sum(NewLabel[point:] == 1)
    P.append(TP/(TP + FP)), R.append(TP/(TP + FN))
    TPR.append(TP/(TP + FN)), FPR.append(FP/(FP + TN))
plt.figure(figsize=(13,5))
plt.subplot(1,2,1)
plt.plot(FPR, TPR)
plt.xlabel(r"FPR"), plt.ylabel(r"TPR")
plt.title(r"ROC")
plt.subplot(1,2,2)
plt.plot(R,P)
plt.xlabel(r"R"), plt.ylabel(r"P")
plt.title(r"P-R")
plt.show()
```



<span id='code2'>**不同复杂度对拟合程度的影响**</span>

```py
import numpy as np
import pandas as pd
import math
import random
import matplotlib.pyplot as plt
import sklearn.linear_model as LM
plt.rcParams['font.sans-serif'] = ['SimHei']
# 生成实际数字
N = 200
x, y, z = np.linspace(0.1,10,N), [], []
for index in range(N):
    i = x[index]
    y.append(10*np.math.cos(i) + 15*np.math.log(i) + 20*np.math.cos(i))
    z.append(y[index] + random.uniform(-3,3))
plt.figure(figsize=(12,4))
plt.subplot(1,2,1)
plt.plot(x,y, color='black', label='真实情况')
plt.scatter(x,z,5,label='真实分布点')
# 训练模型
modulLR = LM.LinearRegression()
X = x.reshape(N,1)
Y = np.array(z)
style = ["--", "-.", ":", "-"]
color = ["blue", "purple", "red", "green"]
modulLR.fit(X, Y)
MSE_train = [np.sum((Y - modulLR.predict(X))**2) / N]
for index in range(1, 5):
    tem = pow(x, index + 1).reshape(N, 1)
    X = np.hstack((X, tem))
    modulLR.fit(X,Y)
    plt.plot(x, modulLR.predict(X),
             linestyle=style[index - 1], color=color[index-1], label=str(index + 1) + "项式")
    MSE_train.append(np.sum((Y - modulLR.predict(X))**2) / N)
plt.legend(loc='upper left')
plt.title("真实关系和不同复杂度模型的拟合情况")
plt.xlabel("输入变量"), plt.ylabel("输出变量")
plt.subplot(1,2,2)
plt.plot([1,2,3,4,5], MSE_train, label="MSE")
plt.scatter([1,2,3,4,5], MSE_train, 20, color="black")
plt.legend(loc='upper right')
plt.ylabel("MSE"), plt.xlabel("模型复杂度"), plt.title("不同复杂度模型的训练误差")
plt.show()
```



<span id='code3'>**预测PM2.5**</span>

```c++
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sklearn.linear_model as LM
plt.rcParams['font.sans-serif'] = ['SimHei']
data = pd.read_excel('D:\\MachineLearning\\data\\data1.xlsx')
PM2, PM10 = np.array(data['PM2.5']), np.array(data['PM10'])
SO2, CO, NO2 = np.array(data['SO2']), np.array(data['CO']), np.array(data['NO2'])
alpha1, alpha2, alpha3 = SO2.reshape(-1,1), CO.reshape(-1,1), NO2.reshape(-1,1)
X = np.hstack([alpha1, alpha2, alpha3])
ModulPM2 = LM.LinearRegression()
ModulPM2.fit(X, PM2)
plt.figure(figsize=(15,7))
real, Predict = PM2, ModulPM2.predict(X)
for index in range(real.size):
    plt.plot([index,index],[real[index], Predict[index]], color='pink', linewidth=1, zorder=1)
plt.plot([0,0],[0,0], color='pink', linewidth=1, zorder=1, label='偏差量')
plt.scatter(list(range(real.size)), real, 5, color='black', label='真实值')
plt.scatter(list(range(real.size)),Predict,5, color='red', label='预测值')
plt.legend(loc='upper right')
plt.title("PM 2.5预测" + r"(SO_2, CO, NO_2)")
plt.xlabel("日期")
plt.ylabel("PM 2.5")
plt.show()
```
