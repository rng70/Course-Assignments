///                        "Al Arafat Tanin "   "1705070"
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<time.h>
#include<cstdlib>
#define ll long long
#define pb push_back
#define sc scanf
#define pf printf
#define Max 10
#define ug GSM
#define MP make_pair
#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define RE(i,n) FOR(i,1,n)
#define REP(i,n) FOR(i,0,(int)(n)-1)
#define R(i,n) REP(i,n)
#define VI vector<int>
#define PII pair<int,int>
#define LD long double
#define FI first
#define SE second
#define st FI
#define nd SE
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

using namespace std;

class Stack
{
    int *element, topp, size_s, total_element ;
public:
    Stack();
    Stack(int n);
    ~Stack();
    void Push(int );
    void Push(int*, int);
    void Push(Stack& );
    int Pop();
    int Top();
    int Size();
    double Similarity(Stack &);
    void print_stack();
    void Resize(int new_size);
    void exit();
};
Stack::Stack()
{
    cout<<"This is the constructor without initialization the stack but allocating memory dynamically "<<endl;
    total_element = 0 ;
    topp = 0 ;
    size_s = Max ;
    element = new int[size_s];
}
Stack::Stack(int x)
{
    cout<<"This is the constructor without initialization but allocating memory dynamically for "<<x<<" elements."<<endl;
    topp = 0 ;
    size_s = x ;
    element = new int[size_s];
}
Stack::~Stack()
{
    cout<<"Hi I am destructor.Dynamically allocated memory was freed by me that was for the current Stack."<<endl<<endl;
    delete[] element;
}
void Stack::Resize(int now_size)
{
    int *mystack = new int[now_size];
    for(int i = 0; i < total_element; i++)
    {
        mystack[i] = element[i];
    }
    delete[] element ;
    element = new int[now_size];
    for(int i = 0; i < total_element; i++)
    {
        element[i] = mystack[i] ;
    }
    size_s = now_size;
    delete[] mystack ;
}
void Stack::Push(int n)
{
    if(total_element <= size_s-1)
    {

        element[topp]=n;
        topp++;
        total_element++;
    }
    else
    {
        cout<<" Insufficient memory for taking 1 extra input more than allocated memory for input . So the stack is going to be resized"<<endl;
        Resize( total_element + 1 );
        element[topp]=n;
        topp++;
        total_element++;
    }
}
void Stack::Push( int *a, int size_of_array )
{
    if((topp+size_of_array) <= size_s)
    {
        for(int i = 0 ; i < size_of_array ; i++)
        {
            element[topp]=a[i];
            topp++;
            total_element++;
        }
    }
    else
    {
        cout<<" Insufficient memory for taking "<<topp+size_of_array-size_s<<" extra input more than allocated memory for input . So the stack is going to be resized"<<endl;
        Resize(topp+size_of_array);
        for(int i = 0 ; i < size_of_array ; i++)
        {
            element[topp]=a[i];
            topp++;
            total_element++;
        }
    }
}
void Stack::Push(Stack &st)
{
    int siz = st.Size();
    if((topp+siz) <= size_s)
    {
        for(int i = 0 ; i< siz; i++)
        {
            element[topp] = st.element[siz-i-1];
            topp++;
            total_element++;
        }
    }
    else
    {
        cout<<" Insufficient memory for taking "<<topp+siz-size_s<<" extra input more than allocated memory for input . So the stack is going to be resized"<<endl;
        Resize(topp+siz);
        for(int i = 0 ; i< siz; i++)
        {
            element[topp] = st.element[siz-i-1];
            topp++;
            total_element++;
        }
    }
}
int Stack::Pop()
{
    int t;
    topp--;
    if((topp)<=0)
    {
        cout<<"The Stack is empty "<<endl;
        return 0 ;
    }
    else
    {
        t = element[topp];
        total_element--;
    }
        int k = this->Size();
        Resize(k);
        return t;
}
int Stack::Top()
{
    if(topp==0)
    {
        cout<<"This Stack is empty"<<endl;
        return 0;
    }
    else
    {
        topp--;
        int k = element[topp];
        topp++;
        return k;
    }
}
int Stack::Size()
{
    return total_element;
}
double  Stack::Similarity(Stack &st)
{
    int count_similar = 0 ;
    int i,j;
    cout<<endl;
    for( i = this->Size()-1,j = st.Size()-1; i >= 0 &&  j >= 0 ; i--, j-- )
    {
        if(this->element[i]==st.element[j])
        {
            count_similar++;
        }
    }
    cout<<"\tMatch found for "<<count_similar<<" elements "<<endl;
    int num = this->Size() + st.Size();
    cout<<"\tAverage size of two stacks is "<<(double)num/2.0<<endl;
    double match = (double)(2*count_similar)/(double)(num);
    return match ;
}
void Stack::print_stack()
{
    cout<<"   Elements in the current Stack are : ";
    for(int i = 0; i< total_element ; i++)
    {
        cout<<element[i]<<" ";
    }
    cout<<endl<<endl;
}
void Stack::exit()
{
    cout<<endl<<"Now you program is terminating and all the memory that was allocated dynamically was freed"<<endl;
    cout<<endl<<"This is the final output : "<<endl;
    cout<<"\t\tElements in the current Stack are : "<<endl;
    cout<<"\t\t\t\t";
    for(int i = 0; i< total_element ; i++)
    {
        cout<<element[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"\t\t\t\tGood bye "<<endl<<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout<<endl;

    int n,choice,u=0;
    string key,s1 = "Y",s2 = "y",s3="N";
    Stack mainStack;
    do
    {
        cout<<"\t1. Push an Element"<<endl;
        cout<<"\t2. Push an Array"<<endl;
        cout<<"\t3. Push a Stack"<<endl;
        cout<<"\t4. Pop"<<endl;
        cout<<"\t5. Top"<<endl;
        cout<<"\t6. Size"<<endl;
        cout<<"\t7. Similarity"<<endl;
        cout<<"\t8. Exit"<<endl;
        cout<<"Enter the number of operation do you want to do"<<endl;
        cin>>choice;
        if(choice == 1)
        {
            cout<<"Enter the number that you want to push"<<endl;
            cin>>n;
            mainStack.Push(n);
            cout<<endl;
            mainStack.print_stack();
        }
        else if(choice == 2)
        {
            cout<<"Enter how many integer numbers do you want to push"<<endl;
            int op;
            cin>>op;
            int *integer;
            integer = new int[op];
            cout<<"Enter the elements"<<endl;
            for(int i=0 ; i < op ; i++)
            {
                cin>>integer[i];
            }
            mainStack.Push(integer, op);
            delete[] integer;
            cout<<endl;
            mainStack.print_stack();
        }
        else if(choice == 3)
        {
            int k;
            cout<<"How many elements do you want to push?"<<endl;
            cin>>k;
            Stack *tempStack = new Stack(k);
            for(int i = 0 ; i < k ; i++)
            {
                int nn;
                cin>>nn;
                tempStack->Push(nn);
            }
            mainStack.Push( *tempStack );
            cout<<endl;
            mainStack.print_stack();
            delete tempStack ;
        }
        else if(choice == 4)
        {
            int k = mainStack.Pop();
            if( k )
            {
                cout<<"The removed element is "<<k<<endl;
            }
            mainStack.print_stack();
        }
        else if(choice == 5)
        {
            int k = mainStack.Top();
            if( k )
                cout<<"The top element is "<<k<<endl;
        }
        else if(choice == 6)
        {
            int k = mainStack.Size();
            cout<<"The size of the stack is "<<k<<endl;
        }
        else if(choice == 7)
        {
            int k;
            cout<<"How many elements do you want to check ?"<<endl;
            cin>>k;
            Stack *tempStack = new Stack(k);
            cout<<"\tEnter the numbers :"<<endl;
            for(int i = 0 ; i < k ; i++)
            {
                int nn;
                cin>>nn;
                tempStack->Push(nn);
            }
            double found = mainStack.Similarity( *tempStack );
            cout<<"\tSimilarity Score : "<<found<<endl;
            delete tempStack ;
            cout<<endl;
            mainStack.print_stack();
        }
        else if(choice == 8)
        {
            mainStack.exit();
            u=1;
        }
        if(u)
        {
        key = s3;
        }
       else
       {
          cout<<"\tDo you want to do operation again?"<<endl;
          cout<<"\tPress Y for Yes or N for No"<<endl;
         cin>>key;
       }
    }
    while(key == s1 || key == s2);
    return 0;
}
