#ifndef TESTTARGET_H
#define TESTTARGET_H
#include <SFML/Graphics.hpp>
#include "LesFormes.h"

class testTarget
{
    public:
        testTarget();
        virtual ~testTarget();
        void setPosition(LesFormes* f);
        void draw(sf::RenderWindow& window);
        void sortCorners(std::vector<cv::Point2f>& corners, cv::Point2f center);
        int getNbCentre(){return Centre.size();};
        vector<Coord> getCentre(){return Centre;};
    protected:
    private:
        vector<Coord> LesCoords;
        vector<Coord> Centre;
        vector<sf::RectangleShape> rect;
        bool activate = false;
};

#endif // TESTTARGET_H
