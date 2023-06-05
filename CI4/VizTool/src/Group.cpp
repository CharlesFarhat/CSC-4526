#include <sstream>
#include "Group.h"
#include <memory>

using namespace std;
using namespace std::literals;


Group::Group(const pugi::xml_node &node) : Entity(node.attribute("label").as_string()) {
    this->x = node.attribute("x").as_double();
    this->y = node.attribute("y").as_double();

    for (pugi::xml_node subNode: node.children()) {
        if (subNode.name() == "Circle"sv) {
            this->children.push_back(std::make_unique<Circle>(subNode));
        }
        if (subNode.name() == "Group"sv) {
            this->children.push_back(std::make_unique<Group>(subNode));
        }
    }
}

std::string Group::dump(std::string const &indent) const {
    ostringstream oss;
    oss << indent
        << "Group " << "\"" << label << "\", "
        << "x: " << x << ", "
        << "y: " << y << ", "
        << "children: [" << endl;
    for (auto const &c: children) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}

void Group::draw(sf::RenderWindow &window, double offset_x, double offset_y) {
    // Draw all the childrens
    for (auto const &c: children) {
        c->draw(window, offset_x + x, offset_y + y);
    }
}

void Group::modify() {

}

Entity *Group::search(const string &label) {
    if (label == this->label)
        return this;
    for (auto const &subNode: children) {
        auto rep = subNode->search(label);
        if (rep)
            return rep;
    }
    return nullptr;
}
