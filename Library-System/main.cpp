#include <bits/stdc++.h>
using namespace std;

const int max_number_books=100,max_number_users=100;

class Book
{
public:
    int id,quantity,borrow;
    string name,names_borrower[100];
    Book()
    {
        id=-1,quantity=0,borrow=0;
    }
    void set_book()
    {
        cout<<"Enter book info: id & name & total quantity: ";
        cin>>id>>name>>quantity;
    }
    bool borrow_book()
    {
        if(quantity==0)
            return false;
        borrow++;
        return true;
    }
    void return_book()
    {
        borrow--;
    }
    void print()
    {
        cout<<"id = "<<id<<" name = "<<name<<" total_quantity = "<<quantity<<" total_borrowed = "<<borrow<<endl;
    }
};

bool cmp_id(const Book &b1,const Book &b2)
{
    return b1.id<b2.id;
}
bool cmp_name(const Book &b1,const Book &b2)
{
    return b1.name<b2.name;
}

struct Name_id
{
    int id=-1;
    string name;
};
class User
{
public:
    int id,number_borrowed_books;
    Name_id borrowed_books[max_number_books];
    string name;
    User()
    {
        id=-1,number_borrowed_books=0;
    }
    void set_user()
    {
        cout<<"Enter user name & national id: ";
        cin>>name>>id;
    }
    bool borrow_book(const int &book_id,const string &book_name)
    {
        if(number_borrowed_books==max_number_books)
            return false;
        borrowed_books[number_borrowed_books].id=book_id;
        borrowed_books[number_borrowed_books++].name=book_name;
        return true;
    }
    void return_book(const string &book_name)
    {
        for(int i=0;i<number_borrowed_books;i++)
            if(borrowed_books[i].name==book_name)
            {
                for(int j=i+1;j<number_borrowed_books;j++)
                    borrowed_books[j-1]=borrowed_books[j];
                number_borrowed_books--;
                return;
            }
    }
    bool borrowed(const string &book_name)
    {
        for(int i=0;i<number_borrowed_books;i++)
            if(borrowed_books[i].name==book_name)
            {
                cout<<name<<endl;
                return true;
            }
        return false;
    }
    void print()
    {
        cout<<"user = "<<name<<" id = "<<id<<" borrowed books ids: ";
        for(int i=0;i<number_borrowed_books;i++)
            cout<<" "<<borrowed_books[i].id;
        cout<<endl;
    }
};

class Library_system
{
public:
    int len_books,len_users;
    Book books[max_number_books];
    User users[max_number_users];
    Library_system()
    {
        len_books=0,len_users=0;
        for(int i=0;i<max_number_books;i++)
            books[i]=Book();
        for(int i=0;i<max_number_users;i++)
            users[i]=User();
    }
    void run()
    {
        menu();
        int choice=-1;
        while(choice==-1)
        {
            cout<<"Enter your menu choice [1 - 10]: ";
            cin>>choice;
            if(choice==1)
                add_book();
            else if(choice==2)
                search_books_by_substring();
            else if(choice==3)
                print_who_borrowed_book_by_name();
            else if(choice==4)
                print_library_by_id();
            else if(choice==5)
                print_library_by_name();
            else if(choice==6)
                add_user();
            else if(choice==7)
                user_borrow_a_book();
            else if(choice==8)
                user_return_a_book();
            else if(choice==9)
                print_users();
            else if(choice==10)
                break;
            else
                cout<<"Wrong choice. Try again"<<endl;
            choice=-1;
        }
    }
    void menu()
    {
        cout<<"Library menu: \n"
            <<"1) Add book\n"
            <<"2) Search books by substring\n"
            <<"3) Print who borrowed book by name\n"
            <<"4) Print library by id\n"
            <<"5) Print library by name\n"
            <<"6) Add user\n"
            <<"7) User borrow a book\n"
            <<"8) User return a book\n"
            <<"9) Print users\n"
            <<"10) Exit\n"<<endl;
    }
    void add_book()
    {
        books[len_books++].set_book();
    }
    void add_user()
    {
        users[len_users++].set_user();
    }
    void search_books_by_substring()
    {
        string sub;
        cout<<"Enter substring of the book name: ";
        cin>>sub;
        bool not_found=1;
        for(int i=0;i<len_books;i++)
        {
            if(sub.length()>books[i].name.size())
                continue;
            string str;
            int siz=books[i].name.size()-sub.size()+1,k=sub.size();
            for(int j=0;j<k;j++)
                str+=books[i].name[j];
            if(sub==str)
            {
                not_found=0;
                cout<<books[i].name<<endl;
                continue;
            }
            for(int j=1;j<siz;j++)
            {
                str.erase(0,1);
                str+=books[i].name[j+k-1];
                if(sub==str)
                {
                    not_found=0;
                    cout<<books[i].name<<endl;
                    break;
                }
            }
//            for(int j=0;j<books[i].name.size();j++)
//                if(sub[0]==books[i].name[j])
//                {
//                    bool flag=1;
//                    for(int k=1;k<sub.size();k++)
//                        if(sub[k]!=books[i].name[j+k])
//                        {
//                            flag=0;
//                            break;
//                        }
//                    if(flag)
//                        cout<<books[i].name<<endl;
//                    break;
//                }
        }
        if(not_found)
                cout<<"No books with such substring\n";
    }
    void print_who_borrowed_book_by_name()
    {
        string book_name;
        cout<<"Enter book name: ";
        cin>>book_name;
        bool bro=0;
        for(int i=0;i<len_users;i++)
        {
            bro=users[i].borrowed(book_name);
        }
        if(!bro)
            cout<<"Invalid book name\n";
    }
    void print_library_by_id()
    {
        sort(books,books+len_books,cmp_id);
        print_books();
    }
    void print_library_by_name()
    {
        sort(books,books+len_books,cmp_name);
        print_books();
    }
    void print_books()
    {
        for(int i=0;i<len_books;i++)
            books[i].print();
    }
    void user_borrow_a_book()
    {
        string u_name,b_name;
        cout<<"Enter user name and book name: ";
        cin>>u_name>>b_name;
        int b_idx{-1},u_idx{-1};
        for(int i=0;i<len_books;i++)
            if(books[i].name==b_name)
            {
                b_idx=i;
                break;
            }
        books[b_idx].borrow_book();
        for(int i=0;i<len_users;i++)
            if(users[i].name==u_name)
            {
                u_idx=i;
                break;
            }
        users[u_idx].borrow_book(books[b_idx].id,books[b_idx].name);
    }
    void user_return_a_book()
    {
        string u_name,b_name;
        cout<<"Enter user name and book name: ";
        cin>>u_name>>b_name;
        int b_idx{-1},u_idx{-1};
        for(int i=0;i<len_books;i++)
            if(books[i].name==b_name)
            {
                b_idx=i;
                break;
            }
        books[b_idx].return_book();
        for(int i=0;i<len_users;i++)
            if(users[i].name==u_name)
            {
                u_idx=i;
                break;
            }
        users[u_idx].return_book(books[b_idx].name);
    }
    void print_users()
    {
        for(int i=0;i<len_users;i++)
            users[i].print();
    }
};
int main()
{
    Library_system().run();
    return 0;
}
