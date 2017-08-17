#include "Camera.h"

sf::Vector2f camera::randomizeCenterFromDrunkLevel(int drunkLevel)
{
	float x = RESX/2, y = RESY/2;
	
	if (drunkLevel > 0 && counter > 10)
	{
		int range;
		range = (drunkLevel / 5) + 1;


		int randomNumber = (std::rand() % ((range * 2)-1)) - (range-1);
		x += randomNumber;

		randomNumber = (std::rand() % ((range * 2) - 1)) - (range - 1);
		y += randomNumber;
		counter = 0;
	}
	counter++;
	return sf::Vector2f(x, y);
}

sf::Vector2f camera::randomizeSizeFromDrunkLevel(int drunkLevel)
{
	float x = RESX, y = RESY;

	if (drunkLevel > 0 && counter2 > 12)
	{
		int range;
		range = (drunkLevel / 2) + 1;


		int randomNumber = (std::rand() % ((range * 2) - 1)) - (range - 1);
		x += randomNumber;

		randomNumber = (std::rand() % ((range * 2) - 1)) - (range - 1);
		y += randomNumber;
		counter2 = 0;
	}
	counter2++;
	return sf::Vector2f(x, y);
}

camera::camera() : view(sf::Vector2f(RESX / 2, RESY / 2), sf::Vector2f(RESX, RESY))
{
	defaultView = view;
	counter = 0;
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
	view.setCenter(randomizeCenterFromDrunkLevel(score));
	view.setSize(randomizeSizeFromDrunkLevel(score));
}
