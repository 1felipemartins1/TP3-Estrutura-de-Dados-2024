#include "Pares.hpp"

Distpair::Distpair(std::string id, double dist) : id(id), distancia(dist) {}

bool Distpair::operator<(const Distpair &other) const
{
    return distancia < other.distancia;
}

bool Distpair::operator<=(const Distpair &other) const
{
    return distancia <= other.distancia;
}

bool Distpair::operator>(const Distpair &other) const
{
    return distancia > other.distancia;
}

bool Distpair::operator>=(const Distpair &other) const
{
    return distancia >= other.distancia;
}
