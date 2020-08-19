///   This assignment was submitted by Al Arafat Tanin
///        File name was set as "FileofGame.txt"


#include <iostream>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3

string to_string(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}

class Position
{

    int x, y;

public:

    Position()
    {
    }
    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    /// Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(this->x <= (GRIDSIZE-2))
            x++;
    }

    void moveLeft()
    {
        if(this->x > (GRIDSIZE-4))
            x--;
    }

    void moveUp()
    {
        if(this->y <= (GRIDSIZE-2))
            y++;
    }

    void moveDown()
    {
        if(this->y > (GRIDSIZE-4))
            y--;
    }

    bool isAdjacent(Position p)
    {
        ///implement the function
        if( this->x + 1 == p.getX() && this->y == p.getY() )
            return true ;
        else if ( this->x - 1 == p.getX() && this->y == p.getY() )
            return true ;
        else if ( this->x == p.getX()&& this->y - 1 == p.getY() )
            return true ;
        else if( this->x - 1 == p.getX() && this->y + 1 == p.getY() )
            return true ;

        else
            return false ;
    }

    bool isSamePoint(Position p)
    {
        ///implement the function
        return (this->x == p.getX()) && (this->y == p.getY());
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class Wumpus
{

    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        /// My Code...
        p = Position(rand()%GRIDSIZE, rand()%GRIDSIZE);
        killed = false ;
    }

    bool isAlive()
    {
        return killed;
    }
    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:


    Player()
    {
        ///My Code...
        direction = UP;
        p = Position(0,0);
        killed = false;
        total_shots = MAX_SHOTS;
    }

    void turnLeft()
    {
        ///...
        if     (direction == UP   )
            direction = LEFT ;
        else if(direction == DOWN )
            direction = RIGHT;
        else if(direction == RIGHT)
            direction = UP   ;
        else if(direction == LEFT )
            direction = DOWN ;
    }

    void turnRight()
    {
        ///...
        if      (direction == UP   )
            direction = RIGHT;
        else if (direction == DOWN )
            direction = LEFT ;
        else if (direction == RIGHT)
            direction = DOWN ;
        else if (direction == LEFT )
            direction = UP   ;
    }

    void moveForward()
    {
        ///...
        if      (direction == UP   )
            p.moveUp()   ;
        else if (direction == DOWN )
            p.moveDown() ;
        else if (direction == RIGHT)
            p.moveRight();
        else if (direction == LEFT )
            p.moveLeft() ;
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }

    Position current_position()
    {
        return p ;
    }
    void kill()
    {
        killed = true;
    }

    string getPositionInfo()
    {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo()
    {
        string s;
        if (direction == UP)
            s = "up";
        if (direction == DOWN)
            s = "down";
        if (direction == LEFT)
            s = "left";
        if (direction == RIGHT)
            s = "right";
        return "Player is moving at direction: " + s;
    }
    bool remain_shoot()
    {
        if(total_shots != 0)
        {
            total_shots--;
            return true;
        }
        else
            return false;
    }
    int current_direction()
    {
        return direction ;
    }

};


class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Position gold_position;
    Position position_of_pit;
    bool ended;

public:

    WumpusWorld()
    {
        ///...
        gold_position = Position(rand()%GRIDSIZE, rand()%GRIDSIZE);
        position_of_pit = Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        wumpus = Wumpus(rand()%GRIDSIZE,rand()%GRIDSIZE);
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        ///...
        gold_position = Position(rand()%GRIDSIZE, rand()%GRIDSIZE);
        position_of_pit = Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        wumpus = Wumpus(wumpus_x,wumpus_y);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        ///...
        gold_position = Position(gold_x,gold_y);
        position_of_pit = Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        wumpus = Wumpus(wumpus_x,wumpus_y);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        ///...
        wumpus = Wumpus(wumpus_x, wumpus_y);
        position_of_pit = Position(pit_x,pit_y);
        gold_position = Position(gold_x, gold_y);
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        ///...
        if(!(player.remain_shoot()))
        {
            cout<<"You Cann't shoot"<<endl;
        }
        else if(player.current_direction() == UP)
        {
            ///player.total_shots--;
            if(wumpus.getPosition().getX() == player.current_position().getX())
            {
                if(wumpus.getPosition().getY()+1 == player.current_position().getY())
                    wumpus.kill();
                cout << "Yes,You have done it.You have killed Wumpus" << endl;
            }
            else
                cout << "Oh no .. ..  :( :( :( .. You have missed it " << endl;
        }
        else if(player.current_direction() == DOWN)
        {
            ///player.total_shots--;
            if(wumpus.getPosition().getX() == player.current_position().getX())
            {
                if(wumpus.getPosition().getY()-1 == player.current_position().getY())
                    wumpus.kill();
                cout << "Yes,You have done it.You have killed Wumpus" << endl;
            }
            else
                cout << "Oh no .. ..  :( :( :( .. You have missed it " << endl;
        }
        else if(player.current_direction() == RIGHT)
        {
            ///player.total_shots--;
            if(wumpus.getPosition().getY() == player.current_position().getY())
            {
                if(wumpus.getPosition().getX()+1 == player.current_position().getX())
                    wumpus.kill();
                cout << "Yes,You have done it.You have killed Wumpus" << endl;
            }
            else
                cout << "Oh no .. ..  :( :( :( .. You have missed it " << endl;
        }
        else if(player.current_direction() == LEFT)
        {
            ///player.total_shots--;
            if(wumpus.getPosition().getY() == player.current_position().getY())
            {
                if(wumpus.getPosition().getX()-1 == player.current_position().getX())
                    wumpus.kill();
                cout << "Yes,You have done it.You have killed Wumpus" << endl;
            }
            else
                cout << "Oh no .. ..  :( :( :( .. You have missed it " << endl;
        }
    }

    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (player.isAdjacent(wumpus.getPosition()))
        {
            cout << "stench!" << endl;
        }
        if (player.isAdjacent(position_of_pit))
        {
            cout << "breeze!" << endl;
        }

        if (player.isSamePoint(wumpus.getPosition()) && !(wumpus.isAlive()))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
        if (player.isSamePoint(position_of_pit))
        {
            cout << "Oh no :( :( :( you fell in the pit!" << endl;
            cout << "Game over!" << endl;
            ended = true;
        }
    }

    bool isOver()
    {
        return ended;
    }

};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    std::srand(std::time(NULL));

    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;

    /// take the six integers input from file

    ifstream File_of_wumpus;
    File_of_wumpus.open("FileofGame.txt");
    File_of_wumpus >> wumpus_x >> wumpus_y >> gold_x >> gold_y >> pit_x>> pit_y;
    File_of_wumpus.close();

    ///cout<< wumpus_x <<" "<< wumpus_y <<" "<< gold_x <<" "<< gold_y <<" "<< pit_x<<" "<< pit_y;

    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}
