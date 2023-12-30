## 1400-C. Qpwoeirut And The City

[网址](https://codeforces.com/problemset/problem/1706/C)

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length;
const int N = 2e5;
vector<lli> arr(N + 10), dp(N + 10);
lli div_(lli one, lli two, lli there){
    lli ans = 0LL;
    lli div1 = one - two;
    if(div1 >= 0) {ans += div1 + 1; two += div1 + 1;}
    lli div2 = there - two;
    if(div2 >= 0) {ans += div2 + 1; two += div2 + 1;}
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout .tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        for(int temp = 1 ; temp <= Length ; temp++)
            cin >> arr[temp];
        dp[0] = dp[1] = dp[2] = 0LL;
        for(int temp = 3 ; temp <= Length ; temp++){
            lli need = div_(arr[temp - 2], arr[temp - 1], arr[temp]);
            if(temp & 1)
                dp[temp] = dp[temp - 2] + need;
            else
                dp[temp] = min(dp[temp - 1], dp[temp - 2] + need);
        }
        cout << dp[Length] << "\n";
    }
    return 0;
}
```

**另外一种思路**

当总数为偶数的情况下：一定有一个是可以空出来的，那我们枚举这个空位置（枚举次数不会超过$n$）

在这个空位之前肯定是偶数拔高，空位之后肯定是奇数拔高， 最后取最小值即可



## 1400-C. LIS or Reverse LIS?

[网址](https://codeforces.com/problemset/problem/1682/C)

首先如果一个排列如果是一个严格递增子序列，那么这个序列中的数只会出现一次

我们假设最后的数组在左边式递增的，右边是递减的

再给出的这个数组中，如果一个数大于二，那么就可以将这个数分配到左边和右边

如果这个数只出现过一次，这些数是可以平分为一半，一半递增，一半递减，如果合理分配，那么肯定是可以塞到原本的数组中

假设出现次数大于一的数字有 $A$ 个，出现一次的有 $B$ 个

所以最后的答案是：

$A + \left \lceil \frac{B}{2} \right \rceil$

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        map<lli,lli> Count;
        for(lli temp = 1, num ; temp <= Length ; temp++){
            cin >> num;
            Count[num]++;
        }
        lli Ans1 = 0LL, Ans2 = 0LL;
        for(auto pr : Count){
            if(pr.second >= 2) Ans1++;
            else Ans2++;
        }
        cout <<((Ans2 + 1) >> 1) + Ans1 << "\n";
    }
    return 0;
}

```

## 1400-C. Fillomino 2

能左就向左，不能就向下，恒有解

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1000;
lli total_ask, Length;
vector<vector<lli>> arr(N, vector<lli>(N));
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    //cin >> total_ask;
    total_ask = 1;
    while(total_ask--){
        cin >> Length;
        for(int temp = 1 ; temp <= Length ; temp++){
            cin >> arr[temp][temp];
        }
        for(int temp = 1 ; temp <= Length ; temp++){
            lli now_ = 1, X = temp, Y = temp;
            while(now_ < arr[temp][temp]){
                //cout << now_ << "***\n";
                if(X - 1 >= 1){
                    if(arr[Y][X-1] == 0){
                        arr[Y][X-1] = arr[temp][temp];
                        now_++;
                        X = X - 1;
                    }else{
                        arr[Y + 1][X] = arr[temp][temp];
                        now_++;
                        Y = Y + 1;
                    }
                }else{
                    arr[Y + 1][X] = arr[temp][temp];
                    now_++;
                    Y = Y + 1;
                }
            }
        }
        for(int temp = 1 ; temp <= Length ; temp++){
            for(int temp2 = 1 ; temp2 <= temp ; temp2++)
                cout << arr[temp][temp2] << " ";
            cout << "\n";
        }
    }
    return 0;
}
```



## 1500-C. Air Conditioner

[网址](https://codeforces.com/problemset/problem/1304/C)

**思路**

算出每个时间段的温度区间范围，之后取交集，看是否为空集

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, Begin;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length >> Begin;
        vector<tuple<lli,lli,lli>> info(Length + 10);
        for(int temp = 1 ; temp <= Length ; temp++)
            cin >> get<0>(info[temp]) >> get<1>(info[temp]) >> get<2>(info[temp]);
        info[0] = make_tuple(0,0,0);
        lli Left = Begin, Right = Begin, flag = 1;
        for(int temp = 1 ; temp <= Length ; temp++){
            lli tem = get<0>(info[temp]) - get<0>(info[temp - 1]);
            Left -= tem; Right += tem;
            Left = max(Left, get<1>(info[temp]));
            Right = min(Right, get<2>(info[temp]));
            if(Left > Right) {flag = 0; break;}
        }
        if(flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```



## 1500-D2. Sage's Birthday

