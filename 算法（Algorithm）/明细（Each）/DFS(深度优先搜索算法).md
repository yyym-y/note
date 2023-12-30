# DFS（深度优先搜索算法）

DFS的核心即是函数的递归

用简单的话来说，DFS == 函数递归

其基本思路便是一路走到黑，遍历到最底下一个之后才结束此轮遍历

用二叉树来表示：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221205170601022.png" alt="image-20221205170601022" style="zoom:80%;" />

二叉树的代码实现

```c++
#include<bits/stdc++.h>
using namespace std;
struct Node{
    char value;
    int l_son;
    int r_son;
}tree[1000];
int index = 1;

int NewNode(char put){
    tree[index].value = put;
    tree[index].l_son = 0;
    tree[index].r_son = 0;
    return index++;
}

void Insert(int father ,int son, int R_or_L){
    if(R_or_L) tree[father].l_son = son;
    else tree[father].r_son = son;
}

int BuiltTree(void){
    int A = NewNode('A'); int B = NewNode('B'); int C = NewNode('C');
    int D = NewNode('D'); int E = NewNode('E'); int F = NewNode('F');
    int G = NewNode('G'); int H = NewNode('H'); int I = NewNode('I');
    int J = NewNode('J'); int K = NewNode('K'); int L = NewNode('L');
    Insert(C, B, 1); Insert(C, G, 0); Insert(B, E, 1); Insert(B, J, 0);
    Insert(G, A, 1); Insert(G, D, 0); Insert(E, K, 1); Insert(E, L, 0);
    Insert(A, H, 1); Insert(D, I, 0); Insert(K, F, 1);
    return C;
}

queue<int>use;

void Print_Tree1(int father){
    if(father){
        cout << tree[father].value << " ";
        Print_Tree1(tree[father].l_son);
        Print_Tree1(tree[father].r_son);
    }
}

void Print_Tree2(int father){
    if(father){
        cout << tree[father].value << " ";
        Print_Tree2(tree[father].r_son);
        Print_Tree2(tree[father].l_son);
    }
}


signed main()
{
    int head = BuiltTree();
    Print_Tree1(head);
    cout << endl;
    Print_Tree2(head);
}
```



虽然但是，在真正使用DFS的时候，更多是用递归来实现

其基本模板为：

```c++
int ans;
void DFS(层数， 其他参数){
    if(DFS的截至条件){
        更新ans;
        return;
    }else{
        (剪枝)
        for(....) 遍历可能出线的所有情况{
            if(这个情况没有被使用过){
                设置这个情况被使用过;
                DFS(层数+1， 其他参数);
                将这个情况设为没使用过;
            }
        }
    }
}
```

## 例题

