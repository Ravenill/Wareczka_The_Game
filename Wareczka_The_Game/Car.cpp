#include "Car.h"
#include <cmath>
#include <iostream>
#include <Windows.h>
#define M_PI 3.14159265358979323846

//Car Paramaters
#define DRIFTO 2.5f
#define POSX 640.0f //x pos
#define POSY 220.0f //y pos
#define ANGLE 180
#define XBLOCK 30.0f
#define YBLOCK 30.0f

//Wheel Paramteres
#define XWHEEL 5.0f
#define YWHEEL 10.0f
#define AMOUNT_OF_PARTICLES 1000


Car::Car()
{
	//TICK for time
	sf::Clock clock;
	sf::Time time1, time2;
	time1 = clock.getElapsedTime();

	for (int i = 0; i < 2; i++)
	{
		//shape
		shape[i].setPointCount(4);

		shape[i].setPoint(0, sf::Vector2f(0, 0));
		shape[i].setPoint(1, sf::Vector2f(XBLOCK, 0));
		shape[i].setPoint(2, sf::Vector2f(XBLOCK, YBLOCK));
		shape[i].setPoint(3, sf::Vector2f(0, YBLOCK));

		shape[i].setOrigin((XBLOCK / 2), (YBLOCK / 2));
		shape[i].setPosition(POSX, i == 0 ? POSY : (POSY + YBLOCK));
		shape[i].setRotation(ANGLE);
	}

	//position of wheels
	sf::Vector2f pos[4] = { {(POSX - (XBLOCK / 2) + (XWHEEL / 2) - 2), POSY},
							{(POSX + (XBLOCK / 2) - (XWHEEL / 2) + 2), POSY},
							{(POSX - (XBLOCK / 2) + (XWHEEL / 2) - 2), (POSY + YBLOCK)},
							{(POSX + (XBLOCK / 2) - (XWHEEL / 2) + 2), (POSY + YBLOCK)} };

	//setting position
	for (int i = 0; i < 4; i++)
	{
		wheel[i].setPointCount(4);

		wheel[i].setPoint(0, sf::Vector2f(0, 0));
		wheel[i].setPoint(1, sf::Vector2f(XWHEEL, 0));
		wheel[i].setPoint(2, sf::Vector2f(XWHEEL, YWHEEL));
		wheel[i].setPoint(3, sf::Vector2f(0, YWHEEL));

		wheel[i].setOrigin((XWHEEL / 2), (YWHEEL / 2));
		wheel[i].setPosition(pos[i]);
		wheel[i].setFillColor(sf::Color::Black);
	}

	speed = 0;
	wheel_rad = 0;
	speed_rad = 0;
	status = ALIVE;

	vx = 0;
	vy = 0;

	//loading textures
	if (!front.loadFromFile("data/graphics/Skoda/Skoda1.png") || !rear.loadFromFile("data/graphics/Skoda/Skoda2.png"))
	{
		MessageBox(NULL, "Error! Textures not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}
	shape[0].setTexture(&front);
	shape[1].setTexture(&rear);

	//TICK for time (continued)
	time2 = clock.getElapsedTime();
	time2 = time2 - time1;
	time = 1;//floor(time2.asMilliseconds());//shitfloor
}

Car::~Car()
{
	int size = track.size();
	for (int i = 0; i < size; i++)
	{
		sf::ConvexShape* temp = track.front();
		track.pop_front();
		delete temp;
	}
}

sf::Vector2f Car::getPosition(size_t index)
{
	if(static_cast<int>(index) < 2)
		return shape[0].getTransform().transformPoint(shape[0].getPoint(index));
	else
		return shape[1].getTransform().transformPoint(shape[1].getPoint(index));
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto i : track) target.draw(*i);
	for (int i = 0; i < 4; i++) target.draw(wheel[i]);
	for (int i = 0; i < 2; i++) target.draw(shape[i]);
}

void Car::follow()
{
	shape[1].setPosition(shape[0].getPosition().x - static_cast<float>((sin(M_PI * (shape[0].getRotation() / 180)) * XBLOCK)), shape[0].getPosition().y + static_cast<float>((cos(M_PI * (shape[0].getRotation() / 180)) * XBLOCK)));
	shape[1].setRotation(shape[0].getRotation());

	for (int i = 0; i < 4;  i = i + 2)
	{
		wheel[i].setPosition(shape[i < 2 ? 0 : 1].getPosition().x - static_cast<float>((cos(M_PI * (shape[0].getRotation() / 180)) * (XBLOCK / 2 - XWHEEL / 2 + 2))), shape[i < 2 ? 0 : 1].getPosition().y - static_cast<float>((sin(M_PI * ((shape[0].getRotation() - speed / 2) / 180)) * (XBLOCK / 2 - XWHEEL / 2 + 2))));
		wheel[i].setRotation(shape[0].getRotation() + (i < 2 ? wheel_rad : 0));
	}
	
	for (int i = 1; i < 4; i = i + 2)
	{
		wheel[i].setPosition(shape[i < 2 ? 0 : 1].getPosition().x + static_cast<float>((cos(M_PI * (shape[0].getRotation() / 180)) * (XBLOCK / 2 - XWHEEL / 2 + 2))), shape[i < 2 ? 0 : 1].getPosition().y + static_cast<float>((sin(M_PI * ((shape[0].getRotation() - speed/2) / 180)) * (XBLOCK / 2 - XWHEEL / 2 + 2))));
		wheel[i].setRotation(shape[0].getRotation() + (i < 2 ? wheel_rad : 0));
	}
	
}

void Car::strighten()
{
	if (((!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))) && speed != 0)
	{
		if (wheel_rad != 0 && speed > 0)
		{
			if (wheel_rad < 0)
				wheel_rad += 0.2f*speed;
			else
				wheel_rad -= 0.2f*speed;
		}

		if (wheel_rad != 0 && speed < 0)
		{
			if (wheel_rad < 0)
				wheel_rad -= 0.2f * speed;
			else
				wheel_rad += 0.2f * speed;
		}
	}
}

