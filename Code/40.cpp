//并查集(可用于判断图中是否有环)(find实现降低复杂度方法一，让所有节点在找寻一次后指向根节点)
#include <iostream>
using namespace std;
class disjointset
{
public:
    int *parent;
    int *sz;
    disjointset(int size);
    int find(int i);              //找到根节点
    void set_union(int i, int j); //合并
};
disjointset::disjointset(int size)
{
    parent = new int[size];
    sz = new int[size];
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }
}
int disjointset::find(int i) //路径压缩
{
    return parent[i] = parent[i] == i ? i : find(parent[i]);
}
void disjointset::set_union(int i, int j) //按秩合并//此即为加边过程
{
    int parenti = find(i);
    int parentj = find(j);
    if (parenti != parentj)
    {
        if (sz[parenti] > sz[parentj])
        {
            int temp = parenti;
            parenti = parentj;
            parentj = parenti;
        }
        parent[parenti] = parentj;
        sz[parentj] += sz[parentj];
    }
    if (parenti == parentj) //判断回路
    {
        cout << "there is a circle" << endl;
    }
}