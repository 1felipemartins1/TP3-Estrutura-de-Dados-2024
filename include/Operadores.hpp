#ifndef POINT_POINTID_HPP
#define POINT_POINTID_HPP

#include <string>

struct Point
{
    double cordx, cordy;
    Point(double cordx = 0, double cordy = 0);

    bool operator<(Point other);
    bool operator<=(Point other);
    bool operator>(Point other);
    bool operator>=(Point other);
};

struct PointID
{
    std::string id;
    Point p;

    bool operator<(PointID other);
    bool operator<=(PointID other);
    bool operator>=(PointID other);
    bool operator>(PointID other);
};

#endif // POINT_POINTID_HPP
