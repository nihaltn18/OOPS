#include<iostream>
using namespace std;
class mat
{
    int a, b, **matrix;
public:
    mat()
    {
        a=0;
        b=0;
    }
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
    friend ostream& operator<<(ostream &out, const mat &m1) ;
    friend istream& operator>>(istream &in, mat &m1) ;
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
    void display ()
    {
        for (int i=0; i<a; i++)
        {
            for (int j=0; j<b; j++)
            {
                cout<<matrix [i][j]<<"/t";
            }
            cout<<"\n";
        }
    }
    friend mat operator*(mat m1, int k) ;
    friend mat operator*(mat m1, mat m2) ;
};

ostream& operator<<(ostream &out, const mat &m1)
{
    for (int i=0; i<m1.a; i++)
    {
        for (int j=0; j<m1.b; j++)
        {
            out<<m1.matrix [i][j]<<"\t";
        }
        out<<endl;
    }
    return out;
}
mat operator*(mat m1, mat m2)
{
    if(m1.b==m2.a)
    {
        mat m3(m1.a, m2. b, 1) ;
        for (int r=0; r<m1.a; r++)
        {
            for (int c=0; c<m2.b; c++)
            {
                int sum=0;
                for(int i=0; i<m1.b; i++)
                {
                    sum=sum+(m1.matrix[r][i]*m2.matrix[i][c]) ;
                }
                m3.matrix [r][c]=sum;
            }
        }
        return m3;
    }
    return m1;
}
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
    cout<<"enter the order\n";
    cin>>r>>c;
    mat m1(r, c) ;
    cout<<"enter the order\n";
    cin>>r>>c;
    mat m2(r, c) ;
    cout<<"matrix 1 is\n";
    cout<<m1;
    cout<<"matrix 2 is\n";
    cout<<m2;
    cout<<"\n\n";
    mat m5=m1*m2;
    cout<<m5;
    return 0;
}
