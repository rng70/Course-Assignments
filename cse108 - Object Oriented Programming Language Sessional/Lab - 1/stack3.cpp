#include <iostream>
#define SIZE 10

using namespace std;


class stack
{
    char s[SIZE]; /// holds the stack
    int top;      /// index of top of stack

    public :
    void init()
    {
        top = 0;
    }

                 /// Push a character
    void push(char c)
    {
        if(top == SIZE)
        {
            cout<<"Stack is full"<<endl;
            return;
        }
        s[top++] = c;
    }

                /// Pop a character
    char pop()
    {
        if(top == 0)
        {
            cout<<"Stack is empty"<<endl;
            return 0; /// return null on empty stack
        }
        return s[--top];
    }

    int isEmpty()
    {
        return top == 0;
    }

};



int main(void)
{
    stack s1;

	s1.init();
	s1.push('a');
	s1.push('b');
	s1.push('c');


    while(!s1.isEmpty())
	{
	    cout<<"Pos Stack: "<<s1.pop()<<endl;
		///printf("Pop stack: %c\n", s1.pop());
	}

	return 0;
}
