#include "testTarget.h"
#include <SFML/Graphics.hpp>

#include <iostream>

testTarget::testTarget()
{
}

testTarget::~testTarget()
{
    //dtor
}

void testTarget::setPosition(LesFormes* f)
{
    rect.clear();
    Centre.clear();
    for(int i=0; i<f->Get_Nb_Forme(); i++)
    {
        Coord c;
        LesCoords=f->Get_Forme(i)->GetCoords();

        string FName=f->Get_Forme(i)->Get_name();
        if (FName.compare(0,FName.size(),"Rectangle") == 0)
        {
            c.y=(LesCoords.at(0).y+LesCoords.at(1).y)/2;
            c.x=(LesCoords.at(1).x+LesCoords.at(2).x)/2;
            std::cout<<"Coords : "<<i<<std::endl;
            std::cout<<"x: "<<c.x<<std::endl;
            std::cout<<"y: "<<c.y<<std::endl;
            Centre.push_back(c);
        }
        cout<<"Centre.size() : "<<Centre.size()<<endl;

    }
}

void testTarget::draw(sf::RenderWindow& window)
{
    for(int i=0; i<rect.size(); i++)
        window.draw(rect[i]);
}
