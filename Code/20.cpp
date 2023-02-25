//交换排序(限域冒泡排序)
#include <iostream>
using namespace std;
template <class T>
void myswap(T &a, T &b)//标准库中模板自带swap函数，因此不能再命名为swap了,但是如果不是申明模板的话就可以使用
{
    T temp = a;
    a = b;
    b = temp;
}
template <class T>
void rangelimitingbubblesort(T a[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int change=0;
        for (int j = 0; j < i; j++)
        {
            if (a[j + 1] < a[j])
            {
                myswap(a[j + 1], a[j]);
                change = j;
            }
        }
        i = change+1;//这是因为还要执行i--
    }
}
int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    rangelimitingbubblesort(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}