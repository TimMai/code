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

char menu();
void initialize(node *&head, node *&last);
void newNode(node *&head, node *&last, std::string name);
void insert(node *&head, node *&last, std::string name);
void insert2(node *&head, node *&last, std::string name);
void remove(node *&head, node *&last);
void showList(node *current);



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
		case '1': 
			
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

			std::cout << " Program size (KB) - ";
			std::cin >> size;

			if (size > 128)
			{
				std::cout << "Error - not enough memory for Program " << name << std::endl;
				break;
			}

			else 
			{
				for (int i = 0; i < 32; i++)
				{
					size -= 4;
					if (size <= 0)
					{
						pages = i + 1;
						std::cout << "Pages used: " << pages << std::endl;
						break;
					}
				}

				for (int i = 0; i < pages; i++)
					insert2(head, last, name);
				
				break;
			}

		case '2': 
			remove(head, last);
			break;

		case '3': 
			showList(head);
			break;

		}

	} while (choice != '4');		//Exit program if 4 is selected
    return 0;
}

char menu()
{
	char choice;	

	std::cout << "Menu \n";
	std::cout << "1. Add program \n";
	std::cout << "2. Remove an item. \n";
	std::cout << "3. Show the list. \n";
	std::cout << "4. Exit. \n";

	std::cin >> choice;
	return choice;
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
	if (head == NULL)	//If there is no linked list initially, create one
		newNode(head, last, name);

	else				//Else add on to end of the list
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

	if (head == NULL)
		newNode(head, last, name);

	else
	{
		if (head->name == "Free")
		{
			head->name = name;
		}
		else
		{
			//Infinite while loop after creating spot for one program
			while (rerun)
			{
				node *temp = head;
				if (temp->name != "Free")
					temp = temp->next;
				

				else
				{
					//node *temp = new node;
					//temp = head;
					temp->name = name;
					//temp->next = head->next;
					//head->next = temp;
					//head = temp;
					//last = last->next;
					//last = last;
					break;
				}
			}
		}
	}
}

void remove(node *&head, node *&last)
{
	if (head == NULL)
		std::cout << "The list is already empty" << std::endl;

	else if (head == last)
	{
		delete head;
		head = NULL;
		last = NULL;
	}

	else
	{
		node *temp = head;
		head = head->next;
	}
}

void showList(node *current)
{
	//if (current == NULL)
		//std::cout << "The list is empty." << std::endl;

	node *temp = current;
	std::cout << "The list contains: " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (current == NULL)
			{
				break;
				//std::cout << "Free \t";
				//current = current->next
			}
			else
			{
				std::cout << temp->name << "\t";
				temp = temp->next;
			}
		}
		std::cout << std::endl;
	}
}
