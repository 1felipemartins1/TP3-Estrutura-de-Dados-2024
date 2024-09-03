#include "Operadores.hpp"

Point::Point(double cordx, double cordy) : cordx(cordx), cordy(cordy) {}

bool Point::operator<(Point other)
{
    if (cordx == other.cordx)
    {
        return cordy < other.cordy;
    }
    return cordx < other.cordx;
}

bool Point::operator<=(Point other)
{
    if (cordx == other.cordx)
    {
        return cordy <= other.cordy;
    }
    return cordx <= other.cordx;
}

bool Point::operator>(Point other)
{
    if (cordx == other.cordx)
    {
        return cordy > other.cordy;
    }
    return cordx > other.cordx;
}

bool Point::operator>=(Point other)
{
    if (cordx == other.cordx)
    {
        return cordy >= other.cordy;
    }
    return cordx >= other.cordx;
}

bool PointID::operator<(PointID other)
{
    return p < other.p;
}

bool PointID::operator<=(PointID other)
{
    return p <= other.p;
}

bool PointID::operator>=(PointID other)
{
    return p >= other.p;
}

bool PointID::operator>(PointID other)
{
    return p > other.p;
}
