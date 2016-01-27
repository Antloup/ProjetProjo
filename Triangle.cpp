#include "Triangle.h"
#include "Forme.h"
#include <iostream>

using namespace cv;
using namespace std;

Triangle::Triangle() : Forme()
{
    name="Triangle";
    for(int i=0;i<3;i++){
        MesPoints[i].x=-1;
        MesPoints[i].y=-1;
    }

}

Triangle::Triangle(Coord pt[3]) : Forme()
{
    name="Triangle";
    for(int i=0;i<3;i++){
        MesPoints[i]=pt[i];
    }

}


vector<Coord> Triangle::GetCoords(){
    vector<Coord> Coords = vector<Coord>();
    for(int i=0;i<3;i++){
            Coords.push_back(MesPoints[i]);
    }
    return Coords;
}


void Triangle::PrintCoord(){

    for(int i=0;i<3;i++){
        cout<<"Points : "<<i<<endl;
        cout<<"x : "<<MesPoints[i].x<<endl;
        cout<<"y : "<<MesPoints[i].y<<endl;
        cout<<endl;

    }

}

