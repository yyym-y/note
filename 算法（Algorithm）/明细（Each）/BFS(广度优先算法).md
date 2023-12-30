# BFS(广度优先算法)

BFS是利用队列，实现逐级扩散，最后找到答案

BFS实际上与DFS类似，只不过DFS是利用递归，而BFS是通过队列来实现

相比于DFS，BFS所需要的空间比DFS要大

用二叉树来举例

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221205172113571.png" alt="image-20221205172113571" style="zoom:80%;" />

编码实现

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

signed main()
{
    queue<int>use;
    int head = BuiltTree();
    use.push(head);
    while(use.size()){
        if(use.front()){
            cout << tree[use.front()].value << " ";
            use.push(tree[use.front()].l_son);
            use.push(tree[use.front()].r_son);
        }
        use.pop();
    }
    return 0;
}
```



BFS基本模板是：

```
queue<...> BFS
queue.push_back(第一个数据)
while(!BFS.empty()) 队列不为空{
	(剪枝)
	for(遍历所有情况)
		判断情况是否符合：符合结束
		BFS.push_back(将子情况放入)
	BFS.pop_front()弹出判断完的情况
}
```



## 例题

