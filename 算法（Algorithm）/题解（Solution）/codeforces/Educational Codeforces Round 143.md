# Educational Codeforces Round 143

[toc]

[比赛网址](https://codeforces.com/contest/1795)

**写在前面**

在我这几天的不懈努力下，终于，没把E题补完.....，作为一道使用单调栈的题目，思想十分高明先进，很遗憾错过了这道题，看看以后能不能再补吧.....

## A. Two Towers

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230217230056774.png" alt="image-20230217230056774" style="zoom:80%;" />

**思路/证明**

这道题赛后想到了一个更高明的方法

移动的本质实际上是将上面的积木以逆序的方式移动到另一块积木上，

所以我们可以将一整块积木逆序拼接到另外一个积木上， 举个例子；

a = **BRBRBRB**  b = **BBRBR**		，然后我们将b逆序拼到a上得到： **BRBRBRBRBRBB**

之后我们维护两个指针`left` , `right` ，分别指向新字符串得开头和末尾

之后不断判断`left`最远可以到哪使`[0,left]`的字符串满足题目的要求， `right`同理

然后判断`left` 于`right`的差值是否小于1即可



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length1, Length2;
string a, b;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length1 >> Length2;
        cin >> a >> b;
        reverse(b.begin(), b.end());
        a += b;
        lli left = 0LL, right = a.size() - 1;
        char old1 = a[0], old2 = a[right];
        for(int temp = 1 ; temp < a.size() ; temp++){
            if(a[temp] == old1) break;
            old1 = a[temp]; left = temp;
        }
        for(int temp = right - 1 ; temp >= 0 ; temp--){
            if(a[temp] == old2) break;
            old2 = a[temp]; right = temp;
        }
        if(right - left > 1) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}
```





## B. Ideal Point

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230217230155624.png" alt="image-20230217230155624" style="zoom:80%;" />



**思路/证明**

既然是可以删除任何多个线段，那我们可以考虑极限情况，假设我们只留下两个点，那么怎么样才能让题目给的`target`值最优呢？

只有一种情况满足： 那就是两个线段的端点在`target`值上重合，但这两个线段除了在`target`上重合外不再重合

举个例子： `[1, 5]` 和 `5, 10]` ，这样就可以让5达到最优

 所以我们只需要统计左端点为`target`值的有多少个， 右端点是`target`值的有多少个

注意一种特殊情况， 如果是`[target, target]`这种情况，我们就可以只留下这个点

也就是说，`[target, target]`出现必有解



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
int total_ask, have, target;;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        lli target_l = 0LL, target_r = 0LL, point = 0LL, eat = 0LL;
        cin >> have >> target;
        for(lli temp = 0, num1, num2; temp < have ; temp++){
            cin >> num1 >> num2;
            if(num1 == num2 && num1 == target) point++;
            else if(num1 == target) target_r++;
            else if(num2 == target) target_l++;
            else continue;
        }
        if(target_l && target_r) cout << "Yes\n";
        else if(point) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```





## C. Tea Tasting

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/QQ%E6%88%AA%E5%9B%BE20230217230357.png" alt="QQ截图20230217230357" style="zoom:80%;" />



**思路/证明**

芜湖，第一次在赛事一次就过掉了C，所实话这题用的算法思维挺多的，我都不知道我咋想到的.....

先把出现的算法思维列一下： 单独考虑贡献， 前缀和， 差分， 二分查找

首先我们考虑作为一杯茶，我们到底会被几个人喝掉：

> 第一杯 ： $1,2,3,4,5,\dots$
>
> 第二杯 ： $2,3,4,5,6,\cdots$
>
> $\dots\dots$

可以观察到，第$i$ 杯茶从第$i$ 个人开始喝，那么喝到谁截止呢？当然是茶的容量已经不支持再喝下去了

也就是说茶$i$ 的量总共有 $v_i$ ， 喝到人 $b$ 截至， 那么 $a_i + a_i+1 + \dots + a_b \le v_i$

想想如何优化这一求和过程，求和？值还不变？ 那必是前缀和啊。

如何寻找一个小于等于 $v_i$ 的坐标？ 在递增的序列里， 那必是用upper_bound 二分查找啊

再想想，可能有些人并不能喝的尽兴，因为此时茶已经不够了， 那么我们就可以把一个茶被喝分为两个部分：

* 喝到自己的值$a_k$
* 没喝到$a_k$， 只能喝剩下的了

