#ifndef PRINTSHAPE_H_INCLUDED
#define PRINTSHAPE_H_INCLUDED
#include "Polygon.h"
#include "Shape.h"


std::string printShape (Shape const &p)
{
    std::stringstream ss;
    ss << "name:" << p.name() << ", area= " << p.area()
       << ", perimeter= " << p.perimeter();
    return ss.str();
}


std::string printShape (Shape const *p)
{
    std::stringstream ss;
    ss << "name:" << p->name() << ", area= " << p->area()
       << ", perimeter= " << p->perimeter();
    return ss.str();
}


#endif // PRINTSHAPE_H_INCLUDED
