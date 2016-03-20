// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

struct node
{
	std::string name;	//Hold the node data (name in this case)
	node * next;
	node * last;
};

//Menu to display choices
int menu();	

//Check to see if user made a valid selection in the menu
int decisionVerification(std::string decision);

//Initialize 32 nodes with "Free" spaces
void initialize(node *&head, node *&last);

//Create a new linked list
void newNode(node *&head, node *&last, std::string name);

//Insert a node at the end of list
void insert(node *&head, node *&last, std::string name);

//Chance the node data (WIP)
void insert2(node *&head, node *&last, std::string name);

//Remove a node at end of list
void remove(node *&head, node *&last);

//Remove node of specified name
void remove2(node *&head, std::string name);

//Checks to see if linked list is empty
bool isEmpty(node *&head);

//Check how many fragments exist
void fragmentation(node *&head);

//Display linked list
void showList(node *current);

//Check if there are duplicates of a program
bool duplicateError(node *&head, std::string name);

//Check if there is enough space
bool spaceError(node *&head, int pages);


int main(int argc, char ** argv)
{
	//Initialize nodes
	node * head = NULL;
	node * last = NULL;

	char choice;			//Hold the user's choice
	std::string name;		//Hold the name of the program
	int size;				//Hold the size of the program
	int pages;				//Hold the number of the pages the program will occupy
	bool rerun = true;		//Initialize boolean for while loops

	
	initialize(head, last);	//Initialize a linked list consisting of 32 nodes with "Free" spaces


	do
	{
		choice = menu();	

		switch (choice)
		{
		case 1: 
			
			std::cout << "Program name - ";
			while (rerun)
			{
				std::cin >> name;
				if (name == "Free")
				{
					std::cout << "Program cannot be called 'Free'. Enter another name." << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
				}
				else
				{
					break;
				}
			}

			std::cout << "Program size (KB) - ";
			std::cin >> size;
			std::cout << std::endl;
			

			if (duplicateError(head, name))
				std::cout << "Error - Program " << name << " already running. \n";

			else
			{
				for (int i = 0; i < 64; i++)
				{
					size -= 4;
					if (size <= 0)
					{
						pages = i + 1;
						if (spaceError(head, pages))
							std::cout << "Error - not enough memory for Program " << name << std::endl;

						break;
					}
				}

				if (!spaceError(head, pages))
				{
					for (int i = 0; i < pages; i++)
						insert2(head, last, name);

					std::cout << "Program " << name << " added successfully: " << pages << " page(s) used. \n";
				}
			}
			
			break;
		

		case 2: 
			std::cout << "Program name - ";
			std::cin >> name;
			remove2(head, name);
			break;

		case 3:
			fragmentation(head);
			break;

		case 4: 
			showList(head);
			break;

		}

	} while (choice != 5);		//Exit program if 4 is selected

    return 0;
}

int menu()
{
	std::string decision;	
	int choice;
	bool rerun = true;

	while (rerun)
	{
		std::cout << std::endl;
		std::cout << "1. Add program \n";
		std::cout << "2. Kill program \n";
		std::cout << "3. Fragmentation \n";
		std::cout << "4. Print memory \n";
		std::cout << "5. Exit \n\n";

		std::cout << "choice - ";
		std::cin >> decision;

		choice = decisionVerification(decision);

		if (choice == 6)
			std::cout << "Invalid selection. Try again. \n";

		else
			return choice;
	}
}

int decisionVerification(std::string decision)
{
	if (decision == "1")
		return 1;

	else if (decision == "2")
		return 2;

	else if (decision == "3")
		return 3;

	else if (decision == "4")
		return 4;

	else if (decision == "5")
		return 5;

	else
		return 6;

}

//Initialize linked list with 32 nodes
void initialize(node *&head, node *&last)		
{

	for (int i = 0; i < 32; i++)
	{
		insert(head, last, "Free");
	}
}

