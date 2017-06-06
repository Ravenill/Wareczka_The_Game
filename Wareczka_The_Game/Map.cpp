#include "Map.h"
#include <Windows.h>

Map::Map(std::string path)
{
	//load and set map texture
	if (!texture.loadFromFile(path))
	{
		MessageBox(NULL, "Error! Textures not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}
	map.setTexture(texture);
	map.setOrigin(1280 / 2, 720 / 2);
	map.setPosition(1280 / 2, 720 / 2);
}

Map::~Map()
{

}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(map);
}