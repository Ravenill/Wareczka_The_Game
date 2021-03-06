#include "Gui.h"
#include <Windows.h>
#include <string>

#define RESX 1280
#define RESY 720

void Gui::update(StatusCar dead)
{
	//TIME
	time = sf::milliseconds(60000) - clock.getElapsedTime();
	if (time < sf::milliseconds(0)) time = sf::milliseconds(0);

	//time counting
	int minutes, seconds, miliseconds;
	minutes = time.asMilliseconds() / 60000;
	time = time - sf::milliseconds(minutes * 60000);
	seconds = time.asMilliseconds() / 1000;
	time = time - sf::milliseconds(seconds * 1000);
	miliseconds = time.asMilliseconds();

	std::string times[3];
	times[0] = ((minutes < 10) ? "0" : "") + std::to_string(minutes);
	times[1] = ((seconds < 10) ? "0" : "") + std::to_string(seconds);
	times[2] = ((miliseconds < 10) ? "0" : "") + std::to_string(miliseconds);

	text_time[0].setString(times[0]);
	text_time[2].setString(times[1]);
	text_time[4].setString(times[2]);

	std::string sc;
	setDead(dead);

	text[2].setString( ((is_dead == StatusCar::ALIVE) ? "OK" : ((is_dead == StatusCar::DEAD) ? "CRASHED" : "ESCAPED")) );

	sc = std::to_string(score);
	text[3].setString(sc);
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < LP; i++) target.draw(text[i]);
	for (int i = 0; i < 5; i++) target.draw(text_time[i]);
}

Gui::Gui()
{
	//Loading fonts
	if (!font.loadFromFile("data/Neon.ttf"))
	{
		MessageBox(NULL, "Error! Font Streamster.tff not found. Please, download it and paste into /data folder.", ERROR, NULL);
		return;
	}

	//GUI - SCORE, STATUS
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

	//TIME
	std::string content2[] = { "00", ":", "00", ":", "00" };
	for (int i = 0; i < 5; i++)
	{
		text_time[i].setFont(font);
		text_time[i].setString(content2[i]);
		text_time[i].setCharacterSize(25);
		text_time[i].setOrigin(text_time[i].getGlobalBounds().width / 2, text_time[i].getGlobalBounds().height / 2);
	}

	text_time[0].setPosition(((RESX / 2) - text_time[2].getGlobalBounds().width - text_time[3].getGlobalBounds().width) - 5, (RESY - 30 - text_time[0].getGlobalBounds().height - 30));
	text_time[1].setPosition(((RESX / 2) - text_time[2].getGlobalBounds().width/2 - text_time[1].getGlobalBounds().width) - 1, (RESY - 30 - text_time[0].getGlobalBounds().height - 34));
	text_time[2].setPosition(((RESX / 2)), (RESY - 30 - text_time[2].getGlobalBounds().height - 30));
	text_time[3].setPosition(((RESX / 2) + text_time[2].getGlobalBounds().width/2 + text_time[3].getGlobalBounds().width) + 1, (RESY - 30 - text_time[4].getGlobalBounds().height - 34));
	text_time[4].setPosition(((RESX / 2) + text_time[2].getGlobalBounds().width + text_time[3].getGlobalBounds().width) + 5, (RESY - 30 - text_time[4].getGlobalBounds().height - 30));

	score = 0;
	max_score = 0;
	is_dead = StatusCar::ALIVE;
	clock.restart();
	time = sf::seconds(1);
}
