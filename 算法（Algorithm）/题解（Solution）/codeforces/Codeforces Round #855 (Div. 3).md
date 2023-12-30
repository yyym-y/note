# Codeforces Round #855 (Div. 3)



**谨以此篇题解纪念第一次最好的CF成绩，以及对jch上移的两厘米发际线表示哀悼**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230303105019796.png" alt="image-20230303105019796" style="zoom:80%;" />



## A. Is It a Cat?

**思路/证明**

比较水，我们可以定义一个变量`point` , 然后用一个`old`来存储上一个字符在`meow`的下标

如果当前字符与`old`对应的字符一致，否则判断是否与`old`下一位对应的字符一致

最后判断`old`是否为最后一位



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1e5;
lli total_ask, Length;
vector<lli> arr(N);
string put, target = "meow";
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        cin >> put;
        transform(put.begin() , put.end() , put.begin() , ::tolower);  //转小写
        lli old = 0, flag = 1LL;
        for(int temp = 0 ; temp < Length ; temp++){
            if(put[temp] == target[old]) continue;
            if(old != 3){
                if(put[temp] == target[old + 1]){
                    old++; continue;
                }
            }
            flag = 0;
        }
        if(flag){
            if(old == 3) cout << "Yes\n";
            else cout << "No\n";
        }
        else cout << "No\n";
    }
    return 0;
}
```



## B. Count the Number of Pairs

**思路/证明**

我们可以统计一下不同字符出现的次数。

我们假设`A` 出现 $8$ 次， `a`出现 $4$ 次， 那么可以预知的是，它可以获得`min(A, a)`的价值，也就是 $4$

之后发现`A`多出来 $4$ 个，那么可以将剩余除 $2$ ，这样就可以在增加价值

不过要注意操作的次数不能超过 $k$



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1e5;
lli total_ask, Length, K;
vector<lli> arr(N);
string put;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> K;
        cin >> put;
        map<char, lli> Count;
        for(int temp = 0 ; temp < Length ; temp++)
            Count[put[temp]] ++;
        lli use = 0LL, ans = 0LL;
        for(int temp = 0 ; temp < 26 ; temp++){
            char a = 'a', b = 'A';
            lli one = Count[a + temp], two = Count[b + temp];
            ans += min(one, two);
            if(use < K){
                lli tem = max(one, two) - min(one , two);
                lli can = tem / 2;
                if(use + can <= K){
                    ans += can;
                    use += can;
                }else{
                    ans += K - use;
                    use = K;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```



## C2. Powering the Hero (hard version)



**思路/代码**

首先这题是使用优先队列的

我们假设这些士兵的下标分别为 ：`3, 6, 7, 11`

那么可以考虑贪心的思想： 对于下标为 $i$ 的士兵， 我拿取从 $1$ ~ $i-1$ ，中没有被拿过的最大的那个

那我们就可以使用优先队列来实现

每次到一个士兵，那么如果队列不空， 那么就去队列头元素，然后将它pop

