#ifndef DISTPAIR_HPP
#define DISTPAIR_HPP

#include <iostream>
#include <string>

struct Distpair
{
    std::string id;
    double distancia;

    Distpair(std::string id = "", double distancia = 0);

    bool operator<(const Distpair &other) const;
    bool operator<=(const Distpair &other) const;
    bool operator>(const Distpair &other) const;
    bool operator>=(const Distpair &other) const;
};


#endif // DISTPAIR_HPP
