#pragma once

#include "Forme.h"

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

class LesFormes{

private:
    //Attributs :
    int phase;
    vector<Forme*> MesFormes;
    vector<Forme*> MesBords;
    Mat Img_Original;
    Mat Img_Transform;
    Mat Img_Contrast;
    Mat Img_Canny;
    Mat Img_Mask;
    Mat Drawing;
    Point2f corners[4];

    //Contrast
    int threshold_value;
    int max_BINARY_value;
    int threshold_type;

    //Canny
    int lowThreshold;
    int highThreshold;
    int v_ratio;
    int kernel_size;

    // approxPolyDP
    float epsilon;

    //Fonctions :
    void CreateFormes();
    bool CreateBords();
    double angle(Point pt1, Point pt2, Point pt0);
    void setLabel(Mat& im, const string label, vector<Point>& contour);
    Mat Contrast(Mat img,float beta,float alpha);
    int Get_Nb_Bord();

public:
    LesFormes();
    LesFormes(Mat img);
    ~LesFormes();
    void Set_Img(Mat img);
    int Get_Nb_Forme(){return MesFormes.size(); }
    Forme* Get_Forme(int index);
    Mat Get_Img_Original();
    Mat getImg_Transform(){return Img_Transform;};
    void setImg_Transform(vector<Coord> c, Mat img);
    Mat Get_Img_Canny();
    Mat Get_Img_Contrast();

};
