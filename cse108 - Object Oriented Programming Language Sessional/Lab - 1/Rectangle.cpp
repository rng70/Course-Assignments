#include<iostream>

using namespace std;
class Rectangle
{
        int length,width,area;

public:

        Rectangle(int a,int b)
        {
          cout<<"In constructor"<<endl;
          length = a;
          width  = b;
        }
       /* void setvalue(int x)
        {
                length=x;
        }
        void setvalue2(int x)
        {
                width=x;
        }*/
        int getarea()
        {

                return length*width;
        }
};
int main()
{
        Rectangle s(10,6);
        ///s.setvalue(25);
        ///s.setvalue2(20);

        cout<<"Area = " << s.getarea()<<endl;
}
