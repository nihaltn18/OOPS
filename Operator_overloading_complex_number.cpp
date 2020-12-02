#include<iostream>
using namespace std;
class complex
{
    int real, imag;
public:
    complex()
    {
        real=0;
        imag=0;
    }
    complex(int r, int i)
    {
        real=r;
        imag=i;
    }
    void display()
    {
        cout<<"("<<real<<")"<<"+ i("<<imag<<")"<<endl;
    }
    complex operator+(complex obj)
    {
        return(complex(real+obj.real, imag+obj.imag)) ;
    }
    friend complex operator-(complex obj1, complex obj2) ;
};
complex operator- (complex obj1, complex obj2)
{
    return(complex(obj1.real-obj2.real,obj1.imag-obj2.imag));
}
int main()
{
    cout << "Hello,World!\n";
    complex c1(1, 2), c2(3, 4) ;
    complex c3=c1+c2;
    complex c4=c1-c2;
    c1. display() ;
    c2. display() ;
    c3. display() ;
    c4. display() ;
    return 0;
}
