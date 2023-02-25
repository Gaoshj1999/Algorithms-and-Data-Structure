//二叉搜索树(链表实现)//这个例子告诉我们，很多情况下下一些操作不写进类中而是在类外通过把类传进去实现会更好，因为这样方便递归调用//傻了，在类内定义函数也可以实现递归调用的,通过传引用
#include <iostream>
using namespace std;
template <class T>
class node
{
public:
    T data;
    node<T> *leftchild;
    node<T> *rightchild;
    node();
};
template <class T>
node<T>::node()
{
    data = NULL;
    leftchild = nullptr;
    rightchild = nullptr;
}
template <class T>
class binarysearchtree
{
public:
    node<T> *root;
    int n;
    binarysearchtree();
    ~binarysearchtree();
    T elemmax();                        //返回最大元素
    T elemmin();                        //返回最小元素
    bool find(T elem);                  //判断是否有该元素
    node<T> *findback(T elem);          //返回找到元素的地址
    node<T> *findbackparent(T elem);    //返回找到元素的双亲的地址
    void insert(T elem, node<T> *root); //向树中插入插入一个元素
    void erase(T elem, node<T> *root);  //删除一个元素并调整树
    int getsize();                      //所有节点的个数
};
template <class T>
binarysearchtree<T>::binarysearchtree()
{
    root = new node<T>;
    root->data = NULL;
    root->leftchild = nullptr;
    root->rightchild = nullptr;
    n = 0;
}
template <class T>
binarysearchtree<T>::~binarysearchtree()
{
    delete root;
}
template <class T>
int binarysearchtree<T>::getsize()
{
    return n;
}
template <class T>
T binarysearchtree<T>::elemmin()
{
    node<T> *temp = root;
    if (n == 0)
    {
        cout << "there is no node in the tree" << endl;
        return static_cast<T>(NULL);
    }
    while (temp->leftchild != nullptr)
    {
        temp = temp->leftchild;
    }
    return temp->data;
}
template <class T>
T binarysearchtree<T>::elemmax()
{
    node<T> *temp = root;
    if (n == 0)
    {
        cout << "there is no node in the tree" << endl;
        return static_cast<T>(NULL);
    }
    while (temp->rightchild != nullptr)
    {
        temp = temp->rightchild;
    }
    return temp->data;
}
template <class T>
bool binarysearchtree<T>::find(T elem)
{
    node<T> *temp = root;
    if (n == 0)
    {
        return false;
    }
    while (temp->leftchild != nullptr || temp->rightchild != nullptr)
    {
        if (elem < temp->data && temp->leftchild != nullptr)
        {
            temp = temp->leftchild;
        }
        else if (elem > temp->data && temp->rightchild != nullptr)
        {
            temp = temp->rightchild;
        }
        else
        {
            break;
        }
    }
    if (temp->data == elem)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <class T>
node<T> *binarysearchtree<T>::findback(T elem) //返回找到元素的地址
{
    node<T> *temp = root;
    if (n == 0)
    {
        return nullptr;
    }
    while (temp->leftchild != nullptr || temp->rightchild != nullptr)
    {
        if (elem < temp->data && temp->leftchild != nullptr)
        {
            temp = temp->leftchild;
        }
        else if (elem > temp->data && temp->rightchild != nullptr)
        {
            temp = temp->rightchild;
        }
        else
        {
            break;
        }
    }
    if (temp->data == elem)
    {
        return temp;
    }
    else
    {
        return temp;
    }
}
template <class T>
node<T> *binarysearchtree<T>::findbackparent(T elem) //返回找到元素的双亲的地址
{
    node<T> *temp = root;
    node<T> *tempparent;
    if (n <= 1)
    {
        return nullptr;
    }
    while (temp->leftchild != nullptr || temp->rightchild != nullptr)
    {
        if (elem < temp->data && temp->leftchild != nullptr)
        {
            tempparent = temp;
            temp = temp->leftchild;
        }
        else if (elem > temp->data && temp->rightchild != nullptr)
        {
            tempparent = temp;
            temp = temp->rightchild;
        }
        else
        {
            break;
        }
    }
    if (temp->data == elem)
    {
        return tempparent;
    }
    else
    {
        return tempparent;
    }
}
template <class T>
void binarysearchtree<T>::insert(T elem, node<T> *root)
{
    node<T> *temp = root;
    node<T> *beforetemp;
    if (n < 1)
    {
        temp->data = elem;
    }
    else
    {
        while (temp != nullptr)
        {
            if (elem < temp->data)
            {
                beforetemp = temp;
                temp = temp->leftchild;
            }
            else if (elem > temp->data)
            {
                beforetemp = temp;
                temp = temp->rightchild;
            }
            else
            {
                cout << "fail" << endl;
                break;
            }
        }
        if (beforetemp->data > elem)
        {
            beforetemp->leftchild = new node<T>;
            beforetemp->leftchild->data = elem;
        }
        else if (beforetemp->data < elem)
        {
            beforetemp->rightchild = new node<T>;
            beforetemp->rightchild->data = elem;
        }
        else
        {
        }
    }
    n++;
}
template <class T>
void binarysearchtree<T>::erase(T elem, node<T> *root)
{
    if (find(elem))
    {
        node<T> *temp = findback(elem);
        node<T> *temp2;
        if (temp->leftchild == nullptr && temp->rightchild == nullptr)
        {
            if (n == 1)
            {
                root->data = NULL;
            }
            else
            {
                temp2 = findbackparent(temp->data);
                if (temp2->leftchild == temp)
                {
                    temp2->leftchild = nullptr;
                }
                else
                {
                    temp2->rightchild = nullptr;
                }
                delete temp;
            }
        }
        else if (temp->rightchild == nullptr && temp->leftchild != nullptr)
        {
            if (temp == root)
            {
                root = temp->leftchild;
                delete temp;
            }
            else
            {
                temp2 = findbackparent(elem);
                if (temp2->leftchild == temp)
                {
                    temp2->leftchild = temp2->leftchild->leftchild;
                    delete temp;
                }
                else
                {
                    temp2->rightchild = temp2->rightchild->leftchild;
                    delete temp;
                }
            }
        }
        else
        {
            temp2 = temp->rightchild;
            {
                if (temp2->leftchild == nullptr)
                {
                    temp->data = temp2->data;
                    temp->rightchild = temp2->rightchild;
                    delete temp2;
                }
                else
                {
                    while (temp2->leftchild != nullptr)
                    {
                        temp2 = temp2->leftchild;
                    }
                    node<T> *temp3 = findbackparent(temp2->data);
                    temp->data = temp2->data;
                    temp3->leftchild = nullptr;
                    delete temp2;
                }
            }
        }
        n--;
    }
}
template <class T>
void preordertraverse(node<T> *root) //递归定义先序遍历并输出每个点的值
{
    if (root)
    {
        cout << root->data << " ";
        preordertraverse(root->leftchild);
        preordertraverse(root->rightchild);
    }
}
template <class T>
void inordertraverse(node<T> *root)
{
    if (root != nullptr)
    {
        inordertraverse(root->leftchild);
        cout << root->data << " ";
        inordertraverse(root->rightchild);
    }
}
template <class T>
void postordertraverse(node<T> *root)
{
    if (root)
    {
        postordertraverse(root->leftchild);
        postordertraverse(root->rightchild);
        cout << root->data << " ";
    }
}
int main()
{
    binarysearchtree<int> tree1;
    tree1.insert(1, tree1.root);
    tree1.insert(9, tree1.root);
    tree1.insert(4, tree1.root);
    tree1.insert(6, tree1.root);
    tree1.insert(5, tree1.root);
    tree1.insert(3, tree1.root);
    tree1.insert(7, tree1.root);
    tree1.insert(8, tree1.root);
    tree1.insert(2, tree1.root);
    preordertraverse(tree1.root);
    cout << endl;
    inordertraverse(tree1.root);
    cout << endl;
    postordertraverse(tree1.root);
    cout << endl;
    cout << tree1.elemmax() << endl;
    cout << tree1.elemmin() << endl;
    cout << tree1.findbackparent(4)->data << endl;
    cout << tree1.find(1) << endl;
    tree1.erase(9, tree1.root);
    cout << tree1.findbackparent(4)->data << endl;
    tree1.erase(4, tree1.root);
    inordertraverse(tree1.root);
    cout << endl;
    cout << tree1.elemmax() << endl;
    preordertraverse(tree1.root);
    return 0;
}
