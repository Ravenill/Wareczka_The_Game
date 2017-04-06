#include "Gui.h"
#include <Windows.h>
#include <string>

#define RESX 1280
#define RESY 720

void Gui::update(StatusCar dead)
{
	std::string sc;
	setDead(dead);

	text[2].setString( ((is_dead == ALIVE) ? "OK" : "CRASHED" ) );

	sc = std::to_string(score);
	text[3].setString(sc);



}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < LP; i++) target.draw(text[i]);
}

Gui::Gui()
{
	if (!font.loadFromFile("data/Neon.ttf"))
	{
		MessageBox(NULL, "Error! Font Streamster.tff not found. Please, download it and paste into /data folder.", ERROR, NULL);
		return;
	}
	std::string content[] = { "Status: ", "Score: ", "0", "0"};

	for (int i = 0; i < LP; i++)
	{
		text[i].setFont(font);
		text[i].setString(content[i]);
		text[i].setCharacterSize(25);
		text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
	}

	text[0].setPosition((5 + text[0].getGlobalBounds().width), 35);
	text[1].setPosition((RESX - 5 - text[1].getGlobalBounds().width), 35);
	text[2].setPosition((5 + text[0].getGlobalBounds().width), (40 + text[0].getGlobalBounds().height));
	text[3].setPosition((RESX - 5 - text[1].getGlobalBounds().width), (40 + text[1].getGlobalBounds().height));

	score = 0;
	max_score = 0;
	is_dead = ALIVE;
}
