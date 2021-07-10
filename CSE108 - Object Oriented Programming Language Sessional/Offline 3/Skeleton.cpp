#include<bits/stdc++.h>
#include<cstdlib>

using namespace std;

class Unit
{
protected :
    int range, health, Damage,cost, step, return_coin,distance,position;
public:
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
    virtual void game_state(){}

};

class Tower:public Unit
{
protected :
    int round ;
public :
    Tower(int)
    {
        range = 200;
        health = 300;
        Damage = 40;
    }
};

class Bowman: public Unit
{
public:
    Bowman(int )
    {
        range = 110;
        health = 60;
        Damage = 10 ;
        cost = 100 ;
        return_coin = 40 ;
    }
    void game_state()
    {
        if(health>0)
        {
            cout<<"Bowman.Health: "<<health<<" .StationaryPositioned at 0.Bowman is shooting Basic Arrows."<<endl;
            health -= 40;
        }
        else
        {
            cout<<"Bowman.Health: "<<health<<" .Unit Died!!"<<endl;
            cout<<"Bowman gave "<<return_coin<<" coins while dying."<<endl;
        }
    }
};

class AdvancedBowman: public Unit
{
public:
    AdvancedBowman(int )
    {
        range = 130;
        health = 85;
        Damage = 15 ;
        cost = 200 ;
        return_coin = 60 ;
    }
    void game_state()
    {
        if(health>0)
        {
            cout<<"AdvancedBowman.Health: "<<health<<" .StationaryPositioned at 0.AdvancedBowman is shooting Canon."<<endl;
            health -= 40;
        }
        else
        {
            cout<<"AdvancedBowman.Health: "<<health<<" .Unit Died!!"<<endl;
            cout<<"AdvancedBowman gave "<<return_coin<<" coins while dying."<<endl;
        }
    }
};
class Archer: public Unit
{
public:
    Archer(int )
    {
        range = 50;
        health = 100;
        Damage = 25 ;
        position = 25;
        cost = 150 ;
        step = 25;
    }
    void game_state()
    {
        if(health>0)
        {
            cout<<"Archer.Health: "<<health<<" .Running."<<"Positioned at "<<position<<" Archer is shooting Advanced Arrows."<<endl;
            health -= 40;
            position += step;
        }
        else
        {
            cout<<"Archer.Health :"<<health<<".Unit Died!!"<<endl;
        }
    }
};
class AdvancedArcher: public Unit
{
public:
    AdvancedArcher(int )
    {
        range = 50;
        health = 120;
        Damage = 50 ;
        position = 25;
        cost = 600 ;
        step = 30;
    }
    void game_state()
    {
        if(health>0)
        {
            cout<<"AdvancedArcher.Health: "<<health<<" .Running."<<"Positioned at "<<position<<" AdvancedArcher is shooting Advanced Arrows."<<endl;
            health -= 40;
            position += step;
        }
        else
        {
            cout<<"AdvancedArcher.Health: "<<health<<" .Unit Died!!"<<endl;
        }
    }
};

int main()
{
    Unit *w;
    Tower *e = new Tower(0);

    int choice,balance=1600,round = 0;
    static int till_end;
    till_end = e->Health();
    cout<<"Coin Remaining: "<<balance<<endl;
    while(1)
    {
        if(balance<100)
        {
            cout<<"No more coins"<<endl;
            cout<<"YOU LOST :("<<endl;
            break;
        }

        cout<<"Choose your option: "<<endl;
        cout<<"1. Archer (Cost 150)"<<endl;
        cout<<"2. Advanced Archer (Cost 600)"<<endl;
        cout<<"3. Bowman (Cost 100)"<<endl;
        cout<<"4. Advanced Bowman (Cost 200)"<<endl;
        cin>>choice;

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
        while(w->Health()>0)
        {
            cout<<"Round : "<<++round<<endl;
            w->game_state();
            if(100-w->pos()<=w->Range())
            {
               till_end -= w->Damafe();
            }
            if(till_end<=0) {
                    cout<<"EnemyTower's Health :"<<till_end<<". Battle WON!!!"<<endl;
                    return 0;
            }
            else if(till_end>0)
            {
                cout<<"EnemyTower's Health : "<<till_end<<". EnemyTower is shooting Fire Arrows."<<endl;
            }
        }
        cout<<"Round : "<<++round<<endl;
        --round;
        w->game_state();
        balance = balance - w->Cost() + w->coin();
        cout<<"Coin Remaining: "<<balance<<endl;
    }
}
