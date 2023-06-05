#include "Turtle.h"
#include <SFML/Graphics.hpp>

namespace turtle {

double turtleX;
double turtleY;
double turtleDir;
bool turtlePenDown;
unsigned char const * turtleColor;

std::unique_ptr<sf::RenderWindow> window;
sf::VertexArray lines(sf::Lines);
std::unique_ptr<sf::Texture> turtleTexture;
std::unique_ptr<sf::Sprite> turtleSprite;

sf::Vector2f updateCoordinates;
void initTurtle()
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Logo");
	sf::Image img;
	img.loadFromFile("resources/turtle.bmp");
	img.createMaskFromColor(sf::Color::Magenta);
	turtleTexture = std::make_unique<sf::Texture>();
	turtleTexture->loadFromImage(img);
	turtleTexture->setSmooth(true);
	turtleSprite = std::make_unique<sf::Sprite>();
	turtleSprite->setTexture(*turtleTexture);
	turtleSprite->setOrigin(sf::Vector2f(28, 44)); // Middle of the image
	turtleX = 0;
	turtleY = 0;
	turtleDir = 0;
	turtlePenDown = true;
	turtleColor = black;
	sf::View centeredView(sf::Vector2f(0, 0), sf::Vector2f(800, 600));
	window->setView(centeredView);
	window->clear(sf::Color::White);
	window->display();
}

void uninitTurtle()
{
}

void redraw()
{
	sf::Event event;
	window->clear(sf::Color::White);
	window->pollEvent(event);
	window->draw(lines);
	turtleSprite->setPosition(static_cast<float>(turtleX), static_cast<float>(turtleY));
	turtleSprite->setRotation(static_cast<float>(turtleDir));
	window->draw(*turtleSprite);
	window->display();
}

// Change from mouse coordinates to bitmap coordinates
void drawLine(double x1, double y1, double x2, double y2, unsigned char const * color)
{
	sf::Color c(color[0], color[1], color[2]);
	lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1)), c));
	lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x2), static_cast<float>(y2)), c));
}

void rest(float s)
{
	sf::sleep(sf::seconds(s));
}

void waitEnd()
{
	while (window->isOpen())
	{
		// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window->pollEvent(event))
		{
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window->close();
		}
	}
}

bool interrupt()
{
	if (!window->isOpen())
	{
		return true;
	}
	// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
	sf::Event event;
	while (window->pollEvent(event))
	{
		// fermeture de la fenêtre lorsque l'utilisateur le souhaite
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window->close();
	}
	return !window->isOpen();
}


} // namespace turtle

