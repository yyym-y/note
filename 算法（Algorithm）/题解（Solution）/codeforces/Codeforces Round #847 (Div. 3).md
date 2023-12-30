# Codeforces Round #847 (Div. 3)

## A. Polycarp and the Day of Pi

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128190135414.png" alt="image-20230128190135414" style="zoom:80%;" />

**题目大意**

给你一个字符串，让你判断字符串中的数字于 $\pi$ 有多少位相同的(同第一个开始算) 输入字符串不大于30



**思路/证明**

水题不解释



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
string Check = "3141592653589793238462643383279";
lli total_ask;
signed main()
{
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        string put; lli Count = 0;
        cin >> put;
        for(int temp = 0 ; temp < put.size() ; temp++){
            if(put[temp] == Check[temp]) Count++;
            else break;
        }
        cout << Count << "\n";
    }
    return 0;
}
```

## B. Taisia and Dice

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128190231751.png" alt="image-20230128190231751" style="zoom:80%;" />


**题目大意**

有 $n$ 个骰子,每个骰子从 $1$ 到 $6$ ,现在有 $n$ 个骰子，他们的和是$s$ ,现在
拿走其中最大的一个，其余的骰子之和为 $r$， 问可能的骰子结果是啥



**思路/证明**

水题，最喜欢这种输入任意一个的题了，不是贪心就是找规律，本题可以用贪心来做

我们可以求出最大值，然后贪心的选取之前的骰子即可



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, have, origin, final;
void solution(lli give, lli target, lli Max){
    if(give == 0) return;
    lli Limit = target - (give - 1);
    if(Limit > Max){
        cout << Max << " ";
        solution(give - 1, target - Max, Max);
    }else{
        cout << Limit << " ";
        solution(give - 1, target - Limit, Max);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> have >> origin >> final;
        solution(have - 1, final, origin - final);
        cout << origin - final << "\n";
    }
    return 0;
}
```


## C. Premutation

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128190342496.png" alt="image-20230128190342496" style="zoom:80%;" />


**题目大意**

给你一个长度为 $n$ 的排列 即 $p = a_1, a_2, \dots, a_i, \dots ,a_n$

现在输出给出 $n$ 次输出，第$i$输出都会将第$i$ 个数字去除

问：原本排列是什么



**思路/证明**

yysy， 还是很水，给的所有数据中只有一个第一个数字于其他不一样，那它就是排列的
开头数字，后面的就是准确的了，直接拼在一起即可



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, have;
signed main()
{
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask --){
        cin >> have;
        vector<vector<lli>> info(have + 5, vector<lli>(have + 5));
        for(int temp = 1 ; temp <= have ; temp++){
            for(int temp2 = 1 ; temp2 <= have - 1 ; temp2++)
                cin >> info[temp][temp2];
        }
        lli first = info[1][1], index = 1;
        for(int temp = 2 ; temp <= have ; temp++){
            if(info[temp][1] != first){
                if(info[temp + 1][1] == info[temp][1]) {first = info[temp][1]; break;}
                else {index = temp ; break;}
            }
        }
        cout << first << " ";
        for(int temp = 1 ; temp <= have - 1 ; temp++)
            cout << info[index][temp] << " ";
        cout << "\n";
    }
    return 0;
}
```

## D. Matryoshkas

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128190447074.png" alt="image-20230128190447074" style="zoom:80%;" />

**题目大意**

给你一串数列，问其中的连续序列有多少个



**思路/证明**

一开始尝试模拟，原本以为是$O(n)$，结果好像会大得多，超时，发现可以用堆积木的想法来实现

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128204704752.png" alt="image-20230128204704752" style="zoom:80%;" />

我们可以通过计算不同积木之间的落差来确定到底有多少个连续对

如果当前这个数字于下一个数字不连续，那么就直接加上它的数量即可

注意：我们统计的是下降过程，最后一步可以通过添加一个空项实现，具体的
计数可以用map实现

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, have;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> have;
        map<lli,lli> info;
        for(lli temp = 0 , num; temp < have ; temp++){
            cin >> num;
            info[num]++;
        }
        lli Count = 0;
        vector<pair<lli,lli>> num;
        for(auto pr : info) num.push_back(pr);
        num.push_back(make_pair(num[num.size() - 1].first + 1, 0));
        for(int temp = 0 ; temp < num.size() - 1 ; temp++){
            if(num[temp].first == num[temp + 1].first - 1){
                if(num[temp].second > num[temp + 1].second)
                    Count += num[temp].second - num[temp + 1].second;
            }
            else
                Count += num[temp].second;
        }
        cout << Count << "\n";
    }
    return 0;
}
```

