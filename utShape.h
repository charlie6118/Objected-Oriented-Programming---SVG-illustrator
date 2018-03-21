#ifndef UTSHAPE_H_INCLUDED
#define UTSHAPE_H_INCLUDED

#include <fstream>
#include "Polygon.h"
#include "Shape.h"
#include "printShape.h"


TEST(Polygon, createRegularPolygon){
    int n = 4;
    Polygon * hell= createRegularPolygon(n);

    EXPECT_NEAR( 1, hell->vertex(1)[1], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(1)[2], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(2)[1], 0.00001);
    EXPECT_NEAR( 1, hell->vertex(2)[2], 0.00001);
    EXPECT_NEAR( -1, hell->vertex(3)[1], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(3)[2], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(4)[1], 0.00001);
    EXPECT_NEAR( -1, hell->vertex(4)[2], 0.00001);

}

TEST(Polygon, scale){
    int n = 4;
    Polygon * hell= createRegularPolygon(n);
    scale(*hell, 2);

    EXPECT_NEAR( 2, hell->vertex(1)[1], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(1)[2], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(2)[1], 0.00001);
    EXPECT_NEAR( 2, hell->vertex(2)[2], 0.00001);
    EXPECT_NEAR( -2, hell->vertex(3)[1], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(3)[2], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(4)[1], 0.00001);
    EXPECT_NEAR( -2, hell->vertex(4)[2], 0.00001);

}

TEST(Polygon, translate){
    int n = 4;
    Polygon * hell= createRegularPolygon(n);
    double t[2]={1,1};
    Vector tt(t,2);
    translate(*hell, tt);

    EXPECT_NEAR( 2, hell->vertex(1)[1], 0.00001);
    EXPECT_NEAR( 1, hell->vertex(1)[2], 0.00001);
    EXPECT_NEAR( 1, hell->vertex(2)[1], 0.00001);
    EXPECT_NEAR( 2, hell->vertex(2)[2], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(3)[1], 0.00001);
    EXPECT_NEAR( 1, hell->vertex(3)[2], 0.00001);
    EXPECT_NEAR( 1, hell->vertex(4)[1], 0.00001);
    EXPECT_NEAR( 0, hell->vertex(4)[2], 0.00001);

}


TEST(Shape, toSVGLine){
    double a[2] = {10, 10}, b[2] = {200, 200};
    Vector u(a, 2), v(b, 2);
    Vector *p[4] = {&u, &v};
    Polygon line = createConvexPolygon(p, 2);

    std::vector<Shape* > s;
    s.push_back (&line);
    std::ofstream myfile;
    myfile.open ("example.svg");
    myfile << toSVG(s);
    myfile.close();
    ASSERT_EQ("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500\" height=\"1500\" viewBox=\"0 0 100 100\"><line x1=\"10\" y1=\"10\" x2=\"200\" y2=\"200\" style=\"stroke:rgb(255,0,0);stroke-width:0.5\" /></svg>", toSVG(s));
}

TEST(Shape, toSVGCircle){
    double a0[2]={50,50};
    Vector c0(a0,2);
    Circle cir(c0, 50);


    std::vector<Shape* > s;
    s.push_back (&cir);

    ASSERT_EQ("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500\" height=\"1500\" viewBox=\"0 0 100 100\"><circle cx=\"50\" cy=\"50\" r=\"50\" stroke= \"orangered\" stroke-width= \"0.5\" fill= \"navy\" /> </svg>", toSVG(s));
}


TEST(Shape, toSVGPolygon){
    double a[2] = {1, 1}, b[2] = {0, 1}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = {&u, &v, &w, &x};
    Polygon square = createConvexPolygon(p, 4);

    std::vector<Shape* > s;
    s.push_back (&square);

    ASSERT_EQ("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500\" height=\"1500\" viewBox=\"0 0 100 100\"><polygon points= \"1,1 0,1 0,0 1,0 \" style = \"fill:navy ; stroke:orangered ; stroke-width: 0.5\" /></svg>", toSVG(s));
}

TEST(Shape, toSVGGroupOfShape){
    double a[2] = {1, 1}, b[2] = {0, 1}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = {&u, &v, &w, &x};
    Polygon square = createConvexPolygon(p, 4);

    double a0[2]={10,10};
    Vector c0(a0,2);
    Circle cir(c0, 10);

    std::vector<Shape* > s;
    s.push_back (&cir);
    s.push_back (&square);

    ASSERT_EQ("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1500\" height=\"1500\" viewBox=\"0 0 100 100\"><circle cx=\"10\" cy=\"10\" r=\"10\" stroke= \"orangered\" stroke-width= \"0.5\" fill= \"navy\" /> <polygon points= \"1,1 0,1 0,0 1,0 \" style = \"fill:navy ; stroke:orangered ; stroke-width: 0.5\" /></svg>", toSVG(s));
}
#endif // UTSHAPE_H_INCLUDED
