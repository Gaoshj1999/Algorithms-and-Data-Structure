//树的带双亲的孩子链表表示法
#include <iostream>
using namespace std;
class node
{
public:
    int child;
    node *next;
    node();
};
node::node()
{
    child = NULL;
    next = nullptr;
}
template <class T>
class treenode
{
public:
    T data;
    node *firstchild;
    int parent;
};
template <class T>
class tree
{
public:
    treenode<T> *root;
    tree();
    ~tree() {}
};
template <class T>
tree<T>::tree()
{
    root = new treenode[100];
    root->data = NULL;
    root->firstchild = nullptr;
    root->parent = -1;
}