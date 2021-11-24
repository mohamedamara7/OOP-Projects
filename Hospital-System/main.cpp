#include <bits/stdc++.h>
#define fastIO() do {ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); } while (0)
using namespace std;

const int max_queue{5},max_specialization{20};
class Hospital_queue
{
public:
    string name[max_queue];
    int status[max_queue],len,spec;
    Hospital_queue()
    {
        len=0;
        spec=-1;
    }
    Hospital_queue(const int &spec_)
    {
        len=0;
        spec=spec_;
    }
    bool add_end(const string &name_,const int &status_)
    {
        if(len==max_queue)
            return false;
        name[len]=name_,status[len++]=status_;
        return true;
    }
    bool add_front(const string &name_,const int &status_)
    {
        if(len==max_queue)
            return false;
        for(int i=len-1;i>=0;i--)
            name[i+1]=name[i],status[i+1]=status[i];
        name[0]=name_;
        status[0]=status_;
        len++;
        return true;
    }
    void remove_front()
    {
        if(len==0)
        {
            cout<<"No patients at the moment. Have rest, Dr\n";
        }
        else
        {
            cout<<name[0]<<" please go with the Dr\n";
            for(int i=1;i<len;i++)
                name[i-1]=name[i],status[i-1]=status[i];
            len--;
        }
    }
    void print()
    {
        if(len)
        {
            cout<<"There are "<<len<<" patients in specialization "<<spec<<endl;
            for(int i=0;i<len;i++)
                cout<<name[i]<<" "<<(status[i]?"urgent":"regular")<<endl;
            cout<<endl;
        }
    }
};

class Hospital_system
{
public:
    Hospital_queue hq[max_specialization];
    Hospital_system()
    {
        for(int i=0;i<max_specialization;i++)
            hq[i]=Hospital_queue(i+1);
    }
    void run()
    {
        //fastIO();
        int choice;
        while(true)
        {
            choice=menu();
            if(choice==1)
                add();
            else if(choice==2)
                print();
            else if(choice==3)
                pick();
            else
                break;
        }
    }
    int menu()
    {
        int choi;
        while(true)
        {
            cout<<"Enter your choice: \n"
                <<"1) Add a new patient \n"
                <<"2) Print all patients \n"
                <<"3) Get next patient \n"
                <<"4) Exit "<<endl;
            cin>>choi;
            if(!(choi>=1&&choi<=4))
            {
                cout<<"Invalid choice. Try again! \n";
            }
            else
                return choi;
        }
    }
    void add()
    {
        int spec;
        bool status;
        string name;
        cout<<"Enter specialization, name and status: ";
        cin>>spec>>name>>status;
        bool st;
        if(status)
            st=hq[--spec].add_front(name,status);
        else
            st=hq[--spec].add_end(name,status);
        if(!st)
            cout<<"Sorry we can't add more patients for this specialization\n";
    }
    void print()
    {
        cout<<"******************************\n";
        for(int i=0;i<max_specialization;i++)
        {
            hq[i].print();
        }
    }
    void pick()
    {
        int spec;
        cout<<"Enter specialization: ";
        cin>>spec;
        hq[--spec].remove_front();
    }
};
int main()
{
    Hospital_system{}.run();
    return 0;
}
