#include "Output.h"
#include "Utility.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


// No more need for that

void printHosts(ostream &log, ListOfHosts& listHosts)
// In this function we are printing the informations we have on each host
// That we gathered from the nmap output file 
{
	ofstream dataFile("Data File.txt"); // should put an append+ flag here
	if (!dataFile.is_open())
	{
		log << "Data File could not be created" << endl;
		return;
	}
	else
		log << "Data File has been created to print the process' results" << endl;

	for (int i = 0; i < listHosts.nbHosts; i++)
	{
		Host* currHost = listHosts.element[i];
		dataFile << currHost->ip << " ";
		string last4 = currHost->ip.substr(currHost->ip.rfind("."));
		switch (last4.length())
		{
		case 4: {
			cout << " ";
			break; }
		case 3: {
			cout << "  ";
			break; }
		case 2: {
			cout << "   ";
			break; }
		default:
			break;
		}
		dataFile << currHost->macAdress << " " << setprecision(6) << currHost->latency << " " << currHost->status << endl;
		for (int j = 0; j < currHost->ports.nbPorts; j++)
		{
			Port* currPort = currHost->ports.element[j];
			dataFile << "      " << currPort->p_number << "/" << currPort->p_state << "," << currPort->p_protocol << ":" << currPort->p_service << endl;
		}
		dataFile << "---------------------------------------------------------------------------------------------------------" <<endl;
	}
	log << "Processed Data has been printed in Data File" << endl;
}
