# Educational Codeforces Round 141 (Rated for Div. 2)

[网址](https://codeforces.com/contest/1783)

## A. Make it Beautiful

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109111157546.png" alt="image-20230109111157546" style="zoom:80%;" />

**题目大意**

如果一个数列 $a$ 至少有一个元素等于在它之前的元素和，那么这个数列就是一个 $ugly$ 数列

如果数列不是 $ugly$ 数列，那么就是一个 $beautiful$ 数列

现在给你一个数列 $a$， 你可以随意修改这个数列中元素的数据，让它变成一个 $beautiful$ 数列

注意你不可以在数列中增加原本没有的数据，也不能删除存在的数据

如果有多种组合符合条件，你只需随意输出一个



**思路/证明**

这道题可以采用一个贪心的思维

我们把最大的放在前面，较小的放在后面，这样后面的元素就可以避免于之前的元素和相同了

值得注意的是，如果当前可以选的最大的数于之前元素的和一样，我们只需要寻找比它小的一个数就好了

求和的话可以用前缀和来维护



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, total_num;
const lli N = 100;
vector<lli> arr(N), sum(N), ans(N);
bool cmp(lli a, lli b){
    return a > b;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> total_num;
        arr.clear(); sum.clear(); ans.clear();
        arr.resize(N);sum.resize(N); ans.resize(N);//要重新resize，因为后面会将元素删除
        for(int temp = 1 ; temp <= total_num ; temp++)
            cin >> arr[temp];
        sort(arr.begin() + 1, arr.begin()+total_num+1, cmp);
        int flag = 1;
        for(int temp = 1 ; temp <= total_num ; temp++){
            int flag2 = 0;
            //下面的循环次数要进行变更，应为元素有删除
            for(int temp2 = 1 ,check = 0; temp2 <= total_num - temp + 1; temp2++){
                if(arr[temp2] != sum[temp - 1]){
                    ans[temp] = arr[temp2];
                    arr.erase(arr.begin()+temp2);
                    sum[temp] = sum[temp - 1] + ans[temp];
                    flag2 = 1;
                    break;
                }
            }
            if(!flag2) flag = 0;
        }
        if(!flag) cout << "No\n";
        else{
            cout << "YES\n";
            for(int temp = 1 ; temp <= total_num ; temp++)
                cout << ans[temp] << " ";
            cout << "\n";
        }
    }
}
```



## B. Matrix of Differences

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109111553715.png" alt="image-20230109111553715" style="zoom:80%;" />



**题目大意**

对于一个矩阵$\begin{pmatrix}1 &2&3\\ 4&5&6\\7&8&9\end{pmatrix} $ , 拿元素5举例， $5$与 $2$，$4$，$6$，$8$相邻

将矩阵中的每一个数 $a$， 与其相邻的数 $b$ 之间的差的绝对值 $c = |a-b|$记录，我们可以得到一组数 $C = {c_1,c_2\dots c_n}$

$C$中不同元素的个数为 $v$ ， 这个数 $v$ 被称为这个矩阵的 $beautiful$ 值

现在给你一个整数 $n$，让你构建一个 $n\cdot n$  的矩阵使得这个矩阵得$beautiful$ 值最大

矩阵中的值范围为 $[1, n\cdot n]$ , 且矩阵中的元素只会出现一次

有多种组合，你只需要输出一种



**思路/证明**

这道题给我最大的触动是有些时候不要被样例带跑

我们拿 $n = 3$ 举例：

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109163820194.png" alt="image-20230109163820194" style="zoom:80%;" />

我们可以发现$beautiful$值最大其实就是 $n^2 - 1$

所以我们只需要将上述这样一条“链子”找到，然后蛇形走位再将其排成一个矩阵即可

那我们如何将这条“链子”找出来呢

首先我们要的差值为$c$， 当前数为$a$， 那么下一个数有两种可能，一个是$a+c$, 一个是 $c-a$

如果这两个数有一个满足在$[1,n\cdot n]$中，且没有在之前出现过，即为答案

判断是否出现过可以使用set



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 50000;
vector<int>ans(N);
set<int>Check;
int arr[100][100];
int size_, use, total_ask;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> size_;
        ans.clear(); ans.resize(N);Check.clear();
        for(int temp = 2 ; temp <= size_*size_ ; temp++) Check.insert(temp);
        use = size_*size_ - 1;
        ans[0] = 1;
        for(int temp = 1 ; temp < size_*size_ ; temp++){
            int one = ans[temp-1]+use;
            int two = ans[temp-1]-use;
            if(one > 0 && one <= size_*size_){
                if(Check.count(one)){
                    ans[temp] = one;
                    Check.erase(one);
                }
            }
            if(two > 0 && two <= size_*size_){
                if(Check.count(two)){
                    ans[temp] = two;
                    Check.erase(two);
                }
            }
            use--;
        }
        int index_ = 0;
        //我是用另一个数组实现蛇形走位，牺牲了空间但比较好写，可以尝试控制输出端点位置以及方向来输出，这样更好
        for(int temp = 1 ; temp <= size_ ; temp++){
            if(temp % 2){
                for(int temp2 = 1 ; temp2 <= size_ ; temp2++)
                    arr[temp][temp2] = ans[index_++];
            }else{
                for(int temp2 = size_ ; temp2 >= 1 ; temp2--)
                    arr[temp][temp2] = ans[index_++];
            }
        }
        for(int temp = 1 ; temp <= size_ ; temp++){
            for(int temp2 = 1 ; temp2 <= size_ ; temp2++){
                cout << arr[temp][temp2] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
```



