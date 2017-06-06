#include "Node.h"

Node::Node()
{
	parent = nullptr;

	can_go = CanGo::CAN;
	cost = 0;
	x = 0;
	y = 0;

	x_cord = 0;
	y_cord = 0;

	G = 0;
	H = 0;
	F = 0;
}
