# A. Strange Birthday Party

[网址](https://codeforces.com/problemset/problem/1470/A)

**思路**

题目说了，价格已经拍好序的，所以我们只需要贪心一下，让K较大的人拿比他小的即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 3e5;
lli total_ask, people, gift;
vector<lli> index(N + 10), price(N + 10);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> people >> gift;
        for(int temp = 1 ; temp <= people ; temp++)
            cin >> index[temp];
        for(int temp = 1 ; temp <= gift ; temp++)
            cin >> price[temp];
        sort(index.begin() + 1, index.begin() + people + 1, greater<int>());
        lli Count = 1;
        for(int temp = 1 ; temp <= people ; temp++){
            if(index[temp] <= Count) break;
            index[temp] = Count++;
        }
        lli Sum = 0LL;
        for(int temp = 1 ; temp <= people ; temp++)
            Sum += price[index[temp]];
        cout << Sum << "\n";
    }
    return 0;
}
```