## C. Yet Another Tournament

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109111646611.png" alt="image-20230109111646611" style="zoom:80%;" />



**题目大意**

现在有 $n$ 个人外加一个你， 这 $n$ 个人的编号是 $1,2,3, \dots , n$

现在加上你一共有$n+1$个人，现在这$n+1$个人两两都要进行一场比赛

对于这$n$个人来说，输赢很简单，两个人 $a_i$ , $a_j$， 有且仅有 $i > j$ 的时候 $a_i$ 赢得比赛

但到了你，问题就变得复杂了，你有  $m$ 的时间，这 $n$ 个人都有一个时间 $v$，你需要准备 $v$ 时间才能打败他

注意： 你在同一时间内只能准备一个人



**思路/证明**

注意：当你输一场的时候，你的对手的胜场将会+1，这可能会导致排名波动

现在假设你的胜场为 $x$ ，其它人的胜场从 依次为 $0,1,2,3,\dots,n-3,n-2,n-1$

对于那些胜场不如你的人，即 $0,1,\dots, x-1$ 的人，你与他们的输赢完全不会影响你的排名

对于那些胜场大于你的人，即 $x,x+1,x+3,\dots, n-3,n-2,n-1$ 的人，你与他们的输赢也不会影响你的排名

真正会影响你的排名的只有那个跟你胜场一样的人，你要是赢了它，你的排名就是他的排名，输了，你的排名就是它的下一位

明白了这个道理之后，我们再来考虑我们到底赢了多少场，即x是多少

$x$是单调的，$x$在$[0,n]$中， 同理你的名次step也是单调的，在$[1,n+1]$之中

所以我们可以二分答案来确定你的名词是多少（当然不二分也行）

我们从两个方向思考，一个是$x$，即胜场

假设你赢了 $temp$ 场， 那么你肯定超过了至少 $temp$人， 那么你的排名至少为 $n - temp + 1$

现在假设你赢下$temp$场的同时也赢下了那个与你一样胜场的人

也就是说你胜场为$temp-1$的时候赢下了那个胜场为$temp$的人，那么你的胜场将达到 $temp$，你的排名也会和他一样，变成$n - temp + 1$

具体的实现方法看代码2+注释

现在考虑名次 $step$

假设你的名次是$step$，判断这个名次你是否可以达到，现在这个排名的胜场为 $n - step$

达到的条件有两个

第一个是你的胜场已经超过了$n-step$

第二个你的胜场为$n-step-1$，但是你打败了原本那个在这个排名的人，你和它并列$step$名

具体看代码1，（代码一不带注释，但是与代码二类似，可以参考代码二）懒......

**代码**

1.二分 //考虑名次

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6;
int info[N], sum[N], tem[N];
int total_ask, total_people, time_;
bool Check(int number){
    if(time_ >= sum[total_people - number + 1])
        return 1;
    if(info[total_people - number + 1] <= tem[total_people - number]){
        if(time_ >= sum[total_people - number])
            return 1;
    }else{
        if(time_ >= sum[total_people - number - 1] + info[total_people - number + 1])
            return 1;
    }
    return 0;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> total_people >> time_;
        for(int temp = 1 ; temp <= total_people ; temp++){
            cin >> info[temp];
            tem[temp] = info[temp];
        }
        sort(tem + 1, tem + total_people + 1);
        for(int temp = 1 ; temp <= total_people ; temp++)
            sum[temp] = tem[temp] + sum[temp - 1];
        int left = 1, right = total_people + 1;
        while(left < right){
            int mid = (left + right) >> 1;
            if(Check(mid)) right = mid;
            else left = mid + 1;
        }
        cout << left << "\n";
    }
    return 0;
}
```

2.枚举 //考虑胜场

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6;
int info[N], sum[N], tem[N];
int total_ask, total_people, time_;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> total_people >> time_;
        for(int temp = 1 ; temp <= total_people ; temp++){
            cin >> info[temp];
            tem[temp] = info[temp]; //拷贝一份原数组
        }
        sort(tem + 1, tem + total_people + 1);//对这个数组进行排序
        for(int temp = 1 ; temp <= total_people ; temp++)//对其求前缀和，目的是判断我所拥有的时间到底可以赢多少场
            sum[temp] = tem[temp] + sum[temp - 1];
        int ans = time_ < sum[1] ? total_people + 1 : total_people;//如果连第一场都赢不了，排名设为n+1
        for(int temp = 2 ; temp <= total_people ; temp++){//依次判断胜场数
            if(time_ >= sum[temp])//如果你可以胜temp场
                ans = total_people - temp + 1;//那么你的排名至少是这个
            if(info[temp] <= tem[temp - 1]){//当那个胜场为temp-1的人你在你可以打败的temp-1个人中时
                if(time_ >= sum[temp - 1]) //如果你可以打败temp-1的人
                    ans = total_people - temp + 1;//你的排名至少是这个
            }else{//当那个胜场为temp-1的人你不在在你可以打败的temp-1个人中时
                if(time_ >= pre[temp - 2] + info[temp])//你需要能打败temp-2个人外加那个胜场为temp-1的人
                    ans = total_people - temp + 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```



## D. Different Arrays

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109111810432.png" alt="image-20230109111810432" style="zoom:80%;" />



## E. Game of the Year

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109111952077.png" alt="image-20230109111952077" style="zoom:80%;" />



## F. Double Sort II

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109112029730.png" alt="image-20230109112029730" style="zoom:80%;" />



## G. Weighed Tree Radius

<img src="C:\Users\阴铭洋\Desktop\笔记\codeforces\image\image-20230109112232737.png" alt="image-20230109112232737" style="zoom:80%;" />