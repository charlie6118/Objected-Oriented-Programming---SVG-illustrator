#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include "Shape.h"
#include "Matrix.h"
#include <algorithm>
#include <iostream>
class Polygon: public Shape
 {
public:
    Polygon(Vector * a[], int numberOfVertices)
    :vertices(a, numberOfVertices) // constructor initialization
    {}

    Polygon(Polygon const &p)
     :vertices(p.vertices){}

    Vector & vertex(int i) const {
        return vertices[i];
    }
    int numberOfVertices ()const{
        return vertices.nRows();
    }
    double perimeter() const{
        double p=0;
        for(int i=1;i<numberOfVertices();i++){
            p+=(vertices[i+1]-vertices[i]).length();
        }
        p+=(vertices[numberOfVertices()]-vertices[1]).length();
        return p;
    }
    double area() const{
        double area=0;
        for(int i=2;i<numberOfVertices();i++){
           area+=VectorArea(vertices[1],vertices[i],vertices[i+1]);
        }
        return area;
    }
    std::string name() const{
        return std::string("polygon");
    }

    std::string svgCode() const{
        std::stringstream ss;
        std::string temp;
        if(numberOfVertices() == 2){
            ss << "<line x1=\"" << vertices[1][1] << "\" y1=\"" << vertices[1][2] <<"\" x2=\"" << vertices[2][1] <<"\" y2=\"" << vertices[2][2] ;
            ss << "\" style=\"stroke:rgb(255,0,0);stroke-width:0.5\" />";
            return ss.str();
        }
        else{
            ss << "<polygon points= \"";
            for(int i = 1; i <= numberOfVertices(); i++){
                for(int j = 1; j<= 2; j++){
                    ss << vertices[i][j];
                    if(j==1)
                        ss<<",";
                }
                ss << " ";
            }
            ss << "\" style = \"fill:navy ; stroke:orangered ; stroke-width: 0.5\" />";
            return ss.str();
        }

    }
private:
    Matrix vertices;
};
class IncreasingByAngleToRefVector{
public:
    IncreasingByAngleToRefVector(Vector const &cV,Vector const &refV)
    :c(cV),ref(refV){}
    bool operator()(Vector * u,Vector * v){
        return angle(ref, *u-c)<angle(ref, *v-c);
    }
    Vector c;
    Vector ref;
};

Polygon createConvexPolygon(Vector* vecs[], int n){
    Vector c = centroid(vecs, n);
    Vector ref = *vecs[0] - c;
    //std::sort(vecs, vecs + n, IncreasingByAngleToRefVector(c, ref));
    std::sort(vecs, vecs + n, [&c,&ref] (Vector *u,Vector *v )->bool{return angle(ref, *u-c)<angle(ref, *v-c);});
    return Polygon(vecs, n);
}



Polygon * createRegularPolygon(int n){
    double **a = new double*[n];
    for(int i = 0; i < n; i++){
        a[i] = new double[2];
    }

    a[0][0] = 1;
    a[0][1] = 0;

    double angle = 360.0 / n;
    for(int i = 1; i < n; i++){
        a[i][0] = cos(angle*M_PI/180) * a[i-1][0] - sin(angle*M_PI/180) * a[i-1][1];
        a[i][1] = sin(angle*M_PI/180) * a[i-1][0] + cos(angle*M_PI/180) * a[i-1][1];

    }

    Vector **b = new Vector*[n];
    for(int i = 0; i < n; i++){
        b[i] = new Vector(a[i], 2);
    }
    return new Polygon (b,n);
}

void scale(Polygon & m, double a){
    Vector **b = new Vector*[m.numberOfVertices()];

    for(int i = 0; i < m.numberOfVertices(); i++){
        b[i] = new Vector(m.vertex(i+1));
    }

    Vector c = centroid(b, m.numberOfVertices());

    for(int i=1; i <= m.numberOfVertices(); i++){
        m.vertex(i) = m.vertex(i)-c;
        multiply(a,m.vertex(i));
        m.vertex(i) = m.vertex(i)+c;
    }
}

translate(Polygon &m, Vector const &t){
    for(int i=1; i <= m.numberOfVertices(); i++){
        m.vertex(i) = m.vertex(i) + t;
    }
}


#endif // POLYGON_H_INCLUDED
