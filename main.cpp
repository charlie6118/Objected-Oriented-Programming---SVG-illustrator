#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Polygon.h"


using namespace std;

int main( int argc , char **argv )
{
    string num;
    vector<Shape* > shape;

    while(true){
        cout<< "Please choose what you want to do:"<<endl;
        cout<< "1.Output 5*5 RegularPolygon"<<endl;
        cout<< "2.Draw Shapes "<<endl;
        cin>>num;

        if(num == "1"){

            double c[2]={10,10}, d[2]={10,20}, e[2]={10,30}, f[2]={10,40}, g[2]={10,50};
            Vector cent(c,2),cent2(d,2), cent3(e,2), cent4(f,2), cent5(g,2);
            Polygon *regular[25];
            for(int i = 0; i < 5; i++){
                regular[i] = createRegularPolygon(i+3);
                scale(*regular[i], 4);
                cent.component(1)=10;
                cent.component(1)=cent.component(1)+10*i;
                translate(*regular[i], cent);
                shape.push_back(regular[i]);
            }
            for(int i = 5; i < 10; i++){
                regular[i] = createRegularPolygon(i+3);
                scale(*regular[i], 4);
                cent2.component(1)=10;
                cent2.component(1)=cent2.component(1)+10*(i-5);
                translate(*regular[i], cent2);
                shape.push_back(regular[i]);
            }
            for(int i = 10; i < 15; i++){
                regular[i] = createRegularPolygon(i+3);
                scale(*regular[i], 4);
                cent3.component(1)=10;
                cent3.component(1)=cent3.component(1)+10*(i-10);
                translate(*regular[i], cent3);
                shape.push_back(regular[i]);
            }
            for(int i = 15; i < 20; i++){
                regular[i] = createRegularPolygon(i+3);
                scale(*regular[i], 4);
                cent4.component(1)=10;
                cent4.component(1)=cent4.component(1)+10*(i-15);
                translate(*regular[i], cent4);
                shape.push_back(regular[i]);
            }
            for(int i = 20; i < 25; i++){
                regular[i] = createRegularPolygon(i+3);
                scale(*regular[i], 4);
                cent5.component(1)=10;
                cent5.component(1)=cent5.component(1)+10*(i-20);
                translate(*regular[i], cent5);
                shape.push_back(regular[i]);
            }
            std::ofstream myfile;
            myfile.open ("RegularPolygon.svg");
            myfile << toSVG(shape);
            myfile.close();
            cout<<"Create success..."<<endl;
            return 0;
        }

        if(num == "2"){
            while(true){
                cout<< "1.Add Circle"<<endl;
                cout<< "2.Add Line"<<endl;
                cout<< "3.Add RegularPolygon"<<endl;
                cout<< "4.Output file"<<endl;
                cin>>num;
                if(num == "1"){
                    double centerOfCircle[2];
                    double r;
                    cout<< "Please input cx:"<<endl;
                    cin>>centerOfCircle[0];
                    cout<< "Please input cy:"<<endl;
                    cin>>centerOfCircle[1];
                    Vector center(centerOfCircle,2);
                    cout<< "Please input radius:"<<endl;
                    cin>>r;
                    Circle cir(center,r);
                    shape.push_back(&cir);
                }

                if(num == "2"){
                    double a[2],b[2];
                    cout<< "Please input x:"<<endl;
                    cin>>a[0];
                    cout<< "Please input y:"<<endl;
                    cin>>a[1];
                    cout<< "Please input x1:"<<endl;
                    cin>>b[0];
                    cout<< "Please input y1:"<<endl;
                    cin>>b[1];
                    Vector w(a,2), v(b,2);
                    Vector *l[2] = {&w, &v};
                    Polygon line = createConvexPolygon(l, 2);
                    cout<<"po1:"<<line.vertex(1).component(1)<<","<<line.vertex(1).component(2)<<endl;
                    cout<<"po2:"<<line.vertex(2).component(1)<<","<<line.vertex(2).component(2)<<endl;
                    shape.push_back(&line);
                }

                if(num == "3"){
                    double a[2];
                    int n, s;
                    cout<< "Please input x:"<<endl;
                    cin>>a[0];
                    cout<< "Please input y:"<<endl;
                    cin>>a[1];
                    Vector center(a,2);
                    cout<< "Please input n-side:"<<endl;
                    cin>>n;
                    Polygon * hell= createRegularPolygon(n);
                    translate(*hell, center);
                    cout<< "Please input scale:"<<endl;
                    cin>>s;
                    scale(*hell, s);
                    shape.push_back(hell);
                }

                if(num == "4"){
                    std::ofstream myfile;
                    myfile.open ("shape.svg");
                    myfile << toSVG(shape);
                    myfile.close();
                    cout<<"Create success..."<<endl;
                    return 0;
                }
                cout<<endl;
            }
        }
    }
}