// 我这个代码写的比较糟糕.......



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 20;
lli total_ask, Length;
vector<lli> arr(N);

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        for(int temp = 1 ; temp <= Length; temp++) cin >> arr[temp];
        vector<lli>point;
        for(int temp = 1 ; temp <= Length ; temp++){
            if(arr[temp] == 0) point.push_back(temp);
        }
        if(point.empty()) {cout << "0\n"; continue;}
        priority_queue<lli> Find;
        lli old = 1, ans = 0LL;
        for(int temp = 0 ; temp < point.size() ; temp++){
            for(int temp2 = old ; temp2 <= point[temp] - 1; temp2++)
                Find.push(arr[temp2]);
            old = point[temp];
            if(Find.empty()) continue;
            ans += Find.top();
            Find.pop();
        }
        cout << ans << "\n";
    }
    return 0;
}
```



## D. Remove Two Letters

**思路/证明**

首先绝对不能暴力，哪怕使用`unsigned_set`也不能过，会 MLE

我们注意，是连续的两个字符， 现在假设我们有一个字符串 $s$ = `abcde`

如果我们去除`bc`， 那么字符串将会变成`ade`， 如果我们去除`cd`, 那么字符串将会变成`abe`

如果`ade` 与 `abe` 一样， 那么就需要 `d = b` 

所以如果间隔一个字符的两个字符相同，那么就有一个是无效的

所以我们可以统计符合上述条件的对数， 代表有多少对是可以有重复的

注意 $s$ 后面要添加一个字符`'#'` ,这样最后如果 $s$ 最后两个也可以判断，实际上要两个....，但一个也行

对于一个长度为 `Len` 的字符串， 那么根据题目操作将会有 `Len - 1` 个字符串

然后我们删去之前统计的次数就是答案



**答案**

```c++
#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1e5;
lli total_ask, Length;
string put;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        cin >> put;
        put += "#";
        lli Count = 0LL;
        for(int temp = 0 ; temp < Length - 2 ; temp++){
            if(put[temp] == put[temp + 2]) Count++;
        }
        cout << Length - Count - 1 << "\n";
    }
    return 0;
}
```



## E1. Unforgivable Curse (easy version)

**思路/证明**

我感觉要先做出E1， 才能更好的推 E2, 也可能是我太菜......

假设我们两个字符串分别为 `one` , `two`

首先判断输入的两个字符串是否一致，一致直接输出 YES

首先对于长度小于等于3的字符串，如果输入的都不一样， 那么肯定是 NO

如果等于4， 那么`one`, `two`下标为 1 2 的字符要一样

同时， `one`下标为0的字符要与`two`下标为3的字符相同, `one`下标为3的字符要与`two`下标为0的字符相同

对于长度为5的字符串 ， 定义一个字符串 $s$ = `abcde`, 那么：

> `abcde`  $\Rightarrow$ `dbcae`
>
> `dbcae` $\Rightarrow$ `ebcad`
>
>  `ebcad` $\Rightarrow$ `abced`

所以说对于长度为5的字符串，最后两个是可以相互互换的， 反过来，将两个也是可以相互互换的

又因为两个区块是通过交换可以下标为 0，1，3，4都可以任意互换

至于长度大于5的字符串，可以只看后面长度为5的字符串，再结合前面的长度为五的字符串，这样所有的字符都可以相互交换

所以只需要统计字符出现的次数是否一致即可。

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1e5;
lli total_ask, Length, K;
vector<lli> arr(N);
string one, two;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> K;
        cin >> one >> two;
        if(Length <= 3){
            if(one == two) cout << "Yes\n";
            else cout << "No\n";
        }else if(Length == 4){
            if(one == two) cout << "Yes\n";
            else{
                if(one[1] == two[1] && one[2]==two[2]){
                    if(one[0] == two[3] && one[3] == two[0])
                        cout << "Yes\n";
                    else cout << "No\n";
                }else cout << "No\n";
            }
        }else{
            map<char,lli> Find1, Find2;
            for(int temp = 0 ; temp < Length ; temp++){
                Find1[one[temp]] ++;
                Find2[two[temp]] ++;
            }
            if(Find1 == Find2){
                if(Length == 5){
                    if(one[2] == two[2]) cout << "Yes\n";
                    else cout << "No\n";
                }else cout << "Yes\n";
            }
            else cout << "No\n";
        }
    }
    return 0;
}
```

## E2. Unforgivable Curse (hard version)

**思路/证明**

同理，只不过这时候的K变得不在是3了，那么我们仍然可以用之前easy的思路来想

首先对于长度小于等于K的输入，如果这两个字符串不相等， 那么就输出NO

如果等于 K+1， 那么就判断中间是否一致，两边是否可以通过互换达到一致

最后是大于 K+1的情况，画个图：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230303104658642.png" alt="image-20230303104658642" style="zoom:80%;" />

可以理解为有两个框，框内的元素都可以相互变换，框没有框到的元素将必须于目标字符串一一对应，否则就输出NO

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 1e5;
lli total_ask, Length, K;
vector<lli> arr(N);
string one, two;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> K;
        cin >> one >> two;
        if(one == two) {cout << "Yes\n"; continue;}
        if(Length <= K) {cout << "No\n"; continue;}
        if(Length == K + 1){
            int flag = 1;
            for(int temp = 1 ; temp < K ; temp++){
                if(one[temp] != two[temp]) {flag = 0; break;}
            }
            if(!flag) cout << "No\n";
            else{
                if(one[0] == two[K] && one[K] == two[0])
                    cout << "Yes\n";
                else cout << "No\n";
            }
        }else{
            map<char, int> Find1, Find2;
            for(int temp = 0 ; temp < Length ; temp++){
                Find1[one[temp]]++; Find2[two[temp]]++;
            }
            if(Find1 == Find2){
                lli tem = Length - (K + 1) - 1;
                lli left = tem + 2, right = K - 1;
                int flag = 1;
                for(int temp = left ; temp <= right ; temp++){
                    if(one[temp] != two[temp]){
                        flag = 0; break;
                    }
                }
                if(flag) cout << "Yes\n";
                else cout << "No\n";
            }else cout << "No\n";
        }
    }
    return 0;
}
```

