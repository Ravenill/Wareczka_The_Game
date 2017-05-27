#pragma once
#include <SFML\Graphics.hpp>

class Bottle: public sf::Drawable, sf::Transformable
{
private:
	int value;
	sf::Vector2f pos;
	sf::ConvexShape shape;
	sf::Texture texture;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Bottle(int value_of_bottle);

	sf::Vector2f getPosition(size_t index) const;
	int getValue() const { return value; }
	void randomize();
};