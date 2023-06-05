#pragma once

#include <string>
#include <pugixml.hpp>
#include "Entity.h"
#include <iostream>

class Circle : public Entity {
public:
    explicit Circle(const pugi::xml_node &node);

    [[nodiscard]] std::string dump(std::string const &indent = "") const override;

    void draw(sf::RenderWindow &window, double offset_x = 0, double offset_y = 0) override;

    void modify() override;

    void setColor(const std::string& color);

    Entity* search(std::string const& label) override;

private:
    double x;
    double y;
    double r;
    std::string color;
};