//线性表(顺序存储网上例子)
#include <iostream>
using namespace std;
typedef int Elem;
class List
{
public:
    List(int size);
    ~List();
    void ClearList();                                 // 将数组长度设为0
    bool ListEmpty();                                 // 判断数组是否为空
    int ListLength();                                 // 获取数组长度
    bool GetElem(int i, Elem *e);                     // 查找指定下标元素
    int LocateElem(Elem *e);                          // 查找指定元素
    bool PriorElem(Elem *currentElem, Elem *preElem); // 查找元素的前驱元素
    bool NextElem(Elem *currentElem, Elem *nextElem); // 查找元素的后继元素
    void ListTraverse();                              // 遍历线性表，输出元素
    bool ListInsert(int i, Elem *e);                  // 在指定位置插入一个元素
    bool ListDelete(int i, Elem *e);                  // 删除指定位置元素
private:
    int *m_pList;  // 指向一块内存
    int m_iSize;   // 内存的大小
    int m_iLength; // 数组的长度
};

List::List(int size)
{
    m_iSize = size;
    m_pList = new Elem[m_iSize];
    m_iLength = 0;
}

List::~List()
{
    delete[] m_pList; // 释放数组内存
    m_pList = NULL;
}

void List::ClearList()
{
    m_iLength = 0;
}

bool List::ListEmpty()
{
    return m_iLength == 0 ? true : false;
}

int List::ListLength()
{
    return m_iLength;
}

bool List::GetElem(int i, Elem *e)
{
    if (i < 0 || i >= m_iSize)
    {
        return false;
    }
    *e = m_pList[i];
    return true;
}

int List::LocateElem(Elem *e)
{
    for (int i = 0; i < m_iLength; i++)
    {
        if (m_pList[i] == *e)
        {
            return i;
        }
    }
    return -1;
}

bool List::PriorElem(Elem *currentElem, Elem *preElem)
{
    int temp = LocateElem(currentElem); // 查找元素的序号
    if (temp == -1)
        return false;
    else if (temp == 0)
        return false;
    else
    {
        *preElem = m_pList[temp - 1];
        return true;
    }
}

bool List::NextElem(Elem *currentElem, Elem *nextElem)
{
    int temp = LocateElem(currentElem); // 查找元素的序号
    if (temp == -1)
        return false;
    else if (temp == m_iLength - 1)
        return false;
    else
    {
        *nextElem = m_pList[temp + 1];
        return true;
    }
}

void List::ListTraverse()
{
    for (int i = 0; i < m_iLength; i++)
    {
        cout << m_pList[i] << endl;
    }
}

bool List::ListInsert(int i, Elem *e)
{
    if (i < 0 || i > m_iLength)
        return false;
    for (int k = m_iLength - 1; k >= i; k--)
    {
        m_pList[k + 1] = m_pList[k];
    }
    m_pList[i] = *e;
    m_iLength++;
    return true;
}

bool List::ListDelete(int i, Elem *e)
{
    if (i < 0 || i > m_iLength)
        return false;
    *e = m_pList[i];
    for (int k = i + 1; k < m_iLength; k++)
    {
        m_pList[k - 1] = m_pList[k];
    }
    m_iLength--;
    return true;
}
int main()
{
    Elem temp;
    Elem arry[11] = {3, 5, 7, 2, 9, 1, 8};
    List *list1 = new List(10);
    cout << "length:" << list1->ListLength() << endl;
    for (int i = 0; i < 7; i++)
    {
        list1->ListInsert(i, &arry[i]);
    }
    cout << "length:" << list1->ListLength() << endl;
    list1->ListDelete(0, &temp);
    cout << temp << endl;
    list1->PriorElem(&arry[4], &temp);
    cout << temp << endl;
    list1->NextElem(&arry[4], &temp);
    cout << temp << endl;
    list1->ListTraverse();
    delete list1;
    return 0;
}
