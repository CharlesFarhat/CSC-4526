#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::CircleShape shape(150.F);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
	sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	}

	window.clear();
	window.draw(shape);
	window.display();
    }

    return 0;
}
