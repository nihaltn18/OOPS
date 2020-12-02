#include<iostream>
using namespace std;
class matri
{
    int mat[10][10];
    int row,col;
public:
    matri(int a,int b)
    {
        row=a;
        col=b;
    }
    void read()
    {
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                cout<<"enter the data of element of row "<<i+1<<" column "<<j+1<<endl;
                cin>>mat[i][j];
            }
        }
    }
    void display()
    {
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                cout<<mat[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
    friend matri transpose(matri m);
};
matri transpose (matri m)
{
    matri n(m.col,m.row);
    for (int i=0; i<n.row; i++)
    {
        for (int j=0; j<n.col; j++)
        {
            n.mat[i][j]=m.mat[j][i];
        }
    }
    return n;
}
int main()
{
    int a,b;
    cout<<" enter the number of rows and column in the original matrix\n";
    cin>>a;
    cin>>b;
    matri m1(a,b);
    m1.read();
    m1.display();
    cout<<"\n\n";
    matri m2=transpose (m1);
    m2.display();
    cout << "Hello,World!\n";
    return 0;
}
