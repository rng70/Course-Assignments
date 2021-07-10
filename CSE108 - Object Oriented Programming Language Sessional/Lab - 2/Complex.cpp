#include<iostream>

using namespace std;

class Complex
{
    int real, img;

public:

    Complex()
    {

    }
    Complex(int r,int i)
    {
        real = r;
        img = i;

    }
    int getreal()
    {
        return real;

    }
    int getimg()
    {
        return img;
    }
    void print()
    {
        cout<<"Real = "<<real<<" "<<"Imaginary = " << img<<endl;
    }
    Complex operator+(Complex obj);
     Complex operator+(int obj);
     Complex operator++(int );
     Complex& operator++();
};
Complex Complex::operator+(Complex obj)
{
    Complex temp;
    temp.real = this->real + obj.real;
    temp.img = this->img + obj.img;

    return temp;
}
Complex Complex::operator++(int)
{
    Complex temp;
    temp.real = this->real;
    temp.img = this->img;

    real++;
    img++;

    return temp;
}
Complex& Complex::operator++()
{


    real++;
    img++;

    return *this;
}
int main()
{

    Complex c1(2,3);
    Complex c2(-4,5);
    c1.print();
    c2.print();
    Complex c3(0,0);
    Complex c4(0,0);
    Complex c6;
    ///c3 = c1+c2;
    c3 = c1.operator+(c2);
    cout<<"Summation :"<<endl;
    c3.print();
    c4= c1+5;
    c4.print();

    c6 = c4++;
    c6.print();
    c4.print();
    c6 = ++c4;
    c6.print();
    c4.print();
}
