#include<iostream>
using namespace std;
class mat
{
    int a, b, **matrix;
public:
    mat(int c,int d)
    {
        a=c;
        b=d;
        matrix=new int*[a];
        for (int i=0; i<a; i++)
        {
            matrix [i]=new int[b];
        }
        cout<<"enter the matrix details\n";
        for (int i=0; i<a; i++)
        {
            for(int j=0; j<b; j++)
            {
                cout<<"enter the data for row "<<i+1<<" and column "<<j+1<<endl;
                cin>>matrix[i][j];
            }
        }
    }
    mat(int c,int d, int e)
    {
        a=c;
        b=d;
        matrix=new int*[a];
        for (int i=0; i<a; i++)
        {
            matrix [i]=new int[b];
        }
        for (int i=0; i<a; i++)
        {
            for(int j=0; j<b; j++)
            {
                matrix[i][j]=0;
            }
        }
    }
    void display()
    {
        for (int i=0; i<a; i++)
        {
            for (int j=0; j<b; j++)
            {
                cout<<matrix [i][j]<<"\t";
            }
            cout<<endl;
        }
    }
    mat operator+(mat m)
    {
        mat m1(m.a,m.b,1) ;
        for (int i=0; i<a; i++)
        {
            for (int j=0; j<b; j++)
            {
                m1. matrix[i][j]=matrix[i][j]+m.matrix[i][j];
            }
        }
        return m1;
    }
    mat operator-(mat m)
    {
        mat m1(a,b,1) ;
        for (int i=0; i<a; i++)
        {
            for (int j=0; j<b; j++)
            {
                m1. matrix[i][j]=matrix[i][j]-m.matrix[i][j];
            }
        }
        return m1;
    }
    friend mat operator*(mat m1, int k) ;
};
mat operator*(mat m1, int k)
{
    mat m2(m1.a, m1. b, 1) ;
    for(int i=0; i<m1.a; i++)
        for(int j=0; j<m1.b; j++)
            m2. matrix[i][j]=m1.matrix[i][j]*k;
    return m2;
}
int main()
{
    int r, c;
    cout<<"enter the order of the matrix\n";
    cin>>r>>c;
    mat m1(r, c) ;
    mat m2(r, c) ;
    mat m3=m1+m2;
    mat m4=(m1+m2)*5;
    cout<<"matrix 1 is\n";
    m1. display () ;
    cout<<"matrix 2 is\n";
    m2. display () ;
    cout<<"sum of the matrix is\n";
    m3. display() ;
    cout<<"sum of all the two matrix*5 is\n";
    m4. display() ;
    return 0;
}
