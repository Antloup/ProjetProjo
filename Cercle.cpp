#include "Cercle.h"
#include "Forme.h"
#include <iostream>

using namespace cv;
using namespace std;

Cercle::Cercle() : Forme()
{
    name="Cercle";
    MonPoint.x=-1;
    MonPoint.y=-1;
    Rayon=-1;

}

Cercle::Cercle(Coord pt,int r) : Forme()
{
    name="Cercle";
    MonPoint=pt;
    Rayon=r;

}


vector<Coord> Cercle::GetCoords(){
    vector<Coord> Coords = vector<Coord>();
    Coords.push_back(MonPoint);
    return Coords;
}


void Cercle::PrintCoord(){

    cout<<"Centre : "<<endl;
    cout<<"X : "<<MonPoint.x<<endl;
    cout<<"Y : "<<MonPoint.y<<endl;
    cout<<"Rayon : "<<Rayon<<endl;

}
