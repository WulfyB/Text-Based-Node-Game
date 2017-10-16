//The Node header file manages the nodes used by the program.
//They store data regarding related nodes and trapped nodes for the graph in the system
//Also used for pointers to follow the user as he travels in the UI.
#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "System.h"
using namespace std;

class Node
{
public:
	Node(string newname)
	{
		setNodeName(newname);
		North = NULL;
		South = NULL;
		East = NULL;
		West = NULL;
		snakeOrLadderNodes = NULL;

	};
	Node()
	{
	};
	void setNodeName(string newname)
	{
		name = newname;
	};
	string getNodeName()
	{
		return name;
	};
	void attachNewNode(Node *newNode, int direction)
	{
		if (direction == 0)
		{
			North = newNode;
		}
		else if (direction == 1)
		{
			East = newNode;
		}
		else if (direction == 2)
		{
			South = newNode;
		}
		else if (direction == 3)
		{
			West = newNode;
		}
	};
	Node *getAttachedNode(int direction)
	{
		if (direction == 0)
		{
			return North;
		}
		else if (direction == 1)
		{
			return East;
		}
		else if (direction == 2)
		{
			return South;
		}
		else
		{
			return West;
		}
		
	};
	void attachSnakeLadderNode(Node *newNode)
	{
		snakeOrLadderNodes = newNode;
	};
	Node *getSnakeLadderNode()
	{
		return snakeOrLadderNodes;
	};
private:

	string name; //name of a node
	Node *North; //pointer to north node
	Node *East; // pointer to east node
	Node *South; //pointer to south node
	Node *West; //pointer to west node
	Node *attachedNodes[4]; //the attached node pointer array
	Node *snakeOrLadderNodes; //pointer to destination from trapped node
};