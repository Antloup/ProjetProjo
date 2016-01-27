#include "LesFormes.h"
#include "Forme.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cercle.h"
#include <iostream>

using namespace std;
using namespace cv;

LesFormes::LesFormes()
{
    threshold_value = 185;
    max_BINARY_value = 255;
    threshold_type = 1;
    lowThreshold = 500;
    highThreshold= 1000;
    v_ratio = 1;
    kernel_size = 3;
    epsilon = 0.04;
    phase=1;


}

LesFormes::LesFormes(Mat img)
{
    threshold_value = 160;
    max_BINARY_value = 255;
    threshold_type = 1;
    lowThreshold = 500;
    highThreshold= 1000;
    v_ratio = 1;
    kernel_size = 3;
    epsilon = 0.04;
    phase=1;

    Img_Original = img;
    Img_Contrast = Contrast(Img_Original,1,2);

    CreateFormes();

}

LesFormes::~LesFormes()
{

    for(int i=0; i<MesFormes.size(); i++)
    {
        free(MesFormes.at(i));
    }

    for(int i=0; i<MesBords.size(); i++)
    {
        free(MesBords.at(i));
    }
}

void LesFormes::Set_Img(Mat img)
{
    Img_Original=img;
    Img_Contrast=Contrast(Img_Original,1,1);

    CreateFormes();

}

void LesFormes::CreateFormes()
{

    for(int i=0; i<MesFormes.size(); i++)
    {
        free(MesFormes.at(i));
    }
    MesFormes = vector<Forme*>(); // Vide vector Forme

    //cvtColor(Img_Contrast, Img_Canny, CV_BGR2HSV);
    //cvtColor(Img_Contrast, Img_Canny, CV_RGB2GRAY);
    Img_Canny=Img_Contrast.clone();
    //GaussianBlur(Img_Canny, Img_Canny, Size(7,7), 1, 1);
    Canny(Img_Canny, Img_Mask, lowThreshold, highThreshold, kernel_size); // A mettre en variable

    /*  Fenetre Curseur : */
    namedWindow("Control_Canny", CV_WINDOW_AUTOSIZE);

    createTrackbar("lowThreshold", "Control_Canny", &lowThreshold, 2000); //Hue (0 - 179)
    createTrackbar("highThreshold", "Control_Canny", &highThreshold, 2000);
    //

    Img_Mask.convertTo(Img_Canny, CV_8U);

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(Img_Canny,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    Drawing = cv::Mat::zeros(Img_Mask.size(), CV_8UC3 );

    std::vector<cv::Point> approx;

    for( int i = 0; i< contours.size(); i++ )
    {

        // Approximate contour with accuracy proportional
        // to the contour perimeter
        //cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*epsilon, true);

        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;

        if (approx.size() == 3) // Triangle
        {
            Coord Coords[3];
            vector<Point>::iterator vertex;
            int j=0;
            for(vertex = approx.begin(); vertex != approx.end(); ++vertex)
            {
                circle(Img_Canny,*vertex,2,cv::Scalar(255,0,0),2);

                //cout<<"*vertex : "<<*vertex<<endl;
                Coords[j].x=vertex->x;
                Coords[j].y=vertex->y;
                j++;
            }

            MesFormes.push_back(new Triangle(Coords));
            setLabel(Img_Canny, "TRI", contours[i]);
            //cout<<"TRI"<<endl;
        }

        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();

            // Get the cosines of all corners
            std::vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));

            // Sort ascending the cosine values
            std::sort(cos.begin(), cos.end());

            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();

            // Use the degrees obtained above and the number of vertices
            // to determine the shape of the contour
            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)  // Rectangle
            {
                cv::RotatedRect boundingBox = cv::minAreaRect(contours[i]);

                boundingBox.points(corners);

                Coord Coords[4];
                for(int j=0; j<4; j++)
                {
                    cv::circle(Img_Canny,corners[j],2,cv::Scalar(255,0,0),2);
                    Coords[j].x=corners[j].x;
                    Coords[j].y=corners[j].y;
                }
                MesFormes.push_back(new Rectangle(Coords));
                setLabel(Img_Canny, "RECT", contours[i]);
                //cout<<"RECT"<<endl;
            }

        }
        else
        {
            Coord Coords;
            // Detect and label circles
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);
            int radius = r.width / 2;

            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                    std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
            {
                Coords.x=r.x;
                Coords.y=r.y;
                setLabel(Img_Canny, "CIR", contours[i]);
                MesFormes.push_back(new Cercle(Coords,radius));
                //cout<<"CIR"<<endl;
            }

        }

    }
}


