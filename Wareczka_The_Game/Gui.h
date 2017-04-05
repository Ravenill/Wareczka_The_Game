#pragma once

class Gui
{
private:
	int score;
	int maxScore;
	bool isDead;

public:
	void display();
	void setscore(int a) { score = a; };
	void update();
};