所以我们用两个数组分别计算这种情况，一种用来统计这个人喝尽兴了几次，第二个计算这个人喝剩下的一共喝了多少

注意，对于第$i$ 杯茶喝到第 $k$ 人截止， 那么对于第一个数组， $i$ 到 $k-1$ 都要加上一个$1$

欸？区间加法？ 差分！必是了

所以这道题就做完了。

其实还有一些细节：在二分查找的时候，你需要将 $v_i$加上`sum`数组的第$i-1$个值，这样才能顺利查找

加剩余的时候也要记得减掉， 至于为什么，你写代码的时候自然懂啦



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 2e5 + 10;
vector<lli> tea(N), people(N), sum(N);
vector<lli> div_(N), Count(N), fin(N);
int total_ask, have;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> have;
        for(int temp = 1 ; temp <= have ; temp++) cin >> tea[temp];
        for(int temp = 1 ; temp <= have ; temp++) cin >> people[temp];
        for(int temp = 1 ; temp <= have ; temp++){
            sum[temp] = sum[temp - 1] + people[temp];
            div_[temp] = 0LL; Count[temp] = 0LL;
        }
        for(int temp = 1 ; temp <= have ; temp++){
            auto re = upper_bound(sum.begin() + temp, sum.begin() + have + 1, tea[temp] + sum[temp - 1]);
            lli index = re - sum.begin() - 1, ele = sum[index];
            Count[index + 1] += tea[temp] - ele + sum[temp - 1];
            div_[temp] ++; div_[index + 1]--;
        }
        for(int temp = 1 ; temp <= have ; temp++)
            fin[temp] = fin[temp - 1] + div_[temp];
        for(int temp = 1 ; temp <= have ;temp++)
            cout << Count[temp] + people[temp] * fin[temp] << " ";
        cout << "\n";
    }
    return 0;
}
```



## D. Triangle Coloring

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230217230558836.png" alt="image-20230217230558836" style="zoom:80%;" />



**思路/证明**

有一说一，这题不如C题

想想， 对于一个三角内，肯定是只有一个与其他不同的颜色是最佳的， 毕竟这样可以加两条边，说人话就是 RRB 和 BBR 这两种情况

所以我们可以找到对于一个三角最优的选择就是把最大和次大的两条边加上

注意一个三角内可能有多种情况使值达到这个最优情况，所以我们穷举即可，一共3种

然后因为 B的数量于 R的数量一致，所以答案还需乘上$C_{\frac{n}{3}}^{\frac{n}{6}}$ 

至于如何求组合数和除法取模，可以看看俺写的其他博客：

[快速求组合数的三种方法_yyym__的博客-CSDN博客](https://blog.csdn.net/weixin_73503181/article/details/129101618)

[乘法逆元 + 模的除法_yyym__的博客-CSDN博客](https://blog.csdn.net/weixin_73503181/article/details/129099778)



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 3e5 + 10;
lli have, P = 998244353;
lli mod(lli number) {return number % P;}
lli fast_pow(lli n, lli power){
    lli ans = 1LL;
    while(power){
        if(power & 1) ans = mod(ans * n);
        n = mod(n * n);
        power >>= 1;
    }
    return (ans + P) % P;
}
lli Compute(lli m, lli n){
    vector<lli> info(m + 10, 0), rev(m + 10, 0);
    info[0] = 1; rev[0] = 1;
    for(int temp = 1 ; temp <= m + 1 ; temp++){
        info[temp] = mod(info[temp - 1] * temp);
        rev[temp] = mod(rev[temp - 1] * fast_pow(temp, P - 2));
    }
    return info[m] * rev[n] % P * rev[m - n] % P;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> have;
    vector<lli> arr(have + 10);
    for(int temp = 1 ; temp <= have ; temp++)
        cin >> arr[temp];
    lli ans = 1LL;
    for(int temp = 1 ; temp <= have ; temp += 3){
        map<lli,lli> Count;
        lli a = arr[temp], b = arr[temp + 1], c = arr[temp + 2];
        Count[a + b] ++; Count[a + c] ++; Count[b + c] ++;
        lli Max = (a + b + c) - min({a,b,c});
        ans *= Count[Max];
        ans = mod(ans);
    }
    ans = mod(ans * Compute(have / 3, have / 6));
    cout << ans << "\n";
}
```



## E. Explosions?

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230217230642907.png" alt="image-20230217230642907" style="zoom:80%;" />