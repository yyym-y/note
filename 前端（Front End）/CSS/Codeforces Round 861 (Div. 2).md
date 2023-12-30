# Codeforces Round 861 (Div. 2)



### B. Playing in a Casino



**yyym说道：一边干饭一边打CF的你真的很狼狈...**

-----2023.3.30

-----

一共有 $t(1 \le t \le 1000)$ 组测试样例， 每个测试样例包含两个数 $n$ , $m$ $(m\cdot n \le 3\times10^5)$， 代表输入有 $n$ 行， 每行有 $m$ 个数

对于一个数 $\alpha_{ij} (1 \le a_{ij} \le 10^6)$ ， 它代表第 $i$ 行的第 $j$ 个数

你需要计算    $\sum\limits_{j=1}^{m}\sum\limits_{a=1}^n \sum\limits_{b = a + 1}^n |\alpha_{aj} - \alpha_{bj}|$

通俗的说， 先假设 $m = 2$ , $n = 3$

即输入为：

> $\alpha_{11} \quad \alpha_{12}$
>
> $\alpha_{21} \quad \alpha_{22}$
>
> $\alpha_{31} \quad \alpha_{32}$

你需要计算 ： $|\alpha_{11} - \alpha_{21}| + |\alpha_{11} - \alpha_{31}| + |\alpha_{21} - \alpha_{31}| +|\alpha_{12} - \alpha_{22}| + |\alpha_{22} - \alpha_{32}| + |\alpha_{12} - \alpha_{32}|$ 

