#include "myMain.h"
#include "Group.h"
#include <pugixml.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.h"

using namespace std;

#define WINDOW_H 800
#define WINDOW_W 800


void modify(Group &g) {
    cout << "Enter the label of the object you want to mofify" << endl;
    string label;
    cin >> label;
    auto selected_node = g.search(label);
    if (!selected_node) {
        cerr << "The entered label does not exist !" << endl;
    }
    selected_node->modify();
}


int main() {
    pugi::xml_document doc;
    if (auto result = doc.load_file("resources/visage.xml"); !result) {
        std::cerr << "Could not open file visage.xml because " << result.description() << std::endl;
        return 1;
    }
    Group g(doc.child("Drawing"));
    std::cout << g.dump();
    std::cout << "MODIFY to modify (or SAVE to save in save.xml file or EXIT to exit)?" << std::endl;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML window");


    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear backdrop
        window.clear();
        sf::RectangleShape backdrop(sf::Vector2f(window.getSize().x, window.getSize().y));
        backdrop.setFillColor(sf::Color::White);
        window.draw(backdrop);
        // Draw all the shapes
        //window.draw(shape);
        g.draw(window);
        // Update the window
        window.display();


        // User command system
        string user_input;
        std::cin >> user_input;
        switch (str2int(user_input.c_str())) {
            case str2int("EXIT"):
                exit(0);
            case str2int("SAVE"):
                cout << "Saving file to disk" << endl;
                // launch save function
                break;
            case str2int("MODIFY"):
                modify(g);
                break;
            default:
                cout << "Could not understand your command please try again" << endl;
        }

    }

    return myMain();
}