[网址](https://codeforces.com/problemset/problem/1419/D2)

交替放置即可，把小的数放在偶数位上，大的数放在奇数位上

可能的方法：二分答案， 保证单独偶数位或奇数位都为升序或都为降序即可

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length;
    for(int temp = 1 ; temp <= Length ; temp++)
        cin >> arr[temp];
    sort(arr.begin() + 1, arr.begin() + Length + 1);
    vector<lli> ans(Length + 10);
    lli Point = 1;
    for(int temp = 2 ; temp <= Length ; temp += 2, Point++)
        ans[temp] = arr[Point];
    for(int temp = 1 ; temp <= Length ; temp += 2, Point++)
        ans[temp] = arr[Point];
    lli Num= 0LL;
    for(int temp = 2 ; temp < Length ; temp++){
        if(ans[temp] < ans[temp - 1] && ans[temp] < ans[temp + 1])
          Num++;
    }
    cout << Num << "\n";
    for(int temp = 1 ; temp <= Length ; temp++) cout << ans[temp] << " ";
    return 0;
}
```



## 1500-C. Cyclic Permutations

[网址](https://codeforces.com/problemset/problem/1391/C)



```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
const lli P = 1e9 + 7;
lli mod(lli num) {return (num % P + P) % P;}
lli total_ask, Length;
vector<lli> arr(N);
lli fast_pow(lli num, lli power){
    lli ans = 1LL; num %= P;
    while(power){
        if(power & 1) ans = mod(ans * num);
        num = mod(num * num);
        power >>= 1;
    }
    return ans;
}
lli factor(lli num){
    lli ans = 1LL;
    for(int temp = 1 ; temp <= num ; temp++){
        ans = mod(ans * temp);
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length;
    lli one = factor(Length);
    lli two = fast_pow(2, Length - 1);
    cout << mod(one - two);
    return 0;
}
```



## 1500-C. Diluc and Kaeya

[网址](https://codeforces.com/problemset/problem/1536/C)

找出最小的组合数，然后相加

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 5e5 + 10;
lli total_ask, Length;
string put;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length;
        cin >> put;
        put.insert(put.begin(), '#');
        map<pair<lli,lli>, lli> info;
        vector<lli> SumD(Length + 10, 0), SumK(Length + 10, 0);
        for(int temp = 1 ; temp <= Length ; temp++){
            if(put[temp] == 'D') SumD[temp] = SumD[temp - 1] + 1;
            else SumD[temp] = SumD[temp - 1];
            if(put[temp] == 'K') SumK[temp] = SumK[temp - 1] + 1;
            else SumK[temp] = SumK[temp - 1];
        }
        for(int temp = 1 ; temp <= Length ; temp++){
            lli one = SumD[temp], two = SumK[temp], k = __gcd(one, two);
            pair<lli,lli> index = make_pair(one/k, two/k);
            info[index] ++;
            cout << info[index] << " ";
        }
        cout << "\n";
    }
    return 0;
}
```



## 1600-A. Row GCD

[网址](https://codeforces.com/problemset/problem/1458/A)

求GCD可以使用辗转相除法
$$
\gcd(a,b) = \gcd(a, b-a) \qquad(a < b)
$$
更加推广来说：
$$
\gcd(a_1, a_2, a_3 \dots a_n) = \gcd(a_1, a_2 - a_1, a_3- a_2\dots a_n - a_{n-1})
$$

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length1, Length2;
vector<lli> arr(N), arr2(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length1 >> Length2;
    for(int temp = 1 ; temp <= Length1 ; temp++)
        cin >> arr[temp];
    for(int temp = 1 ; temp <= Length2 ; temp++)
        cin >> arr2[temp];
    if(Length1 == 1){
        for(int temp = 1 ; temp <= Length2 ; temp++)
            cout << arr[1] + arr2[temp] << " ";
        return 0;
    }
    sort(arr.begin() + 1, arr.begin() + Length1 + 1);
    lli G = arr[2] - arr[1];
    for(int temp = 3 ; temp <= Length1 ; temp++)
        G = __gcd(G, arr[temp] - arr[temp - 1]);
    for(int temp = 1 ; temp <= Length2 ; temp++){
        cout << __gcd(G, arr[1] + arr2[temp]) << " ";
    }
    return 0;
}
```



## 1500-A - Division

[1444A - Division](https://codeforces.com/problemset/problem/1444/A)



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
>       while(num2 % temp == 0){
>           Info1[temp] ++;
>           num2 /= temp;
>       }
>   }
>   if(num2 != 1) Info1[num2]++;
>```
>
>是`temp*temp <= num2` ,不是 `temp < sqrt(num2)`
>
>WA了别怪我



## 1300-C. Tiles

https://codeforces.com/problemset/problem/1178/C
$$
Ans = 4\times 2^{vertical - 1} \times 2^{level - 1}
$$


```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, vertical, level;
lli P = 998244353;
lli mod(lli n) {return (n % P + P) % P;}
vector<lli> arr(N);
lli fast_pos(lli num, lli power){
    lli ans = 1LL;
    num = mod(num);
    while(power){
        if(power & 1) ans = mod(ans * num);
        num = mod(mod(num) * mod(num));
        power >>= 1;
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> vertical >> level;
    lli Ans = mod(4*mod(fast_pos(2, vertical - 1))*mod(fast_pos(2, level - 1)));
    cout << Ans;
    return 0;
}
```

