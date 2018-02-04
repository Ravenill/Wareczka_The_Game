#include "Camera.h"
#include <iostream>

void camera::randomizeNewPointFromDrunkLevel(int drunkLevel)
{
	float x = RESX/2, y = RESY/2;
	
    drunkLevel = drunkLevel <= 15 ? 0 : drunkLevel - 15;

	if (drunkLevel > 0)
	{
		int range = ((drunkLevel / 5) + 1) ;

		int randomNumber = (std::rand() % ((range * 2) - 1)) - (range - 1);

		x += randomNumber;
		randomNumber = (std::rand() % ((range * 2) - 1)) - (range - 1);
		y += randomNumber;
	}
	destination = sf::Vector2f(x, y);
}

bool camera::isDestination()
{
    sf::Vector2f actual_cords = view.getCenter();

    if (actual_cords == destination)
        return true;
    else
        return false;
}

sf::Vector2f camera::getNextCordsToDestination()
{
    sf::Vector2f actual_cords = view.getCenter();

    float x = 0;
    float y = 0;
    
    if (actual_cords.x < destination.x)
        x = 1;
    else if (actual_cords.x > destination.x)
        x = -1;

    if (actual_cords.y < destination.y)
        y = 1;
    else if (actual_cords.y > destination.y)
        y = -1;

    return sf::Vector2f(x, y);
}

camera::camera() : view(sf::Vector2f(RESX / 2, RESY / 2), sf::Vector2f(RESX, RESY))
{
    randomizeNewPointFromDrunkLevel(0);
    lastChange = clock.getElapsedTime();
    defaultView = view;
}

camera::~camera()
{
	view = defaultView;
}

void camera::setViewOnWindow(sf::RenderWindow *mainWindow)
{
	mainWindow->setView(view);
}

void camera::update(int score)
{
    sf::Time actual_time = clock.getElapsedTime();
    //std::cerr << actual_time.asMilliseconds() << "\n";

    if (isDestination())
    {
        randomizeNewPointFromDrunkLevel(score);
    }
    if (actual_time.asMilliseconds() - lastChange.asMilliseconds() > 100)
    {
        view.move(getNextCordsToDestination());
        lastChange = clock.getElapsedTime();
    }
}