## E. Vlad and a Pair of Numbers

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128190600940.png" alt="image-20230128190600940" style="zoom:80%;" />


**题目大意**

给你一个数字 $x$, 问是否存在两个数$a$, $b$ 可以使得 $x = a\oplus b = 
\frac{a + b}{2}$ , $\oplus$ 为 $XOR$

存在输出任意 $a$, $b$ ,不存在输出 $-1$

**思路/证明**

不会真的有人像我一样吧 $\oplus$ 看成 $OR$了吧，甚至还把方法想出来了，甚至代码都敲好了......

没关系，下次拿出来考别人.....

这道题最优的算法是$O(1)$的，但很可惜，我不会粗略的解释如下：

试一下a=n+n/2，b＝2n-a和2n+1-a，然后试一下a=n+n/2+1，b=2n-a和2n+1-a。如果这四种组合都不是可行解就是无解

但我没想到，当我想到了一个奇技淫巧:

首先我们将给的数和它的二倍转化为二进制

之后我们从低位向高位逐个判断：

假设num1 为 原数的二进制表示， num2 为原数乘于2的二进制表示

如果 num1的第 $i$ 位是1 ， 那么两个答案的第 $i$位一定是一个1，一个0

如果这个时候num2的第$i$位是1， 1 和 0 相加肯定也是1，所以我们可以让一个答案的第$i$位为1，另一个为0

但如果num2此时是0， 那么就需要两个答案的 $i-1$位是1，然如果此时num1 的$i-1$位是1，则无解，但我们不管它，最后再判断

同理,num1的第 $i$ 位是0时，我们在更具num2来判断

注意最后要验证一下a，b是否满足条件即可



**代码(我的奇技淫巧)**
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, give;
lli List[35];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    for(lli temp = 0, num = 1 ; temp < 35 ; temp++, num *= 2)
        List[temp] = num;
    while(total_ask --){
        cin >> give;
        if(give & 1) {cout << "-1\n"; continue;}
        vector<int> num1, num2;
        lli one = give, two = give << 1;
        for(int temp = 0 ; temp < 30 ; temp++){
            num1.push_back((one >> temp) & 1);
            num2.push_back((two >> temp) & 1);
        }
        vector<int> ans1(30,0), ans2(30,0);
        for(int temp = 1 ; temp < 30 ; temp ++){
            if(num2[temp] == 0){
                if(num1[temp] == 1){
                    ans1[temp] = 1;
                    ans1[temp - 1] = 1; ans2[temp - 1] = 1;
                }else{
                    ans1[temp] = 0; ans2[temp] = 0;
                }
            }else{
                if(num1[temp] == 1) ans1[temp] = 1;
            }
        }
        lli first = 0, second = 0;
        for(int temp = 0 ; temp < 30 ; temp++){
            if(ans1[temp]) first += List[temp];
            if(ans2[temp]) second += List[temp];
        }
        if(!(first ^ second == one && first + second == two)) {cout << "-1\n"; continue;}
        cout << first << " " << second << "\n";
    }
}
```

## F. Timofey and Black-White Tree

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128191038697.png" alt="image-20230128191038697" style="zoom:80%;" />

## G. Tokens on Graph

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230128191344959.png" alt="image-20230128191344959" style="zoom:80%;" />