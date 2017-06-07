#include "Engine2.h"
#include <Windows.h>

#define RESX 1280
#define RESY 720
#define WALL 30

//looking for min - max interval
void getInterval(const sf::Vector2f * axVertices, int numVert, const sf::Vector2f & xAxis, float & min, float & max)
{
	min = max = (axVertices[0].x * xAxis.x + axVertices[0].y * xAxis.y);

	for (int i = 1; i<numVert; i++)
	{
		float d = (axVertices[i].x * xAxis.x + axVertices[i].y * xAxis.y);

		if (d<min) min = d;
		else if (d>max) max = d;
	}
}

//Interval intersect
bool IntervalIntersect(const sf::Vector2f * A, int Anum, const sf::Vector2f * B, int Bnum, const sf::Vector2f & xAxis, const sf::Vector2f & offset)
{
	float min0, max0;
	float min1, max1;

	getInterval(A, Anum, xAxis, min0, max0);
	getInterval(B, Bnum, xAxis, min1, max1);

	float h = offset.x * xAxis.x + offset.y*xAxis.y;
	min0 += h;
	max0 += h;

	float d0 = min0 - max1;
	float d1 = min1 - max0;

	if (d0 > 0.0f || d1 > 0.0f)
		return false;
	else
		return true;
}

//Collision checker
bool Engine2::check_collision(sf::Vector2f *A, int sizeA, sf::Vector2f *B, int sizeB, sf::Vector2f &offset)
{
	if (!A || !B) return false;

	//amount of corners (axis)
	sf::Vector2f xAxis[8];
	int iNumAxes = 0;

	//A test
	for (int j = sizeA - 1, i = 0; i<sizeA; j = i, i++)
	{
		sf::Vector2f E0 = A[j];
		sf::Vector2f E1 = A[i];
		sf::Vector2f E = E1 - E0;

		xAxis[iNumAxes] = sf::Vector2f(-E.y, E.x);

		if (!IntervalIntersect(A, sizeA, B, sizeB, xAxis[iNumAxes], offset))
			return false;

		iNumAxes++;
	}

	//B test
	for (int j = sizeB - 1, i = 0; i<sizeB; j = i, i++)
	{
		sf::Vector2f E0 = B[j];
		sf::Vector2f E1 = B[i];
		sf::Vector2f E = E1 - E0;
		xAxis[iNumAxes] = sf::Vector2f(-E.y, E.x);

		if (!IntervalIntersect(A, sizeA, B, sizeB, xAxis[iNumAxes], offset))
			return false;

		iNumAxes++;
	}

	return true;
}


void Engine2::collision()
{
	//Player
	sf::Vector2f player_car[4] = { player.getPosition(0), player.getPosition(1), player.getPosition(2), player.getPosition(3) };
	//Walls
	sf::Vector2f wall[5][4] = {{ sf::Vector2f(0, 0), sf::Vector2f(590, 0), sf::Vector2f(590, WALL), sf::Vector2f(0, WALL)},
							{ sf::Vector2f(690, 0), sf::Vector2f(RESX, 0), sf::Vector2f(RESX, WALL), sf::Vector2f(690, WALL)},
							{ sf::Vector2f(RESX-WALL, 0), sf::Vector2f(RESX-WALL, RESY), sf::Vector2f(RESX, RESY), sf::Vector2f(RESX, 0)},
							{ sf::Vector2f(0, RESY-WALL), sf::Vector2f(RESX, RESY-WALL), sf::Vector2f(RESX, RESY), sf::Vector2f(0, RESY)},
							{ sf::Vector2f(0, 0), sf::Vector2f(0, RESY), sf::Vector2f(WALL, RESY), sf::Vector2f(WALL, 0)} };
	//bottle
	sf::Vector2f bottle[4] = { wareczka.getPosition(0), wareczka.getPosition(1), wareczka.getPosition(2), wareczka.getPosition(3) };
	//policeman
	sf::Vector2f police[4] = { sf::Vector2f(policeman.getPosition().x - policeman.getRadius(),policeman.getPosition().y),
							   sf::Vector2f(policeman.getPosition().x,policeman.getPosition().y - policeman.getRadius()) ,
							   sf::Vector2f(policeman.getPosition().x,policeman.getPosition().y + policeman.getRadius()) ,
							   sf::Vector2f(policeman.getPosition().x + policeman.getRadius(),policeman.getPosition().y) };


	//collision with walls
	for (int j = 0; j < 4; j++)
	{
		for (int z = 0; z < 5; z++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (check_collision(player_car, 4, wall[z], 4, player_car[j] - wall[z][i]))
				{
					player.setStatus(StatusCar::DEAD);
					gui.resetScore();
					State = StatusGame2::GAME_OVER;
				}
			}
		}
	}

	//collision with bottles
	for (int i = 0; i < 4; i++)
	{
		if (check_collision(player_car, 4, bottle, 4, player_car[i] - bottle[i]))
		{
			gui.setScore(wareczka.getValue());
			wareczka.randomize();
		}
	}

	//collision with policeman
	if (!policeman.getHitStatus())
	{
		for (int i = 0; i < 4; i++)
		{
			if (check_collision(player_car, 4, police, 4, player_car[i] - police[i]))
			{
				gui.setScore(-10);
				policeman.hit();
				policeman.setStatus(StatusPoliceman::NOTGOOD);
			}
		}
	}
}

