
#include<iostream>
#include<cmath>
using namespace std;


class Point2D
{
	int x,y;
public:
	Point2D(){ x = 0; y = 0; } //default constructor initializes to (0,0)
	Point2D(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void print();
	~Point2D(){ x = 0; y = 0; } //destructor that sets all values to 0
	static double distance (Point2D p1,Point2D p2);
};
double Point2D::distance(Point2D p1,Point2D p2)
{
    return sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX()) + (p1.getY()-p2.getY())*(p1.getY()-p2.getY()));
}
Point2D::Point2D(int argx,int argy)
{
	x = argx;
	y = argy;
}

void Point2D::setX(int argx)
{
	x=argx;
}

void Point2D::setY(int argy)
{
	y=argy;///Complete this function
}

int Point2D::getX()
{
	return x;//Complete this function
}

int Point2D::getY()
{
	return y;//Complete this function
}

void Point2D::print()
{
	cout << "(" << x << "," << y << ")";
}

class Circle
{
	Point2D center;
	double radius;
public:
	//write a default constructor that initializes all values to 0
	Circle(Point2D c, double r);
	//write getter and setter methods for this class
	double area(); //returns area of the circle
	void print(); //prints the rectangle in the stdout
	int intersect(Circle rhs); //determine if this circle intersects with rhs
	int contains(Point2D p); //determine if this circle contains point p
	double perimeter(); //returns perimeter of the circle
	//write a destructor that sets all values to 0
};

Circle::Circle(Point2D c, double r)
{
	center = c;
	radius = r;
	//complete this function
}

double Circle::area()
{
	return 3.1415*radius*radius;//complete this function
}

int Circle::intersect(Circle rhs)
{
    double dist = Point2D::distance(this center , rhs.getCenter());
    double sumOfRad = this->radius + rhs.getRadius ;
    double diffOfRad = abs(this->radius - rhs.getRadius);
    if(sumOfRad << diffOfRad)
        cout<<"Intersect"<<endl;
    return 1;

    else
        cout<<"Not intersect"<<endl;
    return 0;
    cout<<"Inside Intersect : Radius : "<<this -> radius<<endl;
	//complete this function
}

void Circle::print()
{
	cout << "Center: ";
	center.print();
	cout << "Radius: " << radius;
}

class Rectangle
{
	//define two variables that specifies the rectangle in a 2d space
	//the variables should represent: top-right point, bottom-left point
	//consider the rectangle is axes parallel
public:


	///write a default constructor that initializes all values to 0
	//write a constructor that accepts values of all member variables and set the members
	//variables accordingly
	//write getter and setter methods for this class
	double area(); //returns area of the rectangle
	int intersect(Rectangle rhs); //determine if this rectangle intersects with rhs
	int contains(Rectangle rhs);
	int contains(Point2D p1); //determine if this rectangle contains rhs
	int inside(Circle c); //determine if this rectangle is completely inside the circle c
	double perimeter(); //returns perimeter of the circle
	//write a destructor that sets all values to 0
};


int main(void)
{
    Point2D p1(0,0);
    Point2D p2(5,0);

    Circle c1(p1,3.0);
    Circle c2(p2,4.0);

    c1.print();
    c1.intersect(c2);
    cout<<"Distance :"<<Point2D::distance(p1,p2)<<endl;
	//Demonstrate your circle class which will have a point and a radius
	//Demonstrate your area funciton showing that it successfully prints area of a circle
	//Demonstrate intersect(Circle) function by creating appropriate circles and showing that they intersect
	//Demonstrate contains(Point) function by creating appropriate circles and showing that one circle
	//contains the point


	//Demonstrate your Rectangle class
	//Demonstrate your area funciton showing that it successfully prints area of a rectangle
	//Demonstrate intersect(Rectangle) function by creating appropriate circles and showing that
	//they intersect
	//Demonstrate contains(Rectangle) function by creating appropriate circles and showing that
	//one rectangle contains another rectangle
	//Demonstrate inside(Circle) function by creating appropriate rectangle and circle and showing that
	//a rectange is completely inside a circle


	return 0;
}