//Create a new node at the end of the linked list
void newNode(node *&head, node *&last, std::string name)
{
	node *temp = new node;	//Create temporary node
	temp->name = name;		//Temp node holds the program name
	temp->next = NULL;		//Temp points to NULL 
	head = temp;			
	last = temp;			//Since there is only one node, the head and last node are the same node
}



void insert(node *&head, node *&last, std::string name)
{
	if (head == NULL)				//If there is no linked list initially, create one
		newNode(head, last, name);

	else							//Else add on to end of the list
	{
		node *temp = new node;		//Create temporary node
		temp->name = name;			//Temp node holds the program name
		temp->next = NULL;			//Temp points to NULL because the new node will be added to the end
		last->next = temp;			
		last = temp;
	}

}

void insert2(node *&head, node *&last, std::string name)
{
	bool rerun = true;

	
	if (head->name == "Free")
	{
		head->name = name;
	}

	else
	{
		node *temp = head;

		while (temp->name != "Free")
			temp = temp->next;

		temp->name = name;

	}

}

void remove(node *&head, node *&last)
{
	if (head == NULL)
		std::cout << "The list is already empty" << std::endl;

	/*else if (head == last)
	{
		delete head;
		head = NULL;
		last = NULL;
	}*/

	else
	{
		node *temp = head;
		temp->name = "Free";
	}
}

void remove2(node *&head, std::string name)
{
	node *temp = head;
	for (int i = 0; i < 64; i++)
	{
		if(temp->name != name)				//If the node does not contain the program
			temp = temp->next;				//Continue onto the next node

		else if(temp->name == name)			//If the node contains the program
			temp->name = "Free";			//Make it free

		if (temp->next == NULL)				//If the loop reaches the end of the linked list
		{
			if (temp->name == name)			//If the last node contains the program
				temp->name = "Free";		//Make last node free

			break;
		}
	}

}

bool isEmpty(node *& head)
{
	node *temp = head;
	int i = 0;

	while (temp->next != NULL)
	{
		if (temp->name == "Free")
			i++;

		temp = temp->next;
	}
	if (temp->next == NULL && temp->name == "Free")
		i++;

	if (i = 32)
		return true;

	else
		return false;

}

void fragmentation(node *& head)
{
	if (isEmpty(head))
		std::cout << "There are zero fragments. \n";

	else
	{
		int i = 0;
		node *temp = head;

		while (temp->next != NULL)
		{
			/*if (temp->name != "Free")
			{
				while (temp->next->name != "Free")
				{
					temp = temp->next;
					//if (temp->name == "Free")
						//i++;
				}
			}

			temp = temp->next;*/
			while (temp->name != "Free")
			{
				temp = temp->next;
			}
		}

		std::cout << "There are " << i << " fragment(s). \n";
	}
}

void showList(node *current)
{
	if (current == NULL)		//Current node is empty, then the list is empty -- but this condition will not be met in this program
		std::cout << "The list is empty." << std::endl;

	node *temp = current;
	std::cout << std::endl;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (current == NULL)
			{
				std::cout << "Free \t";
				//current = current->next
				break;
			}
			else
			{
				std::cout << temp->name << "\t";
				temp = temp->next;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool duplicateError(node *&head, std::string name)
{
	node *temp = head;

	while(temp->next != NULL) 
	{
		if (temp->name == name)
			return true;

		else
			temp = temp->next;

	}

	return false;
}

bool spaceError(node *&head, int pages)
{
	node *temp = head;
	int i = 0;			//Hold the number of free spaces available

	while (temp->next != NULL)
	{
		if (temp->name != "Free")
			temp = temp->next;

		else
		{
			//if (temp->next->next == NULL)	//If node after the next one points to null
				//i++;

			if (i == pages)
				return false;

			i++;

			temp = temp->next;
		}

		if (i == pages)
			return false;
		
	}

	if (temp->next == NULL && temp->name == "Free")		//If position is at the last node and it is free
		i++;

	if (i == pages)
		return false;

	return true;
}
