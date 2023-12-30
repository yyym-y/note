# Codeforces Round #843 (Div. 2)

[toc]



## A1. Gardener and the Capybaras (easy version)

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230110214800809.png" alt="image-20230110214800809" style="zoom:80%;" />



**题目大意**

现在有三个字符串 $A$ , $B$ , $C$ ,这三个字符串只由 $a , b$ 这两个字母构成

已知$B$ 满足以下条件之一： $B$ 的字典序比 $A$ $C$ 都要小或者等于 ， $B$ 的字典序比 $A$ $C$ 都要大或者等于

现在给你一个字符串 $Z$，让你从$Z$ 中找出一个符合上述条件的任意$A$, $B$, $C$ 组合



**思路/证明**

既然是easy version， 那就简单点，直接暴力搜索+遍历判断

数据小就是任性



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
string put;
int total_ask;
bool Judge1(string one, string two){
    int length = min(one.size(), two.size());
    for(int temp = 0 ; temp < length ; temp++){
        if(one[temp] > two[temp])
            return 0;
    }
    if(one.size() > two.size()) return 0;
    return 1;
}
bool Judge2(string one, string two){
    int length = min(one.size(), two.size());
    for(int temp = 0 ; temp < length ; temp++){
        if(one[temp] < two[temp])
            return 0;
    }
    if(one.size() < two.size()) return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> put;
        int flag = 1;
        for(int temp = 1 ; temp < put.size() - 1 && flag; temp++){
            for(int temp2 = temp+1 ; temp2 < put.size() ; temp2++){
                string a = put.substr(0,temp);
                string b = put.substr(temp,temp2-temp);
                string c = put.substr(temp2);
                if(Judge1(b,a) && Judge1(b,c)){
                    cout << a << " " << b << " " << c << "\n";
                    flag = 0;
                    break;
                }
                if(Judge2(b,a) && Judge2(b,c)){
                    cout << a << " " << b << " " << c << "\n";
                    flag = 0;
                    break;
                }
            }
        }
        if(flag) cout << ":(\n";
    }
    return 0;
}
```



## A2. Gardener and the Capybaras (hard version)

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230110215033342.png" alt="image-20230110215033342" style="zoom:80%;" />

**题目大意**

跟Easy Version一样，只有数据量变大了



**思路/证明**

我们先看条件

 $B$ 的字典序比 $A$ $C$ 都要小或者等于 ， $B$ 的字典序比 $A$ $C$ 都要大或者等于

其实除了这个，还有一个很特殊的条件：现在给你一个字符串 $Z$，让你从$Z$ 中找出一个符合上述条件的==任意==$A$, $B$, $C$ 组合

看到任意两个字，像极了高中数学填空压轴题不会 写的模样

我们完全可以找特殊情况：因为只有 $B$ 是受控制的，那我们就找 $B$ 的特殊情况，注意，在名字中，字典序最小的名字就是 $a$

所以我只需要在$[2,n-1]$ 中找到一个字符 $a$ 作为名字 $B$ ，那么将满足条件$B$ 的字典序比 $A$ $C$ 都要小或者等于

如果在$[2,n-1]$ 中找不到一个 $a$ ,说明 $[2,n-1]$ 中全是 $b$  ，那么将这$[2,n-1]$中所有的$b$ 作为名字 $B$ ， 那么将满足条件$B$ 的字典序比 $A$ $C$ 都要大或者等于



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
string put;
int total_ask;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> put;
        int left, right, flag = 0;
        for(int temp = 1 ; temp < put.size() - 1 ; temp++){
            if(put[temp] == 'a'){
                left = temp; right = temp+1;
                flag = 1;
            }
        }
        if(flag){
            string a = put.substr(0,left);
            string c = put.substr(right);
            cout << a << " a " << c << "\n";
            continue;
        }
        string b = put.substr(1,put.size()-2);
        cout << put[0] << " " << b << " " << put[put.size() - 1] << "\n";
    }
    return 0;
}
```



## B. Gardener and the Array

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230110215607369.png" alt="image-20230110215607369" style="zoom:80%;" />

**题目大意**

现在有一个数组 $A = {a_1, a_2, \cdots , a_n}$ ，选出两个子序列 $q$ , $p$ 

现在定义一个函数 $f(x)$ ，$x$ 为一个数组， $f(x) = x_1 | x_2 | x_3 | \cdots | x_n$  ,   $|$ 为 OR操作

现在问是否存在两个子序列使得 $f(q) = f(p)$ 

如果存在输出 $Yes$ , 不存在输出 $No$

注意输入的数据为二进制位，例如：第 $i$ 行输入1，5，6 ，代表 $a_i = 110010 (二进制表示)$ 

即 第 $i$ 行输入 $p_1, p_2, p_3, \dots , p_n$ ,则 $a_i = 2^{p_1} + 2^{p_2} + 2^{p_3} + \cdot +2^{p_n}$



 **思路/证明**

 我们首先要了解 OR操作的相关性质，以下图为例：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230112151305467.png" alt="image-20230112151305467" style="zoom:80%;" />

