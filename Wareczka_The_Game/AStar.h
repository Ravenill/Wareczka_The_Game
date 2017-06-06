#pragma once
#include "Node.h"
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include "Comparator.h"
#include <SFML\Graphics.hpp>

class AStar
{
private:
	//map
	Node **_map;
	int _map_size_x;
	int _map_size_y;

	Node *_start;
	Node *_end;

	bool isIn(Node*, std::priority_queue<Node*, std::vector<Node*>, NodeComparator>);
	bool isIn(Node*, std::vector<Node*>);
	void calculate(Node&, int, int);
	int calculateG(Node, int, int);
	void calculateF(Node&);
	void findPath();
	void reset();

public:
	AStar(std::string);
	~AStar();

	void printMap();
	void printPath();
	void runPathFinder(int x_start, int y_start, int dest_x, int dest_y);

	int getBoundsX() { return _map_size_x; }
	int getBoundsY() { return _map_size_y; }
	sf::Vector2f getPointPosition(int x, int y) { return sf::Vector2f(_map[x][y].x_cord, _map[x][y].y_cord); }
	void getPath(std::stack<sf::Vector2f>&);
};