#### 题面

考虑 $a + b = c$ 的形式， 已知 $a$ 有 $A$ 个数位， $b$ 有 $B$ 个数位 ，$c$ 有 $C$ 个数位

问符合$a + b = c$ 的形式的等式有多少个？不存在输出 $-1$

#### 输入格式

第一行输入 $3$ 个数字， 代表 $A,B,C$  ， $1 \le A,B,C \le 6$ 

#### 输出格式

输出符合$a + b = c$ 的形式的等式数量，不存在输出 $-1$

#### 样例

**输入一**

```
3 3 3
```

**输出一**

```
489600
```

**输入二**

```
4 3 4
```

**输出二**

```
7605450
```





如果你对题目意思不理解，你可以看看暴力的解法，也许就会明白题意了？

```c++
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    lli Count = 0;
    for(int temp = 100 ; temp < 1000 ; temp ++){
        for(int temp2 = 100 ; temp2 < 1000 ; temp2++){
            lli num = temp + temp2;
            if(num >= 1000) Count++;
        }
    }   
    cout << Count;
    return 0;
}
```



## 题解

首先分析是否存在该情况：

首先要明白，两个数字相加最多只可能向前进一位，所以 $C$  只有可能有两个取值：
$$
C = \max(A, B) \qquad /\qquad C = \max(A,B) + 1
$$
如果不满足上述的条件，则直接输出 $-1$



当条件满足的时候，考虑 $A$ , $B$ 的大小关系以及是否会进位，由此我们可以分成下面几种情况

*  $(A = B) \and (C = \max(A, B) + 1)$  
* $(A = B) \and (C = \max(A, B))$
* $(A < B) \and (C = \max(A, B))$
* $(A < B) \and (C = \max(A, B) + 1)$



> ==$(A = B) \and (C = \max(A, B) + 1)$==

​		* 当 $A = B = 1$ 时， 发生进位的组合有下面的情况：

> $1$		$9$
>
> $2$		$8\qquad9$
>
> $3$		$7\qquad8\qquad9$
>
> $\dots$
>
> $9$		$1\qquad2\qquad3\qquad4\qquad5\qquad6\qquad7\qquad8\qquad9$

总共有 $1+2+3+\dots+9 = 45$ 种情况

​		*当 $A = B = 2$ 时

首先考虑最高位自己进位的情况，此时会有 $45\times10\times10$ 种情况

其次是由于最高位的下一位进位导致的最高位进位

此时就需要 数字 $a, b$ 的最高位之和要等于 $9$， 符合条件的有

> $1$		$8$
>
> $2$		$7$
>
> $\dots$
>
> $8$		$1$

一共有 $8$ 种情况，所以第二种情况的条件数为：$8\times 45=360$

所以总情况数为 $4500 + 360 = 4860$

​		*当 $A = B = 3$ 时

跟等于 $2$ 的分析情况类似，不过也有些特别

首先考虑最高位自己进位的情况，此时会有 $45\times100\times100$ 种情况

其次是由于最高位的下一位进位导致的最高位进位

首先数字 $a, b$ 的最高位之和要等于 $9$，符合条件的有 $8$ 种

**但是最高位的下一位发生进位的条件并非我们之前所求**

在求 $A=B=2$ 时，我们是要求最高位不能为 $0$ 的，所以我们少考虑了两种情况

即： $0\qquad9$ 和 $9\qquad 0$

所以满足最高位的下一位进位的条件数为 ：$8 \times (4860 + 45 + 45) = 39600$

所以符合情况的条件数为 $450000 + 39600 = 489600$

​		*当 $A = B = n$ 时

我们假设答案为 $a_n$ , 那么总结分析我们可以得到下面的答案
$$
\begin{cases}
a_n = 45\cdot10^{2(n-1)} + 8\times b_{n-1}\qquad (n\ge 1)\\\\
b_n = a_n + 2\cdot b_{n-1}\qquad (n\ge 1)\\\\
a_0 = b_0 = 0
\end{cases}
$$


> ==$(A = B) \and (C = \max(A, B))$==

不进位的情况比较简单，可以转化为 $(全部情况 - 进位情况)$

 当 $A = B = n$ 时

全部情况为 $9 \times9 \times 10^{2(n-1)}$

 所以最终答案就是 ： $81\times10^{2(n-1)} - a_n$



> ==$(A < B) \and (C = \max(A, B) + 1)$==

如果要发生进位，那么实际情况一定长成：

> $99999\dots$
>
> $\:\:\:\:\:\:\:\:\:\:\:\:\dots$

其中 $\dots$ 的长度为 $\min(A, B)$ , 所以实际问题又转化为 $A = B = \min(A,B)$ 的情况进位的情况

不过这个时候最高位是可以为 $0$ 的，所以答案实际上是 :  $b_{\min(A,B)} - b_{\min(A,B) - 1}$



> ==$(A < B) \and (C = \max(A, B))$==

同理 ： 可以转化为 $(全部情况 - 进位情况)$

所以答案为 ：

$81\times 10^{A-1}\times10^{B-1} - (b_{\min(A,B)} - b_{\min(A,B) - 1})$





