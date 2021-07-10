#include<iostream>
#include<cstring>

using namespace std;

class student
{
    int id;
    string name;
    float cg;

public :
     void setID(int x)
     {
         id=x;
     }
     int getID()
     {
         return id;
     }
     void nameg(string s)
     {
         name = s;
     }
     string getname()
     {
         return name;
     }
     void setcg(float x)
     {
         cg=x;
     }
     float getcg()
     {
         return cg;
     }
};

int main()
{
   student s[10];

   for(int i=0;i<10;i++)
   {
       s[i].setID(i+1);
   }
   for(int i=0;i<10;i++)
   {
       cout<<" "<<s[i].getID()<<endl;
   }
   //s[0].setID(1);
   //s[0].nameg("Tanin");
   //s[0].setcg(4.00);

   //s[0].setID(2);
   //s[0].nameg("Jakaria");
   //s[0].setcg(3.98);

   /*cout<<"ID     = "<<s1.getID()<<endl;
   cout<<"Name   = "<<s1.getname()<<endl;
   cout<<"CGPA   = "<<s1.getcg()<<endl;

   cout<<"\n"<<"ID     = "<<s2.getID()<<endl;
   cout<<"Name   = "<<s2.getname()<<endl;
   cout<<"CGPA   = "<<s2.getcg()<<endl;*/
}


