#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    cout<<"Please enter Chapter No, Section No, Student ID(Last 3 Digits), Max number of problems: "<<endl;
    int chap, sec, stdid, max;
    cin>>chap>>sec>>stdid>>max;
    cout<<"You have to the following exercise : ";
    for(int i=1;i<=max; i++)
    {
        if(i%max == (11*chap + 9*sec+ stdid)%max) cout<<i<<endl;
    }
    int checker;
    if(stdid >= 61) checker = abs((11*chap + 9*sec + stdid ) % 60 + (1 - 60));
    else checker = abs((11*chap + 9*sec + stdid ) % 60 + (1 + 60));
    cout<<"Your Assignment will be verified by: "<<checker<<endl;
    cout<<"You'll be verifying the answer of:  ";
    for(int i=1;i<=122;i++)
    {
        if(i >= 61) checker = abs((11*chap + 9*sec + i ) % 60 + (1 - 60));
        else checker = abs((11*chap + 9*sec + i ) % 60 + (1 + 60));
        if(checker == stdid) cout<<i<<endl;
    }
    return 0;
}
