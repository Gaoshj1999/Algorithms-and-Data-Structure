//并查集(可用于判断图中是否有环)(union实现降低复杂度方法二，让高度小的树根指向大的树根)
//使用并查集可以造迷宫
#include <iostream>
using namespace std;
class disjointset
{
public:
    int *parent;
    int *height;
    disjointset(int size);
    int find(int i);              //找到根节点
    void set_union(int i, int j); //合并
};
disjointset::disjointset(int size)
{
    parent = new int[size];
    height = new int[size];
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
        height[i] = 1;
    }
}
int disjointset::find(int i)
{
    return parent[i] == i ? i : find(parent[i]);
}
void disjointset::set_union(int i, int j) //此即为加边过程
{
    int parenti = find(i);
    int parentj = find(j);
    if (parenti != parentj)
    {
        if (height[parenti] > height[parentj])
        {
            int temp = parenti;
            parenti = parentj;
            parentj = temp;
        }
        parent[parenti] = parentj;
        height[parentj] += height[parenti];
    }
    if (parenti == parentj) //判断回路
    {
        cout << "there is a circle" << endl;
    }
}