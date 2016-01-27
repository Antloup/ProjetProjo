#include "Rectangle.h"
#include "Forme.h"
#include <iostream>

using namespace cv;
using namespace std;

Rectangle::Rectangle() : Forme()
{
    name="Rectangle";
    for(int i=0;i<4;i++){
        MesPoints[i].x=-1;
        MesPoints[i].y=-1;
    }

}

Rectangle::Rectangle(Coord pt[4]) : Forme()
{
    name="Rectangle";
    for(int i=0;i<4;i++){
        MesPoints[i]=pt[i];
    }

}


vector<Coord> Rectangle::GetCoords(){
    vector<Coord> Coords = vector<Coord>();
    for(int i=0;i<4;i++){
            Coords.push_back(MesPoints[i]);
    }
    return Coords;
}


void Rectangle::PrintCoord(){

    for(int i=0;i<4;i++){
        cout<<"Points : "<<i<<endl;
        cout<<"x : "<<MesPoints[i].x<<endl;
        cout<<"y : "<<MesPoints[i].y<<endl;
        cout<<endl;

    }

}

