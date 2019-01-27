#include <iostream>
#include <fstream>
#include <string>
#include "Utility.h"
#include "Output.h"

using namespace std;

void readPorts(istream& fileI, Host* currHost)
/*
	* This function will read a Host's Ports from the DataFile
	* \param 	istream fileI 	==> Input file where older processed data has been saved
				Host*currHost  	==> Pointer to the current Host where to put the retrieved data
	* \return 	void
*/
{
	string line;
	getline(fileI, line);
	while (line[4] != '-')
	{
		if (currHost->ports.nbPorts >= currHost->ports.capacity)
		{
			ListOfPorts listP = { currHost->ports.nbPorts , currHost->ports.capacity * 2 };
			listP.element = new Port*[listP.capacity];
			for (int i = 0; i < listP.nbPorts; i++)
				listP.element[i] = currHost->ports.element[i];
			listP.element[listP.nbPorts] = new Port;
			Port* currPort = listP.element[listP.nbPorts];
			sscanf(line.c_str(), "%s/%s,%s:%s", currPort->p_number, currPort->p_state, currPort->p_protocol, currPort->p_service);
			currHost->ports.nbPorts++;
			currHost->ports = listP;
		}
		else
		{
			currHost->ports.element[currHost->ports.nbPorts] = new Port;
			Port* currPort = currHost->ports.element[currHost->ports.nbPorts];
			sscanf(line.c_str(), "%s/%s,%s:%s", currPort->p_number, currPort->p_state, currPort->p_protocol, currPort->p_service);
			currHost->ports.nbPorts++;
		}
	}
}

void readData(ostream& log, ListOfHosts& list, ifstream& fileI)
/*
	* This function will read older data from a file and add it to a struct
	* \param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
				ListOfHosts  	==> Strinct where to save the data
				ifstream fileI 	==> Input file from where the data will be read
	* \return 	void
*/
{
	while (!ws(fileI).eof())
	{
		if (list.nbHosts <= list.capacity)
		{
			list.element[list.nbHosts] = new Host;
			Host* currHost = list.element[list.nbHosts];
			currHost->ports.element = new Port*[currHost->ports.capacity];

			fileI >> currHost->ip;

			string line;
			fileI >> line;

			if (line.find("0.") != -1)
				currHost->macAdress = line;

			fileI >> currHost->latency;

			fileI >> currHost->status;

			readPorts(fileI, currHost);

			list.nbHosts++;
		}
		else
		{
			ListOfHosts list2 = { list.nbHosts, list.capacity * 2 };
			for (int i = 0; i < list2.nbHosts; i++)
				list2.element[i] = list.element[i];

			list2.element[list2.nbHosts] = new Host;
			Host* currHost = list2.element[list2.nbHosts];
			currHost->ports.element = new Port*[currHost->ports.capacity];

			fileI >> currHost->ip;

			string line;
			fileI >> line;

			if (line.find("0.") != -1)
				currHost->macAdress = line;

			fileI >> currHost->latency;

			fileI >> currHost->status;

			readPorts(fileI, currHost);

			list.nbHosts++;

			list = { list2.nbHosts, list2.capacity, list2.element };
		}
	}
}

void printDateTime(ostream& result, ostream& log)
/*
	* This function will get current time on machine and print it on the result file 
	* \param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
				ostream result  ==> Result file where the result will be printed
	* \return 	void
*/
{
	time_t tt;
	struct tm * ti;
	time(&tt);
	ti = localtime(&tt);
	string month[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	result << ti->tm_mday << " " << month[ti->tm_mon] << " " << ti->tm_year + 1900 << " " << ti->tm_hour << ":" << ti->tm_min << endl;
}

void comparingData(ofstream& log, ListOfHosts& listHosts)
/*
	* This function will compare old data to new data
	* \param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
				ListOfHosts   	==> Struct where new data has been saved to be compared
	* \return 	void
*/
{
	log << "Comparing Data from the new Nmap Data and the old data from Data File" << endl;
	ifstream fileI("Data File.txt");
	if (fileI.is_open())
	{
		ofstream resultsFile("Results.txt", ios::app);
		log << "Results has been created to print result from comparaison" << endl;
		if (!resultsFile.is_open())
		{
			log << "Results could not be opened" << endl;
			exit(0);
		}
		printDateTime(resultsFile, log);

		ListOfHosts listFromFile = { 0,5 };
		listFromFile.element = new Host*[listFromFile.capacity];
		readData(log, listFromFile, fileI);
		
		for (int i = 0; i < listHosts.nbHosts; i++)
		{
			Host* curr= listHosts.element[i];
			bool exists = false;
			for (int j = 0; j < listFromFile.nbHosts; j++)
			{
				Host* compareTo = listFromFile.element[j];
				if (curr->macAdress == compareTo->macAdress)
				{
					if (curr->ip == compareTo->ip)
						resultsFile << "MAC Adress: " << curr->macAdress << " IP: " << curr->ip << "CONNECTED" << endl;
					else
						resultsFile << "MAC Adress: " << curr->macAdress << "CONNECTED WITH DIFFERENT IP: " << curr->ip << endl;
					listHosts.element[i] = nullptr;
					break;
					exists = true;
				}
			}
			if (exists)
				resultsFile << "MAC Adress: " << curr->macAdress << "has established a NEW connection with IP: " << curr->ip << endl;
		}
		for (int i = 0; i < listFromFile.nbHosts; i++)
		{
			Host* curr = listFromFile.element[i];
			bool exists = false;
			for (int j = 0; j < listHosts.nbHosts; j++)
			{
				Host* compareTo = listHosts.element[j];
				if (compareTo->macAdress == curr->macAdress)
				{
					exists = true;
					break;
				}
			}
			if (exists = false)
				resultsFile << "MAC Adress " << curr->macAdress << " CLOSED it's connection to the network" << endl;
		}
		resultsFile << "--------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		log << "Data File does not exist a new one has been created to print hosts" << endl;
		printHosts(log, listHosts);
	}
}