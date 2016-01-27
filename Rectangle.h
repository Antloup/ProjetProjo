#pragma once
#include "Forme.h"

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


class Rectangle : public Forme{

private:
    Coord MesPoints[4];

public:
    Rectangle();
    Rectangle(Coord pt[4]);
    ~Rectangle(){};

    vector<Coord> GetCoords();
    void SetCoords(Coord c,int index){MesPoints[index]=c;};
    void PrintCoord();
    float GetRayon(){return -1;};

};
