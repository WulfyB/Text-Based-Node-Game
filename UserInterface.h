//The UserInterface header file is the main body of the program.
//It executes the while loops to take in and execute user choices.
//Additionally, the interface follows the user down pointers using the loc node as a tracker.

#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "System.h"
#include "Node.h"
using namespace std;
class UserInterface {
private:
	string choice; //String of available directions player can walk
	string temp; //holds temporary values
	char walk; //Char of the user chosen direction
	bool end = false; //verifies maze is not completed
	System system; //instance of system
	Node node; //instance of node
	Node loc; //follows points to current location of player

public:
	int mazeStart()
	{
		while (temp.empty()) {
			cout << "Please enter the file name of the txt file you wish to use as your maze.\n";
			temp.clear();
			while (temp.empty())
			{
				getline(cin, temp);
			}
			bool x = system.graphReader(temp); //returns true if file is valid.
			if (!x)
			{
				return 0;
			}
		}
		Node *tmpPtr; //temp pointer acts as pointer to player
		tmpPtr = system.startNode();
		loc = tmpPtr[0];
		cout << "You are in " + loc.getNodeName()
			<< ". \n";
		while (!end)
		{
			moveOps(loc);
			choice = "You can go in the following directions. \n" + moveOps(loc);
			cout << choice
				<< "What direction would you like to go?\n";
			temp.clear();
			while (temp.empty())
			{
				getline(cin, temp);
			}
			walk = temp.at(0);
			walk = tolower(walk);

			switch (walk)
			{
			case 'n': //walk north
				tmpPtr = loc.getAttachedNode(0);
				if ((loc.getAttachedNode(0) == nullptr))
				{
					cout << "That direction is invalid. Please try again.\n";
					break;
				}
				loc = tmpPtr[0];
				temp = loc.getNodeName();
				cout << "Heading North, you have entered " + temp + "\n";
				system.addToHistory(temp);
				if (temp == system.getTarget())
				{
					end = true;
				}
				tmpPtr = loc.getSnakeLadderNode();
				if (tmpPtr != nullptr)
				{
					cout << "Oh no! This room is trapped! \n";
					loc = tmpPtr[0];
					temp = loc.getNodeName();
					system.addToHistory(temp);
					cout << "The trap resulted you in ending up in " + temp + ".\n";
				}
				break;
			case 'e': //walk east
				tmpPtr = loc.getAttachedNode(1);
				if ((loc.getAttachedNode(1) == nullptr))
				{
					cout << "That direction is invalid. Please try again.\n";
					break;
				}
				loc = tmpPtr[0];
				temp = loc.getNodeName();
				cout << "Heading East, you have entered " + temp + "\n";
				system.addToHistory(temp);
				if (temp == system.getTarget())
				{
					end = true;
				}
				tmpPtr = loc.getSnakeLadderNode();
				if (tmpPtr != nullptr)
				{
					cout << "Oh no! This room is trapped! \n";
					loc = tmpPtr[0];
					temp = loc.getNodeName();
					system.addToHistory(temp);
					cout << "The trap resulted you in ending up in " + temp + ".\n";
				}
				break;
			case 's': //walk south
				tmpPtr = loc.getAttachedNode(2);
				if ((loc.getAttachedNode(2) == nullptr))
				{
					cout << "That direction is invalid. Please try again.\n";
					break;
				}
				loc = tmpPtr[0];
				temp = loc.getNodeName();
				cout << "Heading South, you have entered " + temp + "\n";
				system.addToHistory(temp);
				if (temp == system.getTarget())
				{
					end = true;
				}
				tmpPtr = loc.getSnakeLadderNode();
				if (tmpPtr != nullptr)
				{
					cout << "Oh no! This room is trapped! \n";
					loc = tmpPtr[0];
					temp = loc.getNodeName();
					system.addToHistory(temp);
					cout << "The trap resulted you in ending up in " + temp + ".\n";
				}
				break;
			case 'w': //walk west
				tmpPtr = loc.getAttachedNode(3);
				if ((loc.getAttachedNode(3) == nullptr))
				{
					cout << "That direction is invalid. Please try again.\n";
					break;
				}
				loc = tmpPtr[0];
				temp = loc.getNodeName();
				cout << "Heading west, you have entered " + temp + "\n";
				system.addToHistory(temp);
				if (temp == system.getTarget())
				{
					end = true;
				}
				tmpPtr = loc.getSnakeLadderNode();
				if (tmpPtr != nullptr)
				{
					cout << "Oh no! This room is trapped! \n";
					loc = tmpPtr[0];
					temp = loc.getNodeName();
					system.addToHistory(temp);
					cout << "The trap resulted you in ending up in " + temp + ".";
				}
				break;
			case 'q': //quits the program when a user gives up or has no options.
				cout << "You have failed to complete the maze or deemed it unsolvable. Exiting the program.\n";
				end = true;
				break;
			default: //informs user of invalid input.
				cout << walk
					<< " is not a valid direction. Please consider choices and choose again.\n";
				break;
			}
		}
		if (walk != 'q')
		{
			cout << "Congratulations!You have reached the destination point.\n"
				<< "You took "
				<< system.getSteps()
				<< " steps.\n You visited the nodes: "
				<< system.visitedRooms();
		}

		return 1;
	}
	string moveOps(Node tLoc) //determines the list of available options
	{
		string options;
		if (!(tLoc.getAttachedNode(0) == nullptr))
		{
			options += "North\n";
		}
		if (!(tLoc.getAttachedNode(1) == nullptr))
		{
			options += "East\n";
		}
		if (!(tLoc.getAttachedNode(2) == nullptr))
		{
			options += "South\n";
		}
		if (!(tLoc.getAttachedNode(3) == nullptr))
		{
			options += "West\n";
		}
		if (options.empty())
		{
			options = "There is no legal move. Please input q to quit.\n"; //for when you're out of options
		}
		return options;
	}
};