#pragma once

#pragma region "Inclusions" //{
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#pragma endregion //}

#pragma region "Déclarations" //{


#pragma region "Structures" //{

struct Port 
{	
	string p_number;
	string p_protocol;
	string p_state;
	string p_service;
};

struct ListOfPorts
{
	int nbPorts;
	int capacity;
	Port** element;
};

struct Host
{
	string ip;
	int status;
	float latency;
	string macAdress;
	ListOfPorts ports;
};

struct ListOfHosts 
{
	int nbHosts;
	int capacity;
	Host** element;
};


#pragma endregion //}

#pragma region "Globaux" //{

void deleteFile(ostream &log, const string& toDelete);
void reAllocListOfHosts(ListOfHosts& listRealloc);
void reAllocListOfPorts(ListOfPorts& listRealloc);

#pragma endregion //}

#pragma endregion //}