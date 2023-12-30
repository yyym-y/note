# Codeforces Round 860 (Div. 2) -C



[网址](https://codeforces.com/contest/1798/problem/C)

我们考虑，如果某一些物品可以归类，那么需要满足一些什么性质：

我们先假设这一堆位置都可以被打上 $Price$ 的标签 ，第 $i$ 个物品的单价是 $b_i$ ，个数是 $a_i$ ，要满足袋子价值是 $Price$ 时，袋子里面的个数为 $d_i$ 

我们可以轻松得出来： 
$$
Price = b_i \times d_i
$$
对可以归为一类得所有物品都有：
$$
Price = b_i\times d_i = b_{i+1} \times d_{i+1} = \dots = b_j \times d_j
$$
所以我们可以轻松的得出来：
$$
Price\quad \%\quad\mathrm{ lcm(b_i, b_{i+1}, \dots,b_j)}   \quad = 0
$$
又想着通过 $d_i$ 来获取另一个关系式，那么我们尝试做一些变换：

> $a_i = K d_i$
>
> $a_i \times b_i = Kd_i \times b_i$
>
> $a_i \times b_i = K \times Price$

所以可以推出：
$$
a_i \times b_i \quad \% \quad Price \quad = 0
$$
推广到全体，我们可以得出：
$$
\mathrm{gcd(a_i\times b_i , a_{i+1} \times b_{i+1}, \dots, a_j \times b_j)} \quad \% \quad Price \quad = 0
$$
那么通过和前面得到的式子结合，可以得到一下关系式：
$$
\mathrm{gcd(a_i\times b_i , a_{i+1} \times b_{i+1}, \dots, a_j \times b_j)} \quad \% \quad \mathrm{ lcm(b_i, b_{i+1}, \dots,b_j)}   \quad = 0
$$
所以我们就可以通过这个式子来判断是否可以满足归为一类

所以代码为：



```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<pair<lli,lli>> arr(N);
lli __lcm(lli num1, lli num2){
    return (num1 * num2) / __gcd(num1, num2);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        for(int temp = 1 ; temp <= Length ; temp++)
            cin >> arr[temp].first >> arr[temp].second;
        lli Ans = 1LL;
        lli Gcd = arr[1].first * arr[1].second, Lcm = arr[1].second;
        for(int temp = 2 ; temp <= Length ; temp++){
            lli one = arr[temp].first * arr[temp].second, two = arr[temp].second;
            Gcd = __gcd(Gcd, one), Lcm = __lcm(Lcm, two);
            if(Gcd % Lcm == 0) continue;
            Ans++;
            Gcd = one; Lcm = two;
        }
        cout << Ans << "\n";
    }
    return 0;
}
```

