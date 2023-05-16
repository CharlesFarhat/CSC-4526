//
// Created by charl on 5/16/2023.
//

#include "Polynome.h"
#include <utility>

Polynome::Polynome(std::vector<double> const &polynome) {
    int degree = 0;
    for (const auto i: polynome) {
        this->polynome.insert({degree, i});
        degree++;
    }
}

Polynome::Polynome(std::map<int, double> polynome) {
    this->polynome = std::move(polynome);
}

Polynome::Polynome() {
    this->polynome.insert({0, 0});
}

std::ostream &operator<<(std::ostream &os, const Polynome &p) {
    os << "Polynome: ";
    for (auto it = p.polynome.begin(); it != p.polynome.end(); ++it) {
        if (it != p.polynome.begin()) {
            os << " + ";
        }
        os << it->second << "X^" << it->first;
    }
    os << std::endl;
    return os;
}

Polynome operator+(const Polynome &p1, const Polynome &p2) {
    Polynome result(p1.polynome);

    for (auto it = p2.polynome.begin(); it != p2.polynome.end(); ++it) {
        result.polynome[it->first] += it->second;
    }
    return result;
}

Polynome operator+(double d, const Polynome &p1) {
    Polynome result(p1.polynome);

    for (auto it = result.polynome.begin(); it != result.polynome.end(); ++it) {
        it->second += d;
    }
    return result;
}

Polynome operator+(const Polynome &p1, double d) {
    Polynome result(p1.polynome);

    for (auto it = result.polynome.begin(); it != result.polynome.end(); ++it) {
        it->second += d;
    }
    return result;
}

Polynome Polynome::derive() {
    Polynome deriv;
    if (this->degree() == 0) {
        return deriv;
    }
    for (auto it=this->polynome.begin(); it != polynome.end(); it++) {
        deriv.polynome.insert({it->first -1, it->second * it->first});
    }
    return deriv;
}

int Polynome::degree() {
    auto it=this->polynome.end();
    it--;
    int degree=it->first;
    return degree;
}



