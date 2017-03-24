#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Map: public sf::Drawable, sf::Transformable
{
private:
	sf::Texture texture;
	sf::Sprite map;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Map(std::string);
	~Map();
};