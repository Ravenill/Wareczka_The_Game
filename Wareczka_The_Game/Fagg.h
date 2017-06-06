#pragma once
#include <SFML\Graphics.hpp>
#include "AStar.h"
#include <stack>

class Fagg : public sf::Drawable, sf::Transformable
{
private:
	sf::CircleShape shape;
	AStar a_star;

	int x_dest;
	int y_dest;
	std::stack <sf::Vector2f> path;
	sf::Vector2f current_d;

	int speed;
	float radius;
	bool _hit;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void randDest();
	void destination();
	void move();

public:
	Fagg();

	void hit() { _hit = 1; }
	bool getHitStatus() { return _hit; }

	sf::Vector2f getPosition() { return shape.getPosition(); }
	float getRadius() { return radius; }

	void update();
};