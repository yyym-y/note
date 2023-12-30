# Codeforces Round #849 (Div. 4)

## A. Codeforces Checking

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204172307962.png" alt="image-20230204172307962" style="zoom:80%;" />

**题目大意**

输入字符，判断是否在“codeforces”里

**思路/证明**

water

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
set<char> Check;
int have;
void Init(){
    string a = "codeforces";
    for(auto pr : a) Check.insert(pr);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> have;
    Init();
    for(int temp = 0 ; temp < have ; temp++){
        char ch;
        cin >> ch;
        if(Check.count(ch)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```

## B. Following Directions

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204172651269.png" alt="image-20230204172651269" style="zoom:80%;" />

**题目大意**

从(0,0)开始，给你轨迹判断是否经过(1,1)

**思路/证明**

水题

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
string put;
lli X, Y, total_ask, flag, Length;
void Solution(char ch){
    if(ch == 'U') Y++;
    if(ch == 'R') X++;
    if(ch == 'D') Y--;
    if(ch == 'L') X--;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask --){
        X = 0; Y = 0; flag = 0;
        cin >> Length >> put;
        for(char pr : put){
            Solution(pr);
            if(X == 1 && Y == 1) {flag = 1; break;}
        }
        if(flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```
## C. Prepend and Append

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204172900248.png" alt="image-20230204172900248" style="zoom:80%;" />

**题目大意**

你可以在字符串前面加0后面加1，也可以前面1后面0，问最短原始字符串长度

**思路/证明**

模拟即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length;
string put;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask --){
        cin >> Length >> put;
        lli left = 0, right = Length - 1, flag = 0;
        while(flag == 0 && left < right){
            if(put[left] == '0' && put[right] == '1') {left++; right--; continue;}
            if(put[left] == '1' && put[right] == '0') {left++; right--; continue;}
            flag = 1;
        }
        cout << right - left + 1 << "\n";
    }
    return 0;
}
```

## D. Distinct Split

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204173002678.png" alt="image-20230204173002678" style="zoom:80%;" />

**题目大意**

给你一个字符串，你可以将其分割成两个部分$s_1, s_2$，$f(x)$为 $x$字符串中不一样字符的个数

问$f(s_1) + f(s_2)$ 的最大值

**思路/证明**

从左扫一遍记录$f(x)$ 的值，在从右扫一遍，记录

之后求最大值即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length;
string put;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> put;
        vector<int> right, left;
        set<char> R, L;
        right.push_back(0); left.push_back(0);
        for(int temp = 0 ; temp < Length ; temp++){
            R.insert(put[temp]);
            right.push_back(R.size());
        }
        reverse(put.begin(), put.end());
        for(int temp = 0 ; temp < Length ; temp++){
            L.insert(put[temp]);
            left.push_back(L.size());
        }
        lli ans = 0LL;
        for(int temp = 0 ; temp <= Length ; temp++){
            lli tem = right[temp] + left[Length - temp];
            ans = max(tem, ans);
        }
        cout << ans << "\n";
    }
    return 0;
}
```

## E. Negatives and Positives

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204173304685.png" alt="image-20230204173304685" style="zoom:80%;" />

**题目大意**

给你一个数组，你可以选取两个相邻的数，然后两个数的符号都变化，问这个数组最大的和是多少

**思路/证明**

可以观察到 两个负数可以全部变成正数，一个负数和0也可以把负数消掉

所以统计负数的个数，如果为偶数，那么负数全可以变成正数

如果剩一个，那么考虑消掉这个还是不消，将两种结果比较即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length;
string put;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> put;
        vector<int> right, left;
        set<char> R, L;
        right.push_back(0); left.push_back(0);
        for(int temp = 0 ; temp < Length ; temp++){
            R.insert(put[temp]);
            right.push_back(R.size());
        }
        reverse(put.begin(), put.end());
        for(int temp = 0 ; temp < Length ; temp++){
            L.insert(put[temp]);
            left.push_back(L.size());
        }
        lli ans = 0LL;
        for(int temp = 0 ; temp <= Length ; temp++){
            lli tem = right[temp] + left[Length - temp];
            ans = max(tem, ans);
        }
        cout << ans << "\n";
    }
    return 0;
}
```

## F. Range Update Point Query

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204173335885.png" alt="image-20230204173335885" style="zoom:80%;" />

**题目大意**

如果输入 1， 那么你需要将 $[l,r]$内所有的数进行操作$z$

操作$z$: 将这个数变成它数位的和 123 -> 6

输入2，查询第 $i$个数的值

**思路/证明**

可以观察，在数据范围内，任何数进行操作$z$ 3次后都不在会改变，所以我们可以记录进行的次数，然后暴力即可

可以使用树状数组来维护，我采用线段树

**代码**
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const lli N = 2e5;
lli total_ask, Length, ask_time;
lli ls(lli number) {return number << 1;}
lli rs(lli number) {return number << 1 | 1;}
vector<lli> arr;
struct TREE{
    lli Sum;
    lli left, right;
}tree[N << 2];
void BuildTree(lli index, lli l, lli r){
    tree[index].left = l; tree[index].right = r;
    if(l == r){
        tree[index].Sum = 0;
        return;
    }
    lli mid = (l + r) >> 1;
    BuildTree(ls(index), l, mid);
    BuildTree(rs(index), mid + 1, r);
    tree[index].Sum = tree[ls(index)].Sum + tree[rs(index)].Sum;
}
void modify(lli index, lli target, lli add){
    if(tree[index].left == target && tree[index].right == target){
        tree[index].Sum += add;
        return;
    }
    if(tree[ls(index)].right >= target) modify(ls(index), target, add);
    else if(tree[rs(index)].left <= target) modify(rs(index), target, add);
    tree[index].Sum = tree[ls(index)].Sum + tree[rs(index)].Sum;
    return;
}
lli query(lli index, lli l, lli r){
    if(tree[index].left == l && tree[index].right == r)
        return tree[index].Sum;
    lli ans = 0;
    if(tree[ls(index)].right >= r) ans += query(ls(index), l,r);
    else if(tree[rs(index)].left <= l) ans += query(rs(index), l, r);
    else{
        lli one = query(ls(index), l, tree[ls(index)].right);
        lli two = query(rs(index), tree[rs(index)].left, r);
        ans += (one + two);
    }
    return ans;
}
lli Compute(lli number, lli time_, lli now){
    if(now == time_) return number;
    string use = to_string(number);
    lli ans = 0;
    for(int temp = 0 ; temp < use.size() ; temp++)
        ans += (use[temp] - '0');
    return Compute(ans, time_, now+1);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> ask_time;
        arr.clear(); arr.push_back(0); BuildTree(1,1,Length + 1);
        bitset<N> Check;
        for(lli temp = 0, num; temp < Length ; temp++){
            cin >> num;
            arr.push_back(num);
        }
        lli order, one, two;
        for(int temp = 1 ; temp <= ask_time ; temp++){
            cin >> order;
            if(order == 1){
                cin >> one >> two;
                modify(1, one, 1); modify(1, two + 1, -1);
            }else{
                cin >> one;
                if(Check[one] == 1) {cout << arr[one] << "\n"; continue;}
                lli time_ = query(1,1,one);
                if(time_ >= 3){
                    lli ans = Compute(arr[one], 3, 0);
                    Check[one] = 1;
                    arr[one] = ans;
                    cout << ans << "\n";
                }else
                    cout << Compute(arr[one], time_, 0) << "\n";
            }
        }
    }
    return 0;
}
```

## G1. Teleporters (Easy Version)

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204173418423.png" alt="image-20230204173418423" style="zoom:80%;" />

**题目大意**

你有$c$ 个硬币，你在0点，你可以进行如下操作：

向左移一步，花费一个硬币

向右移一步，花费一个银币

使用此地传送门，消耗$a_i$个硬币，然后回到0点

问你可以最多使用多少个传送门

**思路/证明**

我们可以算出去每个点的贡献，然后排序，贪心取即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length, coin;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length >> coin;
        vector<lli> Check;
        for(lli temp = 1, num ; temp <= Length ; temp++){
            cin >> num;
            Check.push_back(num + temp);
        }
        sort(Check.begin(), Check.end());
        lli ans = 0;
        while(coin > 0){
            if(ans == Length) break;
            if(coin >= Check[ans]){
                coin -= Check[ans]; ans++;
            }else break;
        }
        cout << ans << "\n";
    }
    return 0;
}
```

## G2. Teleporters (Hard Version)

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230204173507023.png" alt="image-20230204173507023" style="zoom:80%;" />