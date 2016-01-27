#pragma once

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "Coord.h";
using namespace std;

class Forme{

protected:
    string name;

public:
    Forme(){};
    ~Forme(){};
    virtual vector<Coord> GetCoords()=0;
    virtual void SetCoords(Coord c,int index)=0;
    virtual void PrintCoord()=0;
    virtual float GetRayon()=0;
    string Get_name(){return name;};

};
