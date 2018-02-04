#pragma once
#include <SFML\Graphics.hpp>

#define RESX 1280
#define RESY 720

class camera
{
private:
	sf::View view;
	sf::View defaultView;
	int counter, counter2;

	sf::Vector2f randomizeNewPointFromDrunkLevel(int drunkLevel);
	sf::Vector2f randomizeSizeFromDrunkLevel(int drunkLevel);

public:
	camera();
	~camera();

	void setViewOnWindow(sf::RenderWindow* mainWindow);
	void update(int score);
};