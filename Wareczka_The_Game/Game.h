#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "States.h"


class Game
{
private:
	sf::ContextSettings setting;
	sf::RenderWindow MainWindow;
	sf::Font Font;
	sf::Texture TextureMenu1;
	sf::Texture TextureMenu2;
	sf::Texture Frame;
	sf::Image icon;
	sf::Music Musicbckgrd;
	bool musicinmenu;
	bool fullscreen;

protected:
	Status State;

public:
	Game();
	~Game();
	void runGame();

	void menu1();
	void menu2();
	void game1();
	void game2();
	void game3();
	void gameOver();
};
