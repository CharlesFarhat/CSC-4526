#pragma once

#include <string>
#include <vector>
#include "Circle.h"
#include <pugixml.hpp>
#include "Entity.h"
#include <memory>

class Group : public Entity {
public:
    explicit Group(const pugi::xml_node &node);

    [[nodiscard]] std::string dump(std::string const &indent = "") const override;

    void draw(sf::RenderWindow &window, double offset_x = 0, double offset_y = 0) override;

    void modify() override;

    Entity* search(std::string const& label) override;


private:
    double x;
    double y;
    std::vector<std::unique_ptr<Entity>> children;
};