bool LesFormes::CreateBords()
{
    for(int i=0; i<MesBords.size(); i++)
    {
        free(MesBords.at(i));
    }
    MesBords = vector<Forme*>(); // Vide vector Bords

    for(int i=0; i<MesFormes.size(); i++)
    {
        MesBords.push_back(MesFormes.at(i));
    }

}

Mat LesFormes::Get_Img_Original()
{
    return Img_Original;
}


Mat LesFormes::Get_Img_Canny()
{
    return Img_Canny;

}

Mat LesFormes::Get_Img_Contrast()
{
    return Img_Contrast;

}

Forme* LesFormes::Get_Forme(int index)
{
    return MesFormes.at(index);
}


/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
double LesFormes::angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/**
 * Helper function to display text in the center of a contour
 */
void LesFormes::setLabel(Mat& im, const string label, vector<Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);

    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

Mat LesFormes::Contrast(Mat img,float beta,float alpha)
{
    //Binary

    /*  Fenetre Curseur : */
    namedWindow("ControlContrast", CV_WINDOW_AUTOSIZE);

    createTrackbar("threshold_value", "ControlContrast", &threshold_value, 255); //Hue (0 - 179)
    createTrackbar("max_BINARY_value", "ControlContrast", &max_BINARY_value, 255);
    createTrackbar("threshold_type", "ControlContrast", &threshold_type, 4); //Saturation (0 - 255)
    //createTrackbar("epsilon", "ControlContrast", &epsilon, 100); //Saturation (0 - 255)
    //

    Mat Binary;
    //Binary=img.clone();
    cvtColor(img, Binary, CV_RGB2GRAY);

    GaussianBlur(Binary, Binary, Size(5,5), 5, 5);
    threshold( Binary, Binary, threshold_value, max_BINARY_value,threshold_type );
    return Binary;

    //Contrast
    /*
    Mat Contrast = Mat::zeros( img.size(), img.type() );
    for( int y = 0; y < img.rows; y++ )
    { for( int x = 0; x < img.cols; x++ )
         { for( int c = 0; c < 3; c++ )
              {
                Contrast.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( img.at<Vec3b>(y,x)[c] ) + beta );
              }
         }
    }
    return Contrast;
    */
}

/*
int LesFormes::Get_Nb_Bord()
{
    int Nb_Bord=0;
    for(int i=0; i<MesFormes.size(); i++)
    {
        string FName=MesFormes.at(i)->Get_name();
        if (FName.compare(0,FName.size(),"Rectangle") == 0)
        {
            Nb_Bord++;
        }
    }
    cout<<"Nb_Bord : "<<Nb_Bord<<endl;
    return Nb_Bord;

}
*/
void LesFormes::setImg_Transform(vector<Coord> c, Mat img){

    // Define the destination image
    cv::Mat quad = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);

    // Corners of the destination image
    std::vector<cv::Point2f> quad_pts;
    std::vector<cv::Point2f> corners;

    //Dumb push
    corners.push_back(cv::Point2f(c.at(3).x,c.at(3).y));
    corners.push_back(cv::Point2f(c.at(2).x,c.at(2).y));
    corners.push_back(cv::Point2f(c.at(1).x,c.at(1).y));
    corners.push_back(cv::Point2f(c.at(0).x,c.at(0).y));

    cout<<"c.size() :"<<c.size()<<endl;

    quad_pts.push_back(cv::Point2f(0, 0));
    quad_pts.push_back(cv::Point2f(quad.cols, 0));
    quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
    quad_pts.push_back(cv::Point2f(0, quad.rows));

    // Get transformation matrix
    cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);

    // Apply perspective transformation
    cv::warpPerspective(Img_Original, Img_Transform, transmtx, Img_Transform.size());
}
