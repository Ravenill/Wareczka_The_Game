#include "AStar.h"
#include <fstream>
#include <Windows.h>
#include <iostream>

#define RESX 1280
#define RESY 720
#define WALL 30

AStar::AStar(std::string path)
{
	int xsize, ysize;
	
	std::fstream file;
	file.open(path.c_str());

	if (!file.is_open())
	{
		MessageBox(NULL, "Error! Navmesh not found. Please, reinstal the game.", ERROR, NULL);
		return;
	}

	//loading map size
	file >> _map_size_x;
	file >> _map_size_y;

	xsize = (RESX - (2 * WALL)) / _map_size_x;
	ysize = (RESY - (2 * WALL)) / _map_size_y;

	_map = new Node*[_map_size_x];
	for (int i = 0; i < _map_size_x; i++)
		_map[i] = new Node[_map_size_y];

	for (int j = 0; j < _map_size_y; j++)
		for (int i = 0; i < _map_size_x; i++)
		{
			int temp;
			file >> temp;
			if (temp == 0)
				_map[i][j].can_go = CanGo::DONT;
			else
				_map[i][j].cost = temp;

			_map[i][j].x = i;
			_map[i][j].y = j;

			_map[i][j].x_cord = WALL + (xsize * (i+1));
			_map[i][j].y_cord = WALL + (ysize * (j+1));
		}

	_start = nullptr;
	_end = nullptr;
}

AStar::~AStar()
{
	for (int i = 0; i < _map_size_x; i++)
		delete[] _map[i];
	delete[] _map;
}

bool AStar::isIn(Node* elem, std::priority_queue<Node*, std::vector<Node*>, NodeComparator> tab)
{
	Node* temp;

	int sizetab = tab.size();
	for (unsigned int i = 0; i < sizetab; i++)
	{
		temp = tab.top();
		tab.pop();

		if (temp == elem)
			return true;
	}
	return false;
}

bool AStar::isIn(Node* elem, std::vector<Node*> tab)
{
	for (auto x : tab)
		if (x == elem)
			return true;

	return false;
}

void AStar::calculate(Node& elem, int x, int y)
{
	//counting H
	for (int i = elem.x; i != (*_end).x; ((elem.x < (*_end).x) ? i++ : i--))
		elem.H = elem.H + 10 + _map[i][elem.y].cost;
	for (int i = elem.y; i != (*_end).y; ((elem.y < (*_end).y) ? i++ : i--))
		elem.H = elem.H + 10 +_map[(*_end).x][i].cost;

	//counting G
	for (Node* a = &elem; a != nullptr; a = (*a).parent)
	{
		if ((*a).parent == nullptr) break;
		if (((*a).x - ((*(*a).parent).x) == -1) || ((*a).x - ((*(*a).parent).x) == 1))
		{
			if (((*a).y - ((*(*a).parent).y) == -1) || ((*a).y - ((*(*a).parent).y) == 1))
			{
					elem.G = elem.G + (*a).cost + 14;
					continue;
			}
			else;
		}
		elem.G = elem.G + (*a).cost + 10;
	}
	
	//counting F
	elem.F = elem.G + elem.H;
}

int AStar::calculateG(Node elem, int x, int y)
{
	//counting G
	for (Node* a = &elem; a != nullptr; a = (*a).parent)
	{
		if ((*a).parent == nullptr) break;
		if (((*a).x - ((*(*a).parent).x) == -1) || ((*a).x - ((*(*a).parent).x) == 1))
		{
			if (((*a).y - ((*(*a).parent).y) == -1) || ((*a).y - ((*(*a).parent).y) == 1))
			{
				elem.G = elem.G + (*a).cost + 14;
				continue;
			}
			else;
		}
		elem.G = elem.G + (*a).cost + 10;
	}
	return elem.G;
}

void AStar::calculateF(Node & elem)
{
	//counting H
	for (int i = elem.x; i != (*_end).x; ((elem.x < (*_end).x) ? i++ : i--))
		elem.H = 10 + _map[i][elem.y].cost;
	for (int i = elem.y; i != (*_end).y; ((elem.y < (*_end).y) ? i++ : i--))
		elem.H = 10 + _map[(*_end).x][i].cost;
}

void AStar::printMap()
{
	for (int j = 0; j < _map_size_y; j++)
	{
		for (int i = 0; i < _map_size_x; i++)
			std::cout << _map[i][j].can_go << ":" << _map[i][j].H << ":" << _map[i][j].G << ":" << _map[i][j].F << " ";
		std::cout << "\n";
	}

	//DEBUG
	/*
	std::cout << "\n";
	for (int j = 0; j < _map_size_y; j++)
	{
		for (int i = 0; i < _map_size_x; i++)
			std::cout << _map[i][j].x << "," << _map[i][j].y << " ";
		std::cout << "\n";
	}
	*/
}

void AStar::printPath()
{
	Node* temp = _end;

	for (; temp != nullptr; temp = (*temp).parent)
		std::cout << (*temp).x << "," << (*temp).y << "  ";
}

void AStar::runPathFinder(int x_start, int y_start, int dest_x, int dest_y)
{
	if (dest_x > _map_size_x || dest_x < 0)
		return;
	if (dest_y > _map_size_y || dest_y < 0)
		return;
	if (x_start > _map_size_x || x_start < 0)
		return;
	if (y_start > _map_size_y || y_start < 0)
		return;
	
	_start = &_map[x_start][y_start];
	_end = &_map[dest_x][dest_y];

	findPath();
}

void AStar::findPath()
{
	std::vector<Node*> CL;
	std::priority_queue<Node*, std::vector<Node*>, NodeComparator> OL;
	Node* current;

	reset();

	OL.push(_start);

	while (!OL.empty())
	{
		current = OL.top();
		OL.pop();
		CL.push_back(current);

		if (current == _end)//end with path
		{
			return;
		}

		//for every 8(9) node around
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)//if not neighbour - miss
					continue;
				//if out of range - miss
				if ((*current).x + x < 0 || (*current).x + x > _map_size_x - 1)
					continue;
				if ((*current).y + y < 0 || (*current).y + y > _map_size_y - 1)
					continue;

				//taking node[x][y] from map
				Node* temp = &_map[((*current).x) + x][((*current).y) + y];

				//if is in CL or can't go
				if ((*temp).can_go == CanGo::DONT || isIn(temp, CL)) continue;
				//else if isn't in OL
				else if (!isIn(temp, OL))
				{
					(*temp).parent = current;
					calculate(*temp, x, y);
					OL.push(temp);
				}
				//in other case
				else
				{
					int new_G = calculateG(*temp, x, y);
					if (new_G < (*temp).G)
					{
						(*temp).parent = current;
						(*temp).G = new_G;
						calculateF(*temp);
					}
				}
			}
		}//end of for-node
		//DEBUG
		//std::cout << (*current).x << ", " << (*current).y << ":" << (*current).H << ":" << (*current).G << ":" << (*current).F << "     " << (*current).can_go << "\n";
	}
}

void AStar::reset()
{
	for (int j = 0; j < _map_size_y; j++)
		for (int i = 0; i < _map_size_x; i++)
		{
			_map[i][j].F = 0;
			_map[i][j].G = 0;
			_map[i][j].H = 0;
			_map[i][j].parent = nullptr;
		}
}

void AStar::getPath(std::stack<sf::Vector2f>& path)
{
	for (Node* temp = _end; temp != nullptr; temp = (*temp).parent)
		path.push(sf::Vector2f((*temp).x_cord, (*temp).y_cord));
}
