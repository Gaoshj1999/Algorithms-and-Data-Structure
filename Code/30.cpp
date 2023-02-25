//树的孩子兄弟表示法存储方式(left child right-silbing binary tree)
#include <iostream>
using namespace std;
template <class T>
class tree
{
public:
    T data;
    tree<T> *leftchild, nextsibling;
    tree();
};
template <class T>
tree<T>::tree()
{
    data = NULL;
    leftchild = nullptr;
    nextsibling = nullptr;
}