#pragma once
#include <SFML\Graphics.hpp>

#define LP 4

class Gui : public sf::Drawable
{
private:
	sf::Font Font;
	sf::Text text[LP];
	int score;
	int maxScore;
	bool isDead;
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Gui();

	void setscore(int a) { score = a; };
	void update();
};