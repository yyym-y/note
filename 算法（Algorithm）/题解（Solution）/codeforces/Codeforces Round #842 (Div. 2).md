# Codeforces Round #842 (Div. 2)

[网址](https://codeforces.com/contest/1768)

## A. Greatest Convex

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106123156339.png" alt="image-20230106123156339" style="zoom:80%;" />

**题目大意**

给你一个整数 $k$ ，已知 $x \in [1,k)$ ， 问最大的 $x$ 使 $x! + (x - 1)!$ 可以被 $k$ 整除



**思路/证明**

我们将 $x! + (x + 1)!$ 化简得：
$$
x! + (x - 1)!\\
\begin{align}
	& = 1\times2\times3\times\dots\times x + 1\times2\times3\times\dots\times(x-1)\\
	& = (x+1)\times (1\times2\times3\times\dots\times (x-1))
\end{align}
$$
将 $(x+1)\times (1\times2\times3\times\dots\times (x-1))$ 除于 k

因为$x \in [1,k)$ ， 所以$x+1 \in [2,k]$ , 当 $(x+1) = k$ 的时候，$(x+1)\times (1\times2\times3\times\dots\times (x-1))$ 刚好被 $k$ 整除

所以 $x$ 的最大值为 $k-1$

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli time_, give;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> time_;
    for(lli temp = 0 ; temp < time_ ; temp++){
        cin >> give;
        cout << give - 1 << "\n";
    }
    return 0;
}
```



## B. Quick Sort

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106123251747.png" alt="image-20230106123251747" style="zoom:80%;" />

**题目大意**

给你一个排列 $p = [a_1, a_2 \dots a_n]$ 和一个整数 $k$，

你可以将在排列中选取 $k(a_i,a_{i+1},a_{i+2}\dots a_{i+k})$ 个数，然后在排列p$中删掉这 $k$个数，再将这$k$个数按照升序排列在排列$p$的末尾

问：最少需要多少次操作可以使排列$p$按照递增的顺序排列



**思路**

假设我们现在有这样一个队列：
$$
5\quad\quad\quad\quad3\quad\quad\quad\quad1\quad\quad\quad\quad4\quad\quad\quad\quad2
$$
可以将上述操作理解为选 $k$ 个数排好序扔到队列末尾

一个队列排好序递增一定是 $1,2,3,4,\dots ,n$

所以 $1$ 必然是开头，所有$1$之前的数都将被挪到队列末尾

同理$1$到$2$之间的数也会被挪到队列末尾,$2$到$3$之间的数也会被挪到队列末尾...直至队列的末尾

这样我们就能求的需要挪动的数

我们一次可以挪动$k$个数，这样我们就可以相除算出需要的操作数了

值得注意的是，除出来的数是小数，要向上取整

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int arr[N];
int total_ask,total_num, oper, need = 0, num;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> total_num >> oper;
        for(int tem = 0 ; tem < N ; tem++) arr[tem] = 0;
        need = 0;
        for(int temp = 1 ; temp <= total_num ; temp++)
            cin >> arr[temp];
        for(int temp = 1 ; temp <= total_num ; temp++){
            if(arr[temp] == need + 1)  need++;
        }
        need = total_num - need;
        int ans = need % oper ? need / oper + 1 : need /oper;
        cout << ans << "\n";
    }
    return 0;
}
```



## C. Elemental Decompress

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106123345448.png" alt="image-20230106123345448" style="zoom:80%;" />

**题目大意**

给你一个数组 $a_n = [a_1,a_2,a_3\dots a_n]$

问是否存在两个队列 $p$， $q$ 满足一下条件

$a_i = max(p_i , q_i) \quad i \in [0,n)$

存在输出 $p$， $q$



**思路/证明**

可以用贪心的思路求解这道题

在这个数组中，如果这个数是第一次出现，那我将它放于$p$上，即：，第二次出现则放在$q$上，即：，第三次则说明条件无法满足，应为两个排列无法出现三个一样的数

接下来，逐一扫描 $p$，$q$排列，假设这个某个排列没有被赋上值，那么根据贪心的思想，选取一个最接近已选数的填上

即： $p[i] = 6$ ,那么$q[i]$将在可选范围内选出一个最接近$p[i]$的数，如果找不到就说明条件无法成立

注：可以使用set来确定可选方案，更加方便，初始化的化不要全部设为0，即循环2e5来赋值，更不要memset

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int arr[N], Judge[N], p[N], q[N];
set<int>one,two;
int total_ask, total_num;
signed main()
{
    cin >> total_ask;
    while(total_ask--){
        cin >> total_num;
        for(int temp = 1 ; temp <= total_num ; temp++){
            cin >> arr[temp];
            one.insert(temp); two.insert(temp);
            Judge[temp] = p[temp] = q[temp] = 0;
        }
        int flag = 1;
        for(int temp = 1 ; temp <= total_num ; temp++){
            Judge[arr[temp]]++;
            if(Judge[arr[temp]] == 3) {flag = 0 ; break;}
            if(Judge[arr[temp]] == 1){
                p[temp] = arr[temp];
                one.erase(arr[temp]);
            }else{
                q[temp] = arr[temp];
                two.erase(arr[temp]);
            }
        }
        if(!flag) {cout << "NO\n"; continue;}
        for(int temp = 1 ; temp <= total_num ; temp++){
            if(p[temp] && q[temp]) continue;
            if(p[temp]){
                auto re = two.upper_bound(p[temp]);
                if(re == two.begin()) {flag = 0; break;}
                re--;
                q[temp] = *re;
                two.erase(re);
            }else{
                auto re = one.upper_bound(q[temp]);
                if(re == one.begin()) {flag = 0; break;}
                re--;
                p[temp] = *re;
                one.erase(re);
            }
        }
        if(!flag) {cout << "NO\n"; continue;}
        cout << "YES\n";
        for(int temp = 1 ; temp <= total_num ; temp++)
            printf("%d%c", p[temp], " \n"[temp == total_num]);
        for(int temp = 1 ; temp <= total_num ; temp++)
            printf("%d%c", q[temp], " \n"[temp == total_num]);
    }
    return 0;
}
```



## D. Lucky Permutation

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106123527436.png" alt="image-20230106123527436" style="zoom:80%;" />

**代码**

```c++
```





## E. Partial Sorting

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106133659294.png" alt="image-20230106133659294" style="zoom:80%;" />

## F. Wonderful Jump

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230106133818963.png" alt="image-20230106133818963" style="zoom:80%;" />

