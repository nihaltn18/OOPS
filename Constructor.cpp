#include<iostream>
using namespace std;
class cons
{
    int i,j,*ptr;
    public:
    cons()
    {
        i=10;
        j=20;
        cout<<"default constructor called"<<endl;
    }
    cons(int a,int b)
    {
        i=a;
        j=b;
        cout<<"parametrised constructor called\n";
    }
    cons(cons &obj)
    {
        i=obj.i;
        j=obj.j;
        cout<<"copy constructor called\n";
    }
    cons(int k)
    {
    ptr=new int;
    *ptr=k;
    cout<<"dynamic constructor called\n";
    }
};
int main()
{
cons a,b(2,3),c(b),d(6);
int cc,dd;
cout<<"entrer the values for dynamic input constructor\n";
cin>>cc;
cin>>dd;
cons e(cc,dd);
}
