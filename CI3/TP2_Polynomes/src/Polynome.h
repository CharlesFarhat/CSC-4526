//
// Created by charl on 5/16/2023.
//

#include <vector>
#include <iostream>
#include <map>

#pragma once

class Polynome {
public:
    Polynome(std::vector<double> const& polynome);

    Polynome(std::map<int, double> polynome);

    Polynome();

    bool operator==(const Polynome &p) const {
        return polynome == p.polynome;
    }

    Polynome derive();
    int degree();

    friend Polynome operator+(Polynome const& p1, Polynome const& p2);
    friend Polynome operator+(double d, Polynome const& p1);
    friend Polynome operator+(Polynome const& p1, double d);
    friend std::ostream &operator<<(std::ostream& os, Polynome const& p);

private:
    std::map<int, double> polynome;
};
