#include "Bottle.h"
#include <ctime>
#include <Windows.h>

#define RESX 1280
#define RESY 720
#define WALL 30

#define XBLOCK 20.0f
#define YBLOCK 45.0f

Bottle::Bottle(int value_of_bottle)
{
	srand(static_cast<unsigned int>(time(NULL)));
	
	value = value_of_bottle;
	pos.x = static_cast<float>((rand() % (RESX - 4 * WALL)) + (2 * WALL));
	pos.y = static_cast<float>((rand() % (RESY - 4 * WALL)) + (2 * WALL));

	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(XBLOCK, 0));
	shape.setPoint(2, sf::Vector2f(XBLOCK, YBLOCK));
	shape.setPoint(3, sf::Vector2f(0, YBLOCK));

	shape.setOrigin((XBLOCK / 2), (YBLOCK / 2));
	shape.setPosition(pos.x, pos.y);

	//loading textures
	if (!texture.loadFromFile("data/graphics/Ch2/wareczka.png"))
	{
		MessageBox(NULL, "Error! Textures not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}
	shape.setTexture(&texture);
}

void Bottle::randomize()
{
	pos.x = static_cast<float>((rand() % (RESX - 4 * WALL)) + (2 * WALL));
	pos.y = static_cast<float>((rand() % (RESY - 4 * WALL)) + (2 * WALL));
	shape.setPosition(pos.x, pos.y);
}

sf::Vector2f Bottle::getPosition(size_t index) const
{
	return shape.getTransform().transformPoint(shape.getPoint(index));
}

void Bottle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape);
}
