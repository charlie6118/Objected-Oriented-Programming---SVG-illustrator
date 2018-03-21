#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include "Matrix.h"
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

class Shape
{
public:
    virtual std::string name() const = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string svgCode() const = 0;
};
class Circle: public Shape
{
public:
    Circle(Vector const &center, double radius):c(center),r(radius){}
    std::string name() const {
        return std::string("circle");
    }
    double area() const{
        return M_PI*r*r;
    }
    double perimeter() const{
        return 2.0*M_PI*r;
    }
    std::string svgCode() const{
        std::stringstream ss;
        ss << "<circle cx=\"" << c.component(1) << "\" cy=\"" << c.component(2) <<"\" r=\"" << r ;
        ss <<"\" stroke= \"orangered\" stroke-width= \"0.5\" fill= \"navy\" /> ";
        return ss.str();
    }

private:
    Vector c;
    double r;
};


std::string toSVG (std::vector<Shape* > & s){
        std::stringstream ss;
        ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500\" height=\"1500\" viewBox=\"0 0 100 100\">";
        for(int i = 0; i < s.size(); i++){
            ss << s[i]->svgCode();
        }
        ss << "</svg>";
        return ss.str();
}
bool areaGreater (Shape * a, Shape *b) {return a->area() > b->area(); }

#endif // SHAPE_H_INCLUDED
