#pragma once
#include "Forme.h"

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


class Triangle : public Forme{

private:
    Coord MesPoints[3];

public:
    Triangle();
    Triangle(Coord pt[3]);
    ~Triangle(){};

    vector<Coord> GetCoords();
    void SetCoords(Coord c,int index){MesPoints[index]=c;};
    void PrintCoord();
    float GetRayon(){return -1;};

};
