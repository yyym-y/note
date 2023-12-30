# Codeforces Round 861 (Div. 2)

## B. Playing in a Casino

首先我们可以对所有元素进行排序，因为是任意两个数相减之后排序，所以排序并不会改变最终结果

因为是对每一列进行操作，所以我们可以把输入的数据颠倒一下，让每一列的数据都在一个 `vector` 里

我们将数据从大到小进行排序，这样就可以避免相减变成负数，也就可以将绝对值去掉。

我们先假设 $n = 4$ ， 那么这一列的数据是 : $a_1 , a_2, a_3, a_4$

我们将过程写出来，注意这个时候可以将绝对值去掉了
$$
(a_1 - a_2) + (a_1 - a_3) + (a_1 - a_4) + (a_2 - a_3) + (a_2 - a_4) + (a_3 - a_4)
$$
稍微变个形得：
$$
a_1 \times 3 + a_2 \times 1 + a_3 \times (-1) + a_4 \times (-3)
$$
所以我们只需要知道后面乘得数是多少即可

不难想到？ 对于第 $i$ 个数，他前面有 $i - 1$ 个数，这些数会减去它，后面有 $n - i + 1$ 个数，这些数是被它减去的

所以乘的数为 ： $n - i + 1 - (i - 1) = n + 1 - 2i$  

注： 使用减号是应为 $i-1$ 是被减去，所以要用减号

这样，这题目就结束了

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, vertical, level;
vector<lli> arr(N);
bool cmp(lli a, lli b) {return a > b;}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> vertical >> level;
        vector<vector<lli>> info(vertical + 10, vector<lli>(level + 10));
        for(int temp = 1 ; temp <= vertical ; temp++){
            for(int temp2 = 1 ; temp2 <= level ; temp2++)
                cin >> info[temp][temp2];
        }
        if(vertical == 1) {cout << "0\n"; continue;}
        vector<vector<lli>> Use(level + 10, vector<lli>(vertical + 10));
        for(int temp = 1 ; temp <= level ; temp++){
            for(int temp2 = 1 ; temp2 <= vertical ; temp2++)
                Use[temp][temp2] = info[temp2][temp];
            sort(Use[temp].begin() + 1, Use[temp].begin() + vertical + 1, cmp);
        }
        lli ans = 0LL;
        for(int temp = 1 ; temp <= level ; temp++){
            for(int temp2 = 1 ; temp2 <= vertical ; temp2++)
                ans += Use[temp][temp2] * (vertical + 1 - 2*temp2);
        }
        cout << ans << "\n";
    }
    return 0;
}
```



**比赛时的代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, vertical, level;
vector<lli> arr(N);
bool cmp(lli a, lli b) {return a > b;}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> vertical >> level;
        vector<vector<lli>> info(vertical + 10, vector<lli>(level + 10));
        for(int temp = 1 ; temp <= vertical ; temp++){
            for(int temp2 = 1 ; temp2 <= level ; temp2++)
                cin >> info[temp][temp2];
        }
        if(vertical == 1) {cout << "0\n"; continue;}
        vector<vector<lli>> Use(level + 10, vector<lli>(vertical + 10));
        for(int temp = 1 ; temp <= level ; temp++){
            for(int temp2 = 1 ; temp2 <= vertical ; temp2++)
                Use[temp][temp2] = info[temp2][temp];
            sort(Use[temp].begin() + 1, Use[temp].begin() + vertical + 1, cmp);
        }
        lli ans = 0LL;
        for(int temp = 1 ; temp <= level ; temp++){
            lli tem = 0LL;
            for(int temp2 = 2 ; temp2 <= vertical ; temp2++){
                tem += Use[temp][1] - Use[temp][temp2];
            }
            ans += tem;
            for(int temp2 = 2 ; temp2 <= vertical ; temp2++){
                lli tem2 = tem;
                tem2 -= ((Use[temp][temp2 - 1] - Use[temp][temp2]) * (vertical - temp2 + 1));
                tem = tem2;
                ans += tem;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```

