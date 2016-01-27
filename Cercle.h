#pragma once
#include "Forme.h"

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


class Cercle : public Forme{

private:
    Coord MonPoint;
    float Rayon;

public:
    Cercle();
    Cercle(Coord pt,int r);
    ~Cercle(){};

    vector<Coord> GetCoords();
    void SetCoords(Coord c,int index){MonPoint=c;};
    void PrintCoord();
    float GetRayon(){return Rayon;};

};
