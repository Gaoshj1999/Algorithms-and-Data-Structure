//树的双亲表示法存储方式(方便找双亲)
#include <iostream>
using namespace std;
template <class T>
class treenode
{
public:
    T data;
    int parent;
};
template <class T>
class tree
{
public:
    treenode<T> *root;
    tree();
    ~tree() {}
    void create(T *array, int n); //创建一棵以10的倍数分层从1-100的树
};
template <class T>
tree<T>::tree()
{
    root = new treenode<T>[110];
    root->data = NULL;
    root->parent = -1;
}
template <class T>
void tree<T>::create(T *array, int n)
{
    for (int i = 1; i <= n; i++)
    {
        root[i].data = array[i - 1];
        root[i].parent = root[i].data / 10;
    }
}
int main()
{
    int a[100];
    for (int i = 0; i < 100; i++)
    {
        a[i] = i + 1;
    }
    tree<int> tree1;
    tree1.create(a, 100);
    for (int i = 1; i <= 100; i++)
    {
        cout << tree1.root[i].data << " ";
    }
    return 0;
}