#pragma once
#include "Node.h"

class NodeComparator
{
public:
	bool operator()(const Node*& a, const Node*& b) { return ((*a).F > (*b).F); }
	//bool operator()(Node* a, Node* b) { return ((*a).F > (*b).F); }
	bool operator()(Node*& a, Node*& b) { return ((*a).F > (*b).F); }
};