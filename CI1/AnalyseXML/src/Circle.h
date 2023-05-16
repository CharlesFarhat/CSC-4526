//
// Created by charl on 5/15/2023.
//
#pragma once
#include <string>



struct Circle {
    std::string label;
    double x;
    double y;
    double r;
    std::string color;
    std::string dump() const;
};


