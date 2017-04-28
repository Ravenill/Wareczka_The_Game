#pragma once
#include <SFML\Graphics.hpp>
#include "States.h"

#define LP 4

class Gui : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text text[LP];
	sf::Text text_time[5];
	int score;
	int max_score;
	StatusCar is_dead;
	sf::Clock clock;
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Gui();

	void setScore(int a) { score = score + a; }
	void setDead(StatusCar a) { is_dead = a; }
	void update(StatusCar dead);
};