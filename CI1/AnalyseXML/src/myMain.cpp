#include <iostream>
#include "myMain.h"
#include "Circle.h"
#include "pugixml.hpp"

int myMain() {
    std::string s = R"(<?xml version = "1.0"?>
        <Group label="testGroup" x="0" y="1">
          <Circle label="testCircle1" x="2" y="3" r="4" color="Black"/>
          <Circle label="testCircle2" x="5" y="6" r="7" color="Black"/>
        </Group>)";

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    if (!result) {
        std::cerr << result.description();
        exit(1);
    }
    pugi::xml_node node = doc.child("Circle");

    Circle circle;
    circle.label = node.attribute("label").as_string();
    circle.color = node.attribute("color").as_string();
    circle.x = node.attribute("x").as_double();
    circle.y = node.attribute("y").as_double();
    circle.r = node.attribute("r").as_double();

    std::cout << circle.dump();
    return 0;
}