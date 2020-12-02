#include<iostream>
using namespace std;
class vehicle
{
    int *registration_number;
    static int count;
public:
    vehicle ()
    {
        count++;
    }
    void setregno()
    {
        cout<<"enter the registration number of the vehicle\n";
        cin>>*registration_number;
    }
    void getregno()
    {
        cout<<"registration number of the given vehicle is "<<*registration_number<<endl;
    }
    static int getvehiclecount()
    {
        return count;
    }
    ~vehicle() 
    {
    count --;
    delete[]  registration_number;
    }
};
vehicle list[1000];
int i=0;
int vehicle::count=0;
int main()
{
    while (1)
    {
        cout<<"to insert an vehicle info enter 1\n";
        cout<<"to display all vehicle info enter 2\n";
        cout<<"to get the vehicle count enter 3\n";
        cout<<"to quit enter 4\n";
        int o;
        cin>>o;
        if(o==1)
        {
            vehicle v;
            v.setregno();
            list[i]=v;
            i++;
        }
        if (o==2)
        {
            int k=0;
            for (k=0; k<i; k++)
            {
                list[k].getregno();
            }
        }
        if (o==3)
        {
            int z=vehicle::getvehiclecount();
            cout<<"number of vehicle at this stage is :"<<z<<endl;
        }
        if (o==4)
        {
            break;
        }
        else
        {
            cout<<"enter a valid option\n";
        }
    }
}
