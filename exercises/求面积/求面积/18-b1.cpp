/* 2154146 吴金轩 计科 */
#include <iostream>
#include <cmath>
#include <cmath>
#define Pi 3.14159
using namespace std;

class Shape {
protected:
    //根据需要加入相应的成员，也可以为空
public:
    Shape();
    virtual void ShapeName() = 0; //此句不准动
    virtual double area();
    //根据需要加入相应的成员，也可以为空
};

Shape::Shape()
{
}

double Shape::area()
{
    return 0;
}

class Circle :public Shape {
protected:
    double radius;
public:
    Circle(double r);
    virtual void ShapeName();
    virtual double area();
};

Circle::Circle(double r):Shape()
{
    if (r > 0)
        radius = r;
    else
        radius = 0;
}

void Circle::ShapeName()
{
    cout << "Circle" << endl;
}


double Circle::area()
{
    return Pi * radius * radius;
}


class Square :public Shape {
protected:
    double length;
public:
    Square(double a);
    virtual void ShapeName();
    virtual double area();
};

Square::Square(double a) :Shape()
{
    if (a > 0)
        length = a;
    else
        length = 0;
}

void Square::ShapeName()
{
    cout << "Square" << endl;
}

double Square::area()
{
    return length * length;
}


class Rectangle :public Shape {
protected:
    double a;
    double b;
public:
    Rectangle(double a_length, double b_length);
    virtual void ShapeName();
    virtual double area();
};

Rectangle::Rectangle(double a_length, double b_length) :Shape()
{
    if (a_length > 0 && b_length > 0)
    {
        a = a_length;
        b = b_length;
    }
    else
    {
        a = 0;
        b = 0;
    }
}

void Rectangle::ShapeName()
{
    cout << "Rectangle" << endl;
}

double Rectangle::area()
{
    return a * b;
}


class Triangle :public Shape {
protected:
    double s1;
    double s2;
    double s3;
public:
    Triangle(double s1_length, double s2_length, double s3_length);
    virtual void ShapeName();
    virtual double area();
};

Triangle::Triangle(double s1_length, double s2_length, double s3_length) :Shape()
{
    if (s1_length > 0 && s2_length > 0 && s3_length > 0)
    {
        if (s1_length + s2_length > s3_length && s1_length + s3_length > s2_length && s2_length + s3_length > s1_length)
        {
            s1 = s1_length;
            s2 = s2_length;
            s3 = s3_length;
        }
        else
        {
            s1 = 0;
            s2 = 0;
            s3 = 0;
        }
    }
    else
    {
        s1 = 0;
        s2 = 0;
        s3 = 0;
    }
}

void Triangle::ShapeName()
{
    cout << "Triangle" << endl;
}

double Triangle::area()
{
    double p = (s1 + s2 + s3) / 2;

    return sqrt(p * (p - s1) * (p - s2) * (p - s3));
}


class Trapezoid :public Shape {
protected:
    double up;
    double down;
    double height;
public:
    Trapezoid(double u, double d, double h);
    virtual void ShapeName();
    virtual double area();
};

Trapezoid::Trapezoid(double u, double d, double h) :Shape()
{
    if (u > 0 && d > 0 && h > 0)
    {
        up = u;
        down = d;
        height = h;
    }
    else
    {
        up = 0;
        down = 0;
        height = 0;
    }
}

void Trapezoid::ShapeName()
{
    cout << "Trapezoid" << endl;
}

double Trapezoid::area()
{
    return (up + down) * height / 2;
}

//此处给出五个类的定义及实现(成员函数采用体外实现形式)

/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //半径5.2（如果<=0，面积为0）
        Square    s1(5.2);           //边长5.2（如果<=0，面积为0）
        Rectangle r1(5.2, 3.7);      //长、宽（如果任一<=0，面积为0）
        Trapezoid t1(2.3, 4.4, 3.8); //上底、下底、高（如果任一<=0，面积为0）
        Triangle  t2(3, 4, 5);       //三边长度（如果任一<=0或不构成三角形，面积为0）
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //分别打印不同形状图形的名称（格式参考demo）
            cout << s[i]->area() << endl; //分别打印不同形状图形的面积（格式参考demo）
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //半径5.2（如果<=0，面积为0）
        Square    s1(-1);           //边长5.2（如果<=0，面积为0）
        Rectangle r1(5.2, -1);      //长、宽（如果任一<=0，面积为0）
        Trapezoid t1(2.3, -1, 3.8); //上底、下底、高（如果任一<=0，面积为0）
        Triangle  t2(3, 4, -1);       //三边长度（如果任一<=0或不构成三角形，面积为0）
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //分别打印不同形状图形的名称（格式参考demo）
            cout << s[i]->area() << endl; //分别打印不同形状图形的面积（格式参考demo）
            cout << endl;
        }
    }

    return 0;
}
