#pragma once
#include <cmath>

enum CanGo { DONT, CAN };

struct Node
{
public:
	CanGo can_go;
	int cost; //cost of movement
	int x, y;
	int x_cord, y_cord;
	
	float H; //heuristic
	float G; //culminated distance

	float F; //G+H -> define next elem -> priority

	Node *parent;

	//____________________________________________________________________________

	Node();
};