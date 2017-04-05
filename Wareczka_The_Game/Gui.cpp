#include "Gui.h"
#include <Windows.h>
#include <string>

#define RESX 1280
#define RESY 720

void Gui::update()
{

}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

Gui::Gui()
{
	if (!Font.loadFromFile("data/Neon.ttf"))
	{
		MessageBox(NULL, "Error! Font Streamster.tff not found. Please, download it and paste into /data folder.", ERROR, NULL);
		return;
	}
	std::string content = { "Status: ", "Score: " };

	for (int i = 0; i < LP; i++)
	{
		text[i].setFont(Font);
		if (i < 2) text[i].setString(content[i]);
		text[i].setCharacterSize(50);
		text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
	}

	text[0].setPosition(0, 0);
	text[0].setPosition(0, 0);
	text[0].setPosition(0, 0);
	text[0].setPosition(0, 0);
}
