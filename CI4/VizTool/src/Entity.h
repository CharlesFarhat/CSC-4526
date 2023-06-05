//
// Created by charl on 5/17/2023.
//
#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Entity {

public:
    explicit Entity(std::string const &label = "");

    virtual ~Entity() = default;

    virtual void draw(sf::RenderWindow &window, double offset_x = 0, double offset_y = 0) = 0;

    [[nodiscard]] virtual std::string dump(std::string const &indent = "") const = 0;

    virtual void modify() = 0;

    virtual Entity* search(std::string const &label) = 0;

    std::string get_label() {
        return label;
    }

protected:
    std::string label;
};
