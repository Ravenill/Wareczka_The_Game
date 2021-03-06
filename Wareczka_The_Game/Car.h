#pragma once
#include <SFML\Graphics.hpp>
#include "States.h"
#include <deque>


class Car : public sf::Drawable, sf::Transformable
{
private:
	//main
	sf::Texture front;
	sf::Texture rear;
	sf::ConvexShape shape[2];
	sf::ConvexShape wheel[4];
	StatusCar status;
	std::deque<sf::ConvexShape*> track;

	//parameters
	unsigned static const int max_speed = 7;
	float wheel_rad;
	float speed;
	float speed_rad;
	float time;

	float vx;
	float vy;

	//private functions
	void deaccelerate();
	void drifting();
	void follow();
	void strighten();
	void rotate();

	void createWheelTrack();
	void addWheelTrack(sf::ConvexShape *mark1, sf::ConvexShape *mark2);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Car();
	~Car();

	sf::Vector2f getPosition(size_t index);
	StatusCar getStatus() { return status; }
	void setStatus(StatusCar set) { status = set; }

	void update();

	void playAnimation(bool play);
	void accelerate();
	void minusaccelerate();
	void handbreak();
	void rotate_wheel(int angle);
	void setVelocity(float x, float y) { vx = x; vy = y; }
	sf::Vector2f getVelocity() { return sf::Vector2f(vx, vy); }
};