//
// Created by charl on 5/15/2023.
//
#include <sstream>
#include "Circle.h"

std::string Circle::dump() const {
    std::ostringstream oss;
    oss << "Circle " << label << ",";
    oss << " x: " << x << ",";
    oss << " y: " << y << ",";
    oss << " r: " << r << ",";
    oss << " color: " << color << "," <<std::endl;
    return oss.str();
}