void Car::rotate()
{
	if (!(wheel[0].getRotation() == shape[0].getRotation()) && speed != 0)
	{
		if (wheel_rad < 0)
			shape[0].rotate(0.02f * wheel_rad * speed);
		else if (wheel_rad > 0)
			shape[0].rotate(0.02f * wheel_rad * speed);
	}
}

void Car::drifting()
{
	int angle = 0;
	
	if (speed_rad < 0)
		angle = -75;
	else if (speed_rad > 0)
		angle = 75;

	float rotary = shape[1].getRotation();
	float xN = static_cast<float>(sin(M_PI * ((rotary + angle) / 180)));
	float yN = static_cast<float>(cos(M_PI * ((rotary + angle) / 180)));
	shape[1].move(xN*abs(speed_rad/2), -yN*abs(speed_rad/2));

	if (speed_rad > 0.01)
		shape[1].rotate(-0.3f + (wheel_rad / 80) - (((rand() % (4 + (static_cast<int>(speed)/6))) + 1) / 10));
	else if (speed_rad < -0.01)
		shape[1].rotate(0.3f + (wheel_rad / 80) + (((rand() % (4 + (static_cast<int>(speed)/6))) + 1) / 10));

	shape[0].setPosition(shape[1].getPosition().x + static_cast<float>((sin(M_PI * (shape[1].getRotation() / 180)) * 30)), shape[1].getPosition().y - static_cast<float>((cos(M_PI * (shape[0].getRotation() / 180)) * 30)));
	shape[0].setRotation(shape[1].getRotation());
}

void Car::update()
{
	if (status == StatusCar::ALIVE)
	{
		rotate();
		strighten();

		//debug
		//system("CLS");
		std::cout << shape[0].getPosition().x << ", " << shape[0].getPosition().y << "\n" << shape[0].getRotation() << "\n" << wheel_rad << "\n" << wheel[0].getPosition().x << ", " << wheel[0].getPosition().y << "   " << wheel[1].getPosition().x << ", " << wheel[1].getPosition().y << "   " << wheel[2].getPosition().x << "," << wheel[2].getPosition().y << "   " << wheel[3].getPosition().x << ", " << wheel[3].getPosition().y << "\n" << wheel[0].getRotation() << "\t" << speed << "\n" << speed_rad << "\n" << '\n';;

		//moving x, y
		float angle = shape[0].getRotation();
		float xN = static_cast<float>(sin(M_PI * ((angle + wheel_rad) / 180)));
		float yN = static_cast<float>(cos(M_PI * ((angle + wheel_rad) / 180)));

		vx = xN * speed * time;
		vy = yN * speed * time;

		deaccelerate();

		//moving command
		shape[0].move(vx, -vy);
		follow();

		//drifting
		drifting();
		follow();
	}
}

