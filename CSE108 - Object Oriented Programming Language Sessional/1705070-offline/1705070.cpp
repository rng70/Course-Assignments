#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
class Unit
{
protected :
    int range, health, Damage,cost, step, return_coin,distance,position;
    string name,shoot_type,run_type;
public:
    Unit(string a, string b,string c)
    {
        run_type=c;
        name = a;
        shoot_type = b;
    }
    virtual int Health()
    {
        return health;
    }
    virtual int Range()
    {
        return range;
    }
    virtual int Damafe()
    {
        return Damage;
    }
    virtual int pos()
    {
        return position;
    }
    virtual int coin()
    {
        return return_coin;
    }
    virtual int Cost()
    {
        return cost;
    }
    void game_state()
    {
        if(health>0)
        {
            position += step;
            cout<<name<<".Health: "<<health<<" ."<<run_type<<" .Positioned at "<<position<<". ";
            if(range + position >= 100)
            {
                cout<<name<<" is shooting "<<shoot_type<<".";
            }
            health -= 40;
        }
        else
        {
            cout<<name<<".Health: "<<health<<" .Unit Died!!"<<endl;
        }
    }
};
class Tower:public Unit
{
public :
    Tower(int ):Unit("0","0","0")
    {
        range = 200;
        health = 300;
        Damage = 40;
    }
};
class Bowman: public Unit
{
public:
    Bowman(int ):Unit("Bowman","Basic Arrow","Stationary")
    {
        range = 110;
        health = 60;
        Damage = 10 ;
        cost = 100 ;
        return_coin = 40 ;
    }
};
class AdvancedBowman: public Unit
{
public:
    AdvancedBowman(int ):Unit("AdvancedBowman","Canon","Stationary")
    {
        range = 130;
        health = 85;
        Damage = 15 ;
        cost = 200 ;
        return_coin = 60 ;
    }
};
class Archer: public Unit
{
public:
    Archer(int ):Unit("Archer","Advanced Arrow","Running")
    {
        range = 50;
        health = 100;
        Damage = 25 ;
        position = 0;
        cost = 150 ;
        step = 25;
    }
};
class AdvancedArcher: public Unit
{
public:
    AdvancedArcher(int ):Unit("AdvancedArcher","Improved Arrow","Riding Horse")
    {
        range = 50;
        health = 120;
        Damage = 50 ;
        position = 0;
        cost = 600 ;
        step = 30;
    }
};
int main()
{
    Unit *w;
    Tower *e = new Tower(0);

    int choice,balance=1600,round = 0;
    static int till_end;
    till_end = e->Health();
    cout<<"Coin Remaining: "<<balance<<endl<<endl;
    while(1)
    {
        cout<<"Choose your option: "<<endl;
        cout<<"1. Archer (Cost 150)\n2. Advanced Archer (Cost 600)"<<endl;
        cout<<"3. Bowman (Cost 100)\n4. Advanced Bowman (Cost 200)"<<endl;
        cin>>choice;
        if(balance<100 && till_end > 0)
        {
            cout<<"No more coins\nYOU LOST :("<<endl;
            break;
        }
        else
        {
            switch(choice)
            {
            case 1:
                w =  new Archer(0);
                break;
            case 2:
                w = new AdvancedArcher(0);
                break;
            case 3:
                w =  new Bowman(0);
                break;
            default :
                w = new AdvancedBowman(0);
                break;
            }
            if(w->Cost()>balance)
            {
                cout<<"No more coins\nYOU LOST :("<<endl;
                break;
            }
            else
            {
                while(w->Health()>0)
                {
                    cout<<"Round : "<<++round<<endl;
                    w->game_state();
                    if( w->pos() + w->Range() >= 100)
                    {
                        till_end -= w->Damafe();
                    }
                    if(till_end<=0)
                    {
                        cout<<"EnemyTower's Health :"<<till_end<<". Battle WON!!!"<<endl;
                        return 0;
                    }
                    else if(till_end>0)
                    {
                        cout<<"\nEnemyTower's Health : "<<till_end<<". EnemyTower is shooting Fire Arrows."<<endl;
                    }
                }
                cout<<"Round : "<<++round<<endl;
                w->game_state();
                balance = balance - w->Cost() + w->coin();
                cout<<"\nCoin Remaining: "<<balance<<endl<<endl;
            }
        }
    }
}

