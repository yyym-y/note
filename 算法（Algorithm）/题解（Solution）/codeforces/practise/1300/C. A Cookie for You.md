# C. A Cookie for You

[网址](https://codeforces.com/problemset/problem/1371/C)

**思路**

可以观察到，第一种人实际上是挑多的吃，第二种人是挑少的吃

观察到，对于第一种人来说，我们只需要让饼的数量比他多即可

而对第二种人来说，需要最少的比他多

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, one, two, first, second;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> one >> two >> first >> second;
        if(second <= min(one, two)){
            if(one + two - second >= first)
                cout << "Yes\n";
            else cout << "No\n";
        }else cout << "No\n";
    }
    return 0;
}
```

