#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Utility.h"

using namespace std;

void deleteFile(ostream &log, const string& toDelete)
// This function will deletes a file
{
	int returnOfDelete = remove(toDelete.c_str());
	if (returnOfDelete == 0)
		log << toDelete << " has been deleted successfully." << endl;
	else
		log << "Error: Unable to deleted " << toDelete << "." << endl;
}

void reAllocListOfHosts(ListOfHosts& listRealloc)
{
	*listRealloc.element = new Host[listRealloc.capacity * 2];
}

void reAllocListOfPorts(ListOfPorts& listRealloc)
{
	*listRealloc.element = new Port[listRealloc.capacity * 2];
}

void freeAllAllocations(ListOfHosts& list, ostream log)
// This function will free all the dynamicly allocated memory and set all the pointers to nullptr
{
	while (list.nbHosts != 0)
	{
		int i = list.nbHosts - 1;
		while (list.element[i]->ports.nbPorts != 0)
		{
			delete list.element[i]->ports.element[list.element[i]->ports.nbPorts-1];
			list.element[i]->ports.element[list.element[i]->ports.nbPorts-1] = nullptr;
			list.element[i]->ports.nbPorts--;
		}
		delete[] list.element[i]->ports.element;
		list.element[i]->ports.element = nullptr;

		delete list.element[i];
		list.element[i] = nullptr;
	}
	delete[] list.element;
	list.element = nullptr;
	log << "All the memory has been freed" << endl;
}