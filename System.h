//The system header file was originally meant to be the graph reader and roomHistory storage
//After tinkering, the job of the maze became so diminished that it was superfluous
//rather than move and rename everything, the maze fused with System.
//As such, the System crafts the graph using a dynamic array
//and the nodes from the node class. This class does most of the 
//back end work upon which the UI relies.
#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "Node.h"
using namespace std;

class System
{
private:
	string roomHistory; //trace of the rooms visited, in order.
	Node *ndPtr; //pointer for dynamic array
	int arrSize; //stores array size
	string start; //initial node
	string target; //destinitation node
	size_t steps; //number of steps taken to reach destination
public:
	bool graphReader(string FileName)
	{
		string temp; //holds temp string value
		string name; //holds name of node
		FileName = FileName + ".txt";
		ifstream ifs(FileName, ifstream::in); //input file of maze
		int count = -1;
		while (getline(ifs, temp))
		{
			if (count == -1) //crafts the list of nodes that exist
			{
				arrSize = stoi(temp);
				ndPtr = new Node[arrSize]; //sets i[ pir pomter
				getline(ifs, temp);
				start = temp.substr(0, 2);
				getline(ifs, temp);
				target = temp.substr(0, 2);
				count++;
				continue;
			}
			name = temp.substr(0, 2);
			ndPtr[count] = Node(name);
			count++;
		}
		if (count == -1) //If no file is input, count at -1 will catch and return its failure
		{
			cout << "The file could not be found. Exiting program.";
			return false;
		}
		ifstream ifs2(FileName, ifstream::in); //second io stream will attach nodes to ndPtr[]
		count = -3; //made a lower number to account for unneeded lines
		while (getline(ifs2, temp))
		{
			if (count < 0) //removes unneeded lines for this while loop.
			{
				count++;
				continue;
			}
			for (int i = 0; i < 6; i++) //assigns attached nodes to current node
			{
				if (i == 0)
				{
					temp = temp.substr(3);
					continue;
				}
				if (i == 5)
				{
					if (temp.at(0) != '*')
					{
						name = temp;
						Node *tmpPtr = std::find_if(ndPtr, ndPtr + arrSize, [&name](Node& n) { return n.getNodeName() == name; });
						if (tmpPtr == ndPtr + arrSize)
						{
							cout << "The maze input is invalid. Please try again.";
							return false; //if invalid node is attached, kicks back to user and exits program.
						}
						ndPtr[count].attachSnakeLadderNode(tmpPtr);
					}
					break;
				}
				if (temp.at(0) == '*')
				{
					temp = temp.substr(2);
					continue;
				}
				
				name = temp.substr(0, 2);
				temp = temp.substr(3);
				Node *tmpPtr = std::find_if(ndPtr, ndPtr + arrSize, [&name](Node& n) { return n.getNodeName() == name; });
				if (tmpPtr == ndPtr + arrSize)
				{
					cout << "The maze input is invalid. Please try again.";
					return false;  //if invalid node is attached, kicks back to user and exits program.
				}
				ndPtr[count].attachNewNode(tmpPtr, i-1);
				
			}
			count++;
		}
		return true;
	}
	string getStart() //gets startname
	{
		return start;
	}
	Node* startNode() const //returns constant point to startNode()
	{
		return &ndPtr[0];
	}

	string getTarget() //name of Target node
	{
		return target;
	}
	string visitedRooms() //returns roomHistory
	{
		return roomHistory;
	}
	void addToHistory(string temp) //adds to roomHistory
	{
		steps += 1;
		roomHistory += temp + " ";
	}
	size_t getSteps() //returns number of steps taken (ie, rooms visited)
	{
		return steps;
	}
};