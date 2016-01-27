#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <typeinfo>

#include "LesFormes.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    //création fenetre sfml
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    sf::RectangleShape rect1, rect2, rect3, rect4;
    rect1.setFillColor(sf::Color::White);
    rect1.setSize(sf::Vector2f(32,32));
    rect1.setPosition(100,50);
    rect2.setFillColor(sf::Color::White);
    rect2.setSize(sf::Vector2f(32,32));
    rect2.setPosition(600,50);
    rect3.setFillColor(sf::Color::White);
    rect3.setSize(sf::Vector2f(32,32));
    rect3.setPosition(500,500);
    rect4.setFillColor(sf::Color::White);
    rect4.setSize(sf::Vector2f(32,32));
    rect4.setPosition(155,450);

    sf::CircleShape c1, c2, c3, c4;
    c1.setFillColor(sf::Color::Red);
    c1.setRadius(7.f);
    c2.setFillColor(sf::Color::Red);
    c2.setRadius(7.f);
    c3.setFillColor(sf::Color::Red);
    c3.setRadius(7.f);
    c4.setFillColor(sf::Color::Red);
    c4.setRadius(7.f);

    // Touche clavier
    char key;
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    Mat Video;
    Mat Image;
    Image = imread("image.png", CV_LOAD_IMAGE_COLOR);
    LesFormes* Formes= new LesFormes();


    while (window.isOpen())
    {
        //event sfml
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cap >> Video; // get a new frame from camera
        // take a shoot
        //if(key=='s')
        {
            cout<<endl<<"NOUVELLE CAPTURE :"<<endl;
            // On enregistre l'image
            Formes->Set_Img(Video);

            imshow("Canny", Formes->Get_Img_Canny());
            imshow("Image", Formes->Get_Img_Original());
            imshow("Contrast", Formes->Get_Img_Contrast());

            for(int i=0; i<Formes->Get_Nb_Forme(); i++)
            {
                vector<Coord> c = Formes->Get_Forme(i)->GetCoords();
                string FName=Formes->Get_Forme(i)->Get_name();
                if (FName.compare(0,FName.size(),"Rectangle") == 0)
                {
                    //if(s_R.compare(Formes->Get_Forme(i)->Get_name())==0){ // Rectangle
                    cout<<"Rectangle : "<<i<<endl;
                }

                else if(FName.compare(0,FName.size(),"Triangle") == 0)
                {
                    cout<<"Triangle : "<<i<<endl;
                }

                else
                {
                    cout<<"Cercle : "<<i<<endl;
                    //cout<<"Rayon : "<<Formes->Get_Forme(i)->GetRayon()<<endl;
                }

                Formes->Get_Forme(i)->PrintCoord();
            }
            cout<<"Nb Bords :"<<Formes->Get_Nb_Bords()<<endl;
            if(Formes->Get_Nb_Bords()==4){
                cout<<"Bord ok, transformatiooooon !!" <<endl;
                Formes->setImg_Transform(Formes->getBords(),Formes->Get_Img_Original());
                imshow("Img_Transform",Formes->getImg_Transform());
            }

        }

        /* Affichage des frames */
        imshow("Video", Video);

        //affichage sfml
        window.clear();
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);

        window.display();

        // On attend 10ms
        key = cvWaitKey(10);

    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 1;
}