//_____________________________________________
void Engine2::update()
{
	player.update();
	policeman.update();
	collision();
	gui.update(player.getStatus());
}

void Engine2::draw()
{
	(*MainWindow).clear();
	(*MainWindow).draw(map);
	(*MainWindow).draw(gui);
	(*MainWindow).draw(wareczka);
	(*MainWindow).draw(policeman);
	(*MainWindow).draw(player);
	(*MainWindow).display();
}

void Engine2::run()
{
	while (State != StatusGame2::END2)
	{
		switch (State)
		{
		case StatusGame2::RUN:
			game();
			break;
		case StatusGame2::GAME_OVER:
			end(0);
			break;
		case StatusGame2::END_GAME2:
			end(1);
			break;
		}
	}
}

void Engine2::game()
{
	bool menu = false;

	//GAME
	//________________________________________________________________________________
	while (!menu && player.getStatus() == StatusCar::ALIVE)
	{
		//check if exit
		sf::Event event;
		while ((*MainWindow).pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
			{
				menu = true;
				State = StatusGame2::END2;
			}
		}

		//events for player
		//if time gone
		if (gui.getTime() <= 0)
		{
			State = StatusGame2::GAME_OVER;
			gui.resetScore();
			menu = true;
		}
		//if go outside
		if (isEscape())
		{
			player.setStatus(StatusCar::LEFT);
			State = StatusGame2::END_GAME2;
			menu = true;
		}


		//player - moving
		if (player.getStatus() != DEAD)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					player.rotate_wheel(-1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					player.rotate_wheel(1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player.accelerate();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player.minusaccelerate();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				player.handbreak();
			}
		}

		update();
		draw();
	}//______________________________________________________________________________
	
}

void Engine2::end(bool win)
{
	std::string result;
	result = win ? ("Congratulations! Value of your Wareczkas: " + std::to_string(gui.getScore())) : "Oh no! Time is up, you broke your car or smtg worse... All your Wareczkas disappered";

	MessageBox(NULL, result.c_str(), "Information", MB_ICONINFORMATION);
	State = StatusGame2::END2;
}

bool Engine2::isEscape()
{
	if ((player.getPosition(0).x > 590 && player.getPosition(0).x < 690 - 30) || (player.getPosition(1).x > 590 && player.getPosition(1).x < 690 - 30) || (player.getPosition(2).x > 590 && player.getPosition(2).x < 690 - 30) || (player.getPosition(3).x > 590 && player.getPosition(3).x < 690 - 30))
		if (player.getPosition(0).y < 5 || player.getPosition(1).y < 5 || player.getPosition(2).y < 5 || player.getPosition(3).y < 5)
			return true;
	return false;
}