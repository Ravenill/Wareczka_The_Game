#include "Fagg.h"
#include <string>
#include <ctime>

#define POSX 200
#define POSY 200
#define NODEX 32
#define NODEY 33

void Fagg::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape);
}

Fagg::Fagg() : a_star(static_cast<std::string>("data/graphics/Ch2/map_fagg.bmap"))
{
	srand(static_cast<unsigned int>(time(NULL)));
	
	speed = 1;
	radius = 10.0;
	_hit = 0;

	//set a policeman
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
	shape.setPosition(POSX, POSY);

	destination();
}

void Fagg::randDest()
{
	x_dest = (std::rand() % a_star.getBoundsX());
	y_dest = (std::rand() % a_star.getBoundsY());
}

void Fagg::destination()
{
	//destination
	randDest();
	a_star.runPathFinder((shape.getPosition().x/NODEX), (shape.getPosition().y/NODEY), x_dest, y_dest);
	a_star.getPath(path);
	current_d = path.top();
	path.pop();
}

void Fagg::move()
{
	int x = 0, y = 0;

	if ((current_d.x - shape.getPosition().x) > 0)
		x = speed;
	else
		x = -speed;

	if ((current_d.y - shape.getPosition().y) > 0)
		y = speed;
	else
		y = -speed;

	shape.move(x, y);
}

void Fagg::update()
{
	move();

	if (((shape.getPosition().x < current_d.x + 5) && (shape.getPosition().x > current_d.x - 5)) && ((shape.getPosition().y < current_d.y + 5) && (shape.getPosition().y > current_d.y - 5)))
	{
		current_d = path.top();
		path.pop();
	}

	if (path.empty())
		destination();

}
