#include <sstream>
#include "Circle.h"
#include "utils.h"


using namespace std;

Circle::Circle(const pugi::xml_node &node) : Entity(node.attribute("label").as_string()),
                                             x(node.attribute("x").as_double()),
                                             y(node.attribute("y").as_double()),
                                             r(node.attribute("r").as_double()),
                                             color(node.attribute("color").as_string()) {}

std::string Circle::dump(std::string const &indent) const {
    ostringstream oss;
    oss << indent
        << "Circle " << "\"" << this->label << "\", "
        << "x: " << x << ", "
        << "y: " << y << ", "
        << "r: " << r << ", "
        << "color: " << "\"" << color << "\"" << endl;
    return oss.str();
}

void Circle::draw(sf::RenderWindow &window, double offset_x, double offset_y) {
    // Create shape
    sf::CircleShape circle(r);

    // Parse the color
    switch (str2int(color.c_str())) {
        case str2int("Magenta"):
            circle.setFillColor(sf::Color::Magenta);
            break;
        case str2int("Red"):
            circle.setFillColor(sf::Color::Red);
            break;
        case str2int("Green"):
            circle.setFillColor(sf::Color::Green);
            break;
        case str2int("Black"):
            circle.setFillColor(sf::Color::Black);
            break;
        default:
            circle.setFillColor(sf::Color::Cyan);
    }

    // set shape correct position from center
    circle.setPosition(window.getSize().x / 2 - r + x + offset_x, window.getSize().y / 2 - r - y - offset_y);
    // draw on window
    window.draw(circle);
}

void Circle::modify() {
    std::cout << "1 : Change color\n"
                 "2 : Copy\n"
                 "3 : Translation by (delta_x, delta_y) \n";
    int response;
    cin >> response;

    switch (response) {
        case 1: {
            std::string new_color;
            cin >> new_color;
            this->setColor(color);
            std::cout << "Color changed" << std::endl;
            break;
        }
        case 2:
            cout << "Copy is yet to be implemented" << endl;
            break;
        case 3:
            cout << "delta_x :";
            int delta_x;
            cin >> delta_x;
            this->x += delta_x;
            cout << "delta_y :";
            int delta_y;
            cin >> delta_y;
            this->x += delta_y;
            break;
        default:
            cout << "Didn't understand your request !";

    }
}

Entity *Circle::search(const string &label) {
    if (label == this->label)
        return this;
    return nullptr;
}

void Circle::setColor(const string &color) {
    this->color = color;
}