void Car::playAnimation(bool play)
{

}

void Car::handbreak()
{
	if (speed > 0.25)
	{
		speed = speed - 0.08f;
		createWheelTrack();
	}
	else if (speed < -0.25)
		speed = speed + 0.08f;
	
	if (DRIFTO > abs(speed_rad) && speed > 0.5)
	{
		if (wheel_rad < 0)
			speed_rad = speed_rad + 0.1f;
		else if (wheel_rad > 0)
			speed_rad = speed_rad - 0.1f;
	}

}

void Car::deaccelerate()
{
	if (speed > 0)
		speed = speed - 0.01f;
	if (speed < 0)
		speed = speed + 0.01f;
	if (speed < 0.001 && speed > -0.001)
		speed = 0;

	if (speed_rad > 0.01)
		speed_rad = speed_rad - 0.03f;
	if (speed_rad < -0.01)
		speed_rad = speed_rad + 0.03f;

	if (speed_rad < 0.02 && speed_rad > -0.02)
		speed_rad = 0;
}

void Car::minusaccelerate()
{
	if (speed >= -1.5 && abs(speed_rad) < (DRIFTO - 0.2))
		speed = speed - 0.05f;
}

void Car::accelerate()
{
	if(speed <= max_speed && abs(speed_rad) < (DRIFTO - 0.2))
		speed = speed + 0.05f;
}

void Car::rotate_wheel(int angle)
{
	int resist;

	resist = static_cast<int>(0.23*pow(speed, 3) - 2.07*pow(speed, 2) - 1.15*(speed) + 40);
	if (speed > (max_speed - 1))
		resist = 8;
	if (speed <= 0)
		resist = 40;

	wheel_rad += angle;
	if (!(wheel_rad <= resist && wheel_rad >= -resist))
	{
		wheel_rad -= angle*2;
	}
}

void Car::createWheelTrack()
{
	sf::ConvexShape *wheel_temp1 = new sf::ConvexShape;
	sf::ConvexShape *wheel_temp2 = new sf::ConvexShape;
	addWheelTrack(wheel_temp1, wheel_temp2);

	if (track.size() > AMOUNT_OF_PARTICLES)
	{
		for (int i = 0; i < 2; i++)
		{
			sf::ConvexShape *temp2 = track.front();
			track.pop_front();
			delete temp2;
		}
	}
}

void Car::addWheelTrack(sf::ConvexShape *mark1, sf::ConvexShape *mark2)
{
	//left wheel
	mark1->setPointCount(4);
	
	mark1->setPoint(0, sf::Vector2f(0, 0));
	mark1->setPoint(1, sf::Vector2f(XWHEEL, 0));
	mark1->setPoint(2, sf::Vector2f(XWHEEL, YWHEEL));
	mark1->setPoint(3, sf::Vector2f(0, YWHEEL));

	mark1->setOrigin((XWHEEL / 2), (YWHEEL / 2));
	mark1->setFillColor(sf::Color(0,0,0,50));

	mark1->setPosition(wheel[2].getPosition());
	mark1->setRotation(wheel[2].getRotation());

	//right wheel
	mark2->setPointCount(4);

	mark2->setPoint(0, sf::Vector2f(0, 0));
	mark2->setPoint(1, sf::Vector2f(XWHEEL, 0));
	mark2->setPoint(2, sf::Vector2f(XWHEEL, YWHEEL));
	mark2->setPoint(3, sf::Vector2f(0, YWHEEL));

	mark2->setOrigin((XWHEEL / 2), (YWHEEL / 2));
	mark2->setFillColor(sf::Color(0, 0, 0, 50));

	mark2->setPosition(wheel[3].getPosition());
	mark2->setRotation(wheel[3].getRotation());

	track.push_back(mark1);
	track.push_back(mark2);
}