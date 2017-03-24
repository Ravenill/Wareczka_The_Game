#include "Game.h"
#include "Engine2.h"
#include <Windows.h>
#include <string>


#define RESX 1280
#define RESY 720

Game::Game()
{
	State = END;
	setting.antialiasingLevel = 8;

	//Tworzenie okna
	MainWindow.create(sf::VideoMode(RESX, RESY), L"Wareczka The GAME", sf::Style::Close, setting);
	MainWindow.setVerticalSyncEnabled(true);
	MainWindow.requestFocus(); //Mo¿e pokaszaniæ
	MainWindow.setActive(); //Mo¿e pokaszaniæ
	MainWindow.setMouseCursorGrabbed(true);

	//£adowanie textur, czcionek i reszty
	if (!Font.loadFromFile("data/Streamster.ttf"))
	{
		MessageBox(NULL, "Error! Font Streamster.tff not found. Please, download it and paste into /data folder.", ERROR, NULL);
		return;
	}
	if (!TextureMenu1.loadFromFile("data/graphics/bckgrd.png") || !TextureMenu2.loadFromFile("data/graphics/bckgrd2.png") || !Frame.loadFromFile("data/graphics/empty.png") || !icon.loadFromFile("data/graphics/icon.png"))
	{
		MessageBox(NULL, "Error! Textures not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}
	if (!Musicbckgrd.openFromFile("data/sounds/msc.ogg"))
	{
		MessageBox(NULL, "Error! Music not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}

	//ikona i ostateczne ustawienia
	MainWindow.setIcon(100, 100, icon.getPixelsPtr());
	Musicbckgrd.setLoop(true);
	Musicbckgrd.setVolume(20);
	musicinmenu = false;
	fullscreen = 0;
	State = MENU1;
}

Game::~Game()
{

}

void Game::runGame()
{
	while (State != END)
	{
		switch (State)
		{
		case MENU1:
			menu1();
			break;
		case MENU2:
			menu2();
			break;
		case GAME1:
			game1();
			break;
		case GAME2:
			game2();
			break;
		case GAME3:
			game3();
			break;
		case GAME_OVER:
			//
			break;
		}
	}
}

void Game::menu1()
{
	//Muzyka i kursor
	MainWindow.setMouseCursorVisible(true);
	if (musicinmenu == 0)
	{
		Musicbckgrd.play();
		musicinmenu = 1;
	}

	//Background
	sf::Sprite background;
	background.setTexture(TextureMenu1);
	background.setOrigin(1280 / 2, 720 / 2);
	background.setPosition(1280 / 2, 720 / 2);

	//Napisy w Menu1
	const int lp = 4;
	sf::Text text[lp];
	std::string str[lp] = { "Play", "Quit", "Fullscreen", "Windowed" };
	for (int i = 0; i < lp; i++)
	{
		text[i].setFont(Font);
		text[i].setString(str[i]);
		text[i].setCharacterSize(80);
		text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
	}
	text[0].setPosition(1280 / 2 - 300, 500);
	text[1].setPosition(1280 / 2 + 300, 500);

	text[2].setCharacterSize(30);
	text[2].setPosition(1340 - text[2].getGlobalBounds().width/2, 55);
	text[3].setCharacterSize(30);
	text[3].setPosition(1340 - text[3].getGlobalBounds().width/2, 55);

	while (State == MENU1)
	{
		//Obs³uga eventów
		sf::Event event;
		while (MainWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				MainWindow.close();
				State = END;
				break;

			case sf::Event::MouseButtonReleased:
				if (event.key.code == sf::Mouse::Left && text[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				{
					State = MENU2;
				}
				if (event.key.code == sf::Mouse::Left && text[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				{
					MainWindow.close();
					Musicbckgrd.stop();
					State = END;
				}
				//Fullscreen/Windowed
				if (!fullscreen)
				{
					if (event.key.code == sf::Mouse::Left && text[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
					{
						MainWindow.create(sf::VideoMode(RESX, RESY), L"Wareczka The GAME", sf::Style::Fullscreen, setting);
						MainWindow.setVerticalSyncEnabled(true);
						MainWindow.requestFocus(); //Mo¿e pokaszaniæ
						MainWindow.setActive(); //Mo¿e pokaszaniæ
						MainWindow.setMouseCursorGrabbed(true);
						fullscreen = 1;
					}
				}
				else
				{
					if (event.key.code == sf::Mouse::Left && text[3].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
					{
						MainWindow.create(sf::VideoMode(RESX, RESY), L"Wareczka The GAME", sf::Style::Close, setting);
						MainWindow.setVerticalSyncEnabled(true);
						MainWindow.requestFocus(); //Mo¿e pokaszaniæ
						MainWindow.setActive(); //Mo¿e pokaszaniæ
						MainWindow.setMouseCursorGrabbed(true);
						fullscreen = 0;
					}
				}
				break;

			default:
				break;
			}//koniec CASE
		}//Koniec While PollEvent

		//Obs³uga efektów
		for (int i = 0; i < lp; i++)
		{
			if (text[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
			{
				text[i].setFillColor(sf::Color(254, 153, 219, 255));
				text[i].setCharacterSize(i >= 2 ? 35 : 85);
			}
			else
			{
				text[i].setFillColor(sf::Color::White);
				text[i].setCharacterSize(i >= 2 ? 30 : 80);
			}
		}


		//Rendering
		MainWindow.clear();
		MainWindow.draw(background);
		for (int i = 0; i < 2; i++) MainWindow.draw(text[i]);
		MainWindow.draw(fullscreen ? text[3] : text[2]);
		MainWindow.display();
	}//Koniec While State
}

void Game::menu2()
{
	if (musicinmenu == 0)
	{
		Musicbckgrd.play();
		musicinmenu = 1;
	}
	
	//Background
	sf::Sprite background;
	background.setTexture(TextureMenu2);
	background.setOrigin(1280 / 2, 720 / 2);
	background.setPosition(1280 / 2, 720 / 2);

	//Wróæ Button
	sf::Text text;
	text.setFont(Font);
	text.setString("Back");
	text.setCharacterSize(60);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(1280 / 2, 670);

	//Frames
	sf::Sprite frame[3];
	for (int i = 0; i < 3; i++)
	{
		frame[i].setTexture(Frame);
		frame[i].setOrigin(static_cast<float>(338/2), static_cast<float>(583/2));
	}
	frame[0].setPosition(209, 337);
	frame[1].setPosition(632, 336);
	frame[2].setPosition(1071, 337);

	while (State == MENU2)
	{
		//Obs³uga Eventów
		sf::Event event;
		while (MainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				State = END;
			//Back
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				State = MENU1;
			//Chapter1
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && frame[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				State = GAME1;
			//Chapter2
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && frame[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				State = GAME2;
			//Chapter3
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && frame[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
				State = GAME3;
		}//Koniec WHILE pollEvent

		//Obs³uga efektów
		//Frames
		for (int i = 0; i < 3; i++)
		{
			if (frame[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
			{
				frame[i].setColor(sf::Color(157, 0, 103, 225));
				frame[i].setScale(1.02f, 1.02f);
			}
			else
			{
				frame[i].setColor(sf::Color(254, 153, 219, 225));
				frame[i].setScale(1/1.03f, 1/1.025f);
			}
		}
		//Back
		if (text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(MainWindow))))
		{
			text.setFillColor(sf::Color(254, 153, 219, 225));
			text.setCharacterSize(65);
		}
		else
		{
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(60);
		}


		//Rendering
		MainWindow.clear();
		MainWindow.draw(background);
		for (int i = 0; i < 3; i++) MainWindow.draw(frame[i]);
		MainWindow.draw(text);
		MainWindow.display();
	}//Koniec WHILE State
}

void Game::game1()
{
	MessageBox(NULL, "DLC will be released soon!", "Information", MB_ICONINFORMATION);
	State = MENU2;
}

void Game::game2()
{
	musicinmenu = 0;
	Musicbckgrd.pause();

	State = GAME2;

	Engine2 engine(MainWindow);
	engine.run();

	State = MENU2;
}

void Game::game3()
{
	MessageBox(NULL, "DLC will be released soon!", "Information", MB_ICONINFORMATION);
	State = MENU2;
}

void Game::gameOver()
{

}