#pragma once
#include "Car.h"
#include "Map.h"
#include "Gui.h"
#include "Bottle.h"
#include "Fagg.h"
#include <string>

class Engine2
{
private:
	sf::RenderWindow *MainWindow;
	StatusGame2 State;
	Gui gui;
	Car player;
	Map map;
	Bottle wareczka;
	Fagg policeman;
		
	void update();
	void draw();
	void collision();
	bool isEscape();

	//SAT
	bool check_collision(sf::Vector2f *A, int sizeA, sf::Vector2f *B, int SizeB, sf::Vector2f &offset);


public:
	Engine2(sf::RenderWindow &win) : MainWindow(&win), map(static_cast<std::string>("data\\graphics\\Ch2\\map.jpg")), State(StatusGame2::RUN), wareczka(5) {};
	~Engine2() {}

	void run();
	void game();
	void end(bool win);
};

//SAT
void getInterval(const sf::Vector2f *axVertices, int numVert, const sf::Vector2f &xAxis, float &min, float &max);
bool IntervalIntersect(const sf::Vector2f *A, int Anum, const sf::Vector2f *B, int Bnum, const sf::Vector2f &xAxis, const sf::Vector2f &offset);
