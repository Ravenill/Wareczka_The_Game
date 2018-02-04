#pragma once
#include <SFML\Graphics.hpp>

#define RESX 1280
#define RESY 720

class camera
{
private:
	sf::View view;
	sf::View defaultView;
    sf::Vector2f destination;
    sf::Clock clock;
    sf::Time lastChange;

	void randomizeNewPointFromDrunkLevel(int drunkLevel);
    bool isDestination();
    sf::Vector2f getNextCordsToDestination();

public:
	camera();
	~camera();

	void setViewOnWindow(sf::RenderWindow* mainWindow);
	void update(int score);
};