只要OR操作的某一个数的某一位是1，那么无论它与任何一个数进行OR操作，这个位都是1

所以可以想到我们先将所有的数进行OR操作，然后记录每个位被OR 1 的次数

之后我们遍历所有的输入的数据，如果某个数据是可以被替代的（也就是说他所提供的是1的位完全可以由其他数提供）

那么这个数据将是可有可无的



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int total_ask, total_num, num, step;
vector<int> info[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> total_num;
        for(int temp = 0 ; temp <= total_num ; temp++) info[temp].clear();
        //要用map， 如果用一个数组去记录，每次初始化将会耗费大量时间
        map<int,int> Count;
        for(int temp = 0 ; temp < total_num ; temp ++){
            cin >> num;
            for(int temp2 = 0 ; temp2 < num ; temp2++){
                cin >> step;
                info[temp].push_back(step);
                Count[step]++;
            }
        }
        int flag = 0;
        for(int temp = 0 ; temp < total_num ; temp++){
            int flag2 = 1;
            for(auto pr : info[temp]){
                if(Count[pr] == 1){
                    flag2 = 0;
                    break;
                }
            }
            if(flag2){flag = 1; break;}
        }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}
```



## C. Interesting Sequence

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230110220239949.png" alt="image-20230110220239949" style="zoom:80%;" />

**题目大意**

给你一个数 $n$ 和 $x$ ,问是否存在一个数 $m$ 使得

$n$ $\&$ $(n+1)$ $\&$ $(n+2)$ $\&$ $(n+3)$ $\&$ $\cdots$ $\&$  $m$  $=$ $x$ 

如果存在，输出最小的 $m$ , 如果不存在，输出 $-1$



**思路/证明**

首先先稍微了解一下 与(and) 运算，当两个位都为1的时候，这个位才为1

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230112165709969.png" alt="image-20230112165709969" style="zoom:80%;" />

可以观察到，$n$ $\&$ $(n+1)$ $\&$ $(n+2)$ $\&$ $(n+3)$ 会不断把 $n$ 后面全部变成0

也就是说假如 $n$ = $01011101111$ , 那将会有一下过程如果一直递增与下去

$01011101111 \Rightarrow 01011110000 \Rightarrow \dots \Rightarrow 000000000$

也就是说只要不做限制，最后将会变成0

那我们来把初始的 $n$ 与最后的 $target$ 作比较  $n$ = 10, $target$ = 8
$$
1\quad0\quad1\quad0 \\
1\quad0\quad0\quad0
$$
可以看到对于10来说，第四位是要保护的位，第二位是要消除的位

所以如果要想有解，那么$target$位上所有的1,$n$上都要有，且要消除的最高位不能高于要保留的最低位

但注意，我们要寻找的m是要大于n的，所以消除的最高位不能大于==等于==要保留的最低位

因为需要的$m$比$n$大那么需要这个消除的位需要进1，这会使它的上一位取反。

注：因为代码涉及位运算，所以会有注解，方便我这种小白看懂....

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, num1, target;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> num1 >> target;
        if((num1 & target) != target) {cout << "-1\n"; continue;}
        if(num1 == 0) {cout << "0\n"; continue;}
        vector<int> a, b;
        for(int temp = 0 ; temp < 60 ; temp++){
            if(num1 >> temp & 1){
                if(target >> temp & 1)
                    a.push_back(temp);
                else
                    b.push_back(temp);
            }
        }
        if(b.size() == 0) {cout << num1 << "\n"; continue;}
        if(a.size() != 0 && b.back() + 1 >= a[0]) {cout << "-1\n"; continue;}
        lli ans = num1;
        ans += 1LL << b.back();
        for(int temp = b.back() ; temp >= 0 ; temp--){
            if(ans >> temp & 1)
                ans ^= (1LL << temp);
        }
        cout << ans << "\n";
    }
    return 0;
}
```

**注解**

* `(num1 & target) != target` 

  主要是判断 是否 $target$位上所有的1，$n$上都有

  比如 $num1 = 1 1 0 0 1$ ， $target = 1 1 0 0 0$， 那么他们$\&$ 的值是 $1 1 0 0 0$

  但如果$target = 1 0 1 0 0$， 那么他们$\&$的值是 $1 0 0 0 0$

* `vector<int> a, b` 

  $a$用于存储要保留的位， $b$用于要消去的位， `a[0]`则是要保留的最低位， `b.back()` 则表示要删除的最高位

* `num1 >> temp & 1`

  主要是判断num1的第temp位是几，举个例子：

  $num1 = 100110$, 判断第五位， `num >> 5` = $000010$ , 在于$1(000001$)取$\&$ 得 $0$

* ```c++
  for(int temp = b.back() ; temp >= 0 ; temp--){
      if(ans >> temp & 1)
         ans ^= (1LL << temp);
  }
  ```

  主要目的是让$ans$ 在 `b.back()` 后面得位都变成0，先找出等于$1$得位，再让它于$1$异或，自然结果就是$0$了



## D. Friendly Spiders

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230112172855693.png" alt="image-20230112172855693" style="zoom:80%;" />
