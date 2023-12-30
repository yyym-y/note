# C++进阶技巧

最大值最小值函数

```c++
#include<algorithm>
```

## int 强转 string  to_string

```c++
auto break_(int number){
   string s;
   s = to_string(number);
    return s;
}
```

## string大小写转换

```c++
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    string aa = "aaasslldk";
    transform(aa.begin() , aa.end() , aa.begin() , ::toupper); //转大写
    cout << aa <<endl;
    transform(aa.begin() , aa.end() , aa.begin() , ::tolower);  //转小写
    cout << aa;
}
```

## stringstream 类

stringstream用于类型转换与不定长度的读取

**与getline配合使用，如果前面有额外输入数字，主要要cin.ignore将\n吃掉**

```c++
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    string put1;
    int number1;
    cin >> put1;
    stringstream ss;
    ss << put1;
    ss >> number1; //强制类型转换
    ss.clear(); // ss.str(""); 两种清空方式，使用强制类型转换后用clear
    cin.ignore();
    cin >> put1;
    ss << put1
    while(ss >> number1) //可以将每一个数字读出，不需要知道具体个数
        cout << number;
}
```

## map排序相关

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221116144934165.png" alt="image-20221116144934165" style="zoom:80%;" />

```c++
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    ios::sync_with_stdio(false) , cin.tie(0) , cout.tie(0);
    int number;
    map<string , int>remem;
    for(cin >> number ; number ; number--){
        string put;
        cin >> put;
        remem[put]++;
    }
    map<int , vector<string>>ans; //重点在这一步，pair第二个参数是vector，所以哪怕次数一样也不会被替换掉
    for(auto pr : remem){
        ans[-pr.second].push_back(pr.first); //.push_back
    }
    for(auto pr1 : ans){
        for(auto pr2 : pr1.second){
            cout << pr2 << " " << -pr1.first << "\n";
        }
    }
    return 0;
}
```



## copy()函数

```c++
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0) , cout.tie(0);
    int arr[3] = {0,7,3};
    for(int temp : arr)
        cout << temp << " ";
    cout <<endl;
    int abc[3];
    copy(arr , arr+3 , abc);
    for(int temp : abc)
        cout << temp << " ";
    return 0;
}
```



## max_element()函数

求数组最大值，返回地址，要解引用

```c++
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0) , cout.tie(0);
    int arr[3] = {0,7,3};
    cout <<*(max_element(arr , arr + 3));
}
```



## sort排序函数可设立多重要求

```c++
struct member{
    string name, preview;
    lli score, grade, id, now;
}info[200];
bool cmp1(struct member a, struct member b){
    if(a.score == b.score)
        return a.id < b.id;
    else
        return a.score > b.score;
}
bool cmp2(struct member a, struct member b){
    if(a.now != b.now)
        return a.now < b.now;
    else if (a.now == b.now && a.grade != b.grade)
        return a.grade > b.grade;
    else
        return a.id < b.id;
}
```



## next_permutation()  prev_permutation()

next_permutation返回下一排列，prev_permutation返回上一排列

可以理解为返回移动数字能达到的比这个数要大（小）的第一个数

next_permutation原理

在当前序列中，从尾端向前寻找两个相邻元素，前一个记为\*i，后一个记为\*t，并且满足*i < *t。然后再从尾端

寻找另一个元素\*j，如果满足\*i < *j，即将第i个元素与第j个元素对调，并将第t个元素之后（包括t）的所有元

素颠倒排序，即求出下一个序列了

```c++
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    int arr[5] = {1,2,3,4,5};
    int num = 10;
    next_permutation(arr,arr + 5);
    for(int temp = 0 ; temp < 5 ; temp++)
        cout << arr[temp] << " ";
    cout << "\n";
}
//1 2 3 5 4
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    int arr[5] = {1,2,3,4,5};
    int num = 10;
    prev_permutation(arr,arr + 5);
    for(int temp = 0 ; temp < 5 ; temp++)
        cout << arr[temp] << " ";
    cout << "\n";
}
//5 4 3 2 1
//注：如已是最后排列/第一排列，函数返回false,但数组数据仍会改变
```

## lower_bound()/upper_bound()

在从小到大的排序数组中，

lower_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

在从大到小的排序数组中，重载lower_bound()和upper_bound()

lower_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

upper_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

## is_sorted()



## 排列常见求和

$$
C_n^m = C_{n-1}^{m-1} + C_{n-1}^{m}\\\\
m\cdot C_n^m = n\cdot C_{n-1}^{m-1}\\\\
C_n^0 + C_n^1 + C_n^2 + \dots+ C_n^n = 2^n\\\\
1\cdot C_n^1 + 2\cdot C_n^2 + 3\cdot C_n^3 +\dots+n\cdot C_n^n = n\cdot2^{n-1}\\\\
1^2\cdot C_n^1 + 2^2\cdot C_n^2+3^2\cdot C_n^3 +\dots +n^2\cdot C_n^n = n(n+1)\cdot2^{n-2}\\\\
\frac{C_n^1}{1} - \frac{C_n^2}{2} + \frac{C_n^3}{3} + \dots + (-1)^{n-1}\frac{C_n^n}{n} = 1+\frac{1}{2}
+\frac{1}{3}+\dots +\frac{1}{n}\\\\
(C_n^0)^2+(C_n^1)^2+(C_n^2)^2+\dots+(C_n^n)^2+ = C_{2n}^n
$$

## 快速幂

```c++
lli fast_pow(lli number, lli power){
    lli ans = 1LL; number %= P;
    while(power){
        if(power & 1) ans  = mod(ans * number);
        number = mod(number * number);
        power >>= 1;
    }
    return ans;
}
```

## set_intersection( )

**求交集**

使用时注意两个输入必须是有序，并且存储的容器应有足够的空间

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
signed main()
{
    vector<lli>arr1,arr2;
    for(int temp = 1 ; temp <= 10 ; temp ++){
        arr1.push_back(temp); arr2.push_back(temp);
    }
    for(int temp = 5 ; temp <= 15 ; temp++)
        arr2.push_back(temp);
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    vector<lli> final(50);
    auto re = set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), final.begin() + 1);
    int index = re - final.begin();
    for(int temp = 1 ; temp < index ; temp++)
        cout << final[temp] << " ";
    return 0;
}
```

## set_union()

**求并集**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
signed main()
{
    vector<lli>arr1,arr2;
    for(int temp = 1 ; temp <= 10 ; temp ++){
        arr1.push_back(temp); arr2.push_back(temp);
    }
    for(int temp = 5 ; temp <= 15 ; temp++)
        arr2.push_back(temp);
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    vector<lli> final(50);
    auto re = set_union(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), final.begin() + 1);
    int index = re - final.begin();
    for(int temp = 1 ; temp < index ; temp++)
        cout << final[temp] << " ";
    return 0;
}
```

## set_difference()

**求差集**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
signed main()
{
    vector<lli>arr1,arr2;
    for(int temp = 1 ; temp <= 10 ; temp ++){
        arr1.push_back(temp); arr2.push_back(temp);
    }
    for(int temp = 5 ; temp <= 15 ; temp++)
        arr2.push_back(temp);
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    vector<lli> final(50);
    auto re = set_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), final.begin() + 1);
    int index = re - final.begin();
    for(int temp = 1 ; temp < index ; temp++)
        cout << final[temp] << " ";
    return 0;
}
```

