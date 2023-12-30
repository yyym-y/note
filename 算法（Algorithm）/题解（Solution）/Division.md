[1960. Division - SoCodingOJ](https://oj.socoding.cn/p/1960)

> yyym : 激动....激动.....激动.......



一般情况下，看到这种可以整除无非就几个想法： 思维，GCD， 基本算数定理

这题就考了一个基本算数定理和模板的质因数分解。



首先我们要了解什么时候 $x$ 不能被 $q$ 整除：

我们将 $q$ 进行质因数分解可以得到：
$$
q = p_1^{k_1} \cdot p_2^{k_2} \cdot p_3^{k_3} \cdots p_n^{k_n}
$$
我们将 $x$ 按照 $q$ 一样的进行质因数分解可以得到同样的形式：
$$
x = p_1^{a_1} \cdot p_2^{a_2} \cdot p_3^{a_3} \cdots p_n^{a_n}
$$
其中只需要任意的 $a_i < k_i$ ，那么 $x \bmod q \ne 0$ 

> 具体理解的话可以模拟一下除的过程，如果 $a_i < k_i$ ，那么该 $p_i$ 的次方数就会是负数，所以就不会整除



现在我们重新回归问题：

如果 $p \bmod q \ne 0$  , 那么毫无疑问答案肯定是 $p$ 

接下来就是 $p \bmod q = 0$ 的情况了，因为 $p \bmod q = 0$ ， 所以 $p$ 肯定也能化为如下形式：
$$
p = p_1^{b_1} \cdot p_2^{b_2} \cdot p_3^{b_3} \cdots p_n^{b_n}
$$
因为我们要不能被 $q$ 整除， 所以我们需要让 $a_i < k_i$

我们要寻找最大的 $x$ ， 所以我们只让一个系数的次方等于 $k_i - 1$, 其他的全部拉满就好了

之后维护一个最大值即可

**代码**（懒得写这么详细的注释） :smile:

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, Num1, Num2;
vector<lli> arr(N);
ull fast_pow(ull num, ull power){ //其实没多大用的快速幂
    ull ans = 1LL;
    while(power){
        if(power & 1) ans *= num;
        num *= num;
        power >>= 1;
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Num1 >> Num2;
        if(Num1 % Num2){ // 如果直接不能被整除
            cout << Num1 << "\n"; continue;
        }
        map<lli,lli> Info1, Info2;
        lli num1 = Num1, num2 = Num2;
        //分解质因数板子
        for(int temp = 2 ; temp * temp <= num2 ; temp++){
            while(num2 % temp == 0){
                Info1[temp] ++;
                num2 /= temp;
            }
        }
        if(num2 != 1) Info1[num2]++;
        for(auto pr : Info1){
            while(num1 % pr.first == 0){
                Info2[pr.first] ++;
                num1 /= pr.first;
            }
        }
        lli Max = INT_MIN;
        //逐一判断
        for(auto pr : Info2){
            lli div_ = pr.second - Info1[pr.first] + 1;
            lli Ans = Num1 / fast_pow(pr.first, div_);
            Max = max(Max, Ans);
        }
        cout << Max << "\n";
    }
    return 0;
}
```



注意板子细节：

>```c++
>for(int temp = 2 ; temp * temp <= num2 ; temp++){
>            while(num2 % temp == 0){
>                Info1[temp] ++;
>                num2 /= temp;
>            }
>        }
>        if(num2 != 1) Info1[num2]++;
>```
>
>是`temp*temp <= num2` ,不是 `temp < sqrt(num2)`
>
>WA了别怪我