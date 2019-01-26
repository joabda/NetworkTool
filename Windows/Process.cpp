#include "Utility.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Process.h"

using namespace std;

void findMACAdress(const string& line, Host* currHost)
{
	int position = line.find(" ");
	position = line.find(" ", position + 1);
	currHost->macAdress = line.substr(position + 1, 17);
}

void process(ostream &log, ListOfHosts& listHosts)
// This function will be reading line by line from the nmap output file
// Then will process the data to save for every host it's IP, Status and ports
// Into the structure 
{
	string nmapOutput = "NmapOutput.txt";
	ifstream nmapOutputFile(nmapOutput);
	string line;
	int position = 0;
	if (!nmapOutputFile.is_open())
	{
		log << "Nmap Output file could not be opened" << endl;
		return;
	}
	else
		log << "Nmap Output file has been opened for processing" << endl;
	while (!ws(nmapOutputFile).eof())
	{
		getline(nmapOutputFile, line);
		if (line.find("Nmap scan report for ") != -1)
		{
			listHosts.element[listHosts.nbHosts] = new Host;
			listHosts.element[listHosts.nbHosts]->ports = { 0,5 };
			listHosts.element[listHosts.nbHosts]->ports.element = new Port*[listHosts.element[listHosts.nbHosts]->ports.capacity];
			Host* currHost = listHosts.element[listHosts.nbHosts];
			currHost->ip = line.substr(21);
			getline(nmapOutputFile, line);
			if (line.find("Host is up") != -1)
			{
				currHost->status = 1;
				line = line.substr(12);
				position = line.find("s");
				line = line.substr(0, position);
				currHost->latency = stof(line, NULL);
				getline(nmapOutputFile, line);
				getline(nmapOutputFile, line);

				if (line.find("PORT") != -1)
				{ 
					getline(nmapOutputFile, line);
					while (line.find("MAC Address") == -1)
					{
						if (line == "")
							break;
						currHost->ports.element[currHost->ports.nbPorts] = new Port;
						Port* currPort = currHost->ports.element[currHost->ports.nbPorts];
						
						position = line.find("/");
						currPort->p_number = line.substr(0, position);
						
						line = line.substr(position + 1);

						position = line.find(" ");
						currPort->p_protocol = line.substr(0,position);

						line = line.substr(position + 1);

						position = line.find(" ");
						currPort->p_state = line.substr(0, position);

						currPort->p_service = line.substr(position+2);

						currHost->ports.nbPorts++;
						getline(nmapOutputFile, line);
					}
					findMACAdress(line, currHost);
				}
				else
				{
					getline(nmapOutputFile, line);
					findMACAdress(line, currHost);
				}
			}
			else
				listHosts.element[listHosts.nbHosts]->status = 0;
			listHosts.nbHosts++;
		}
	}
	log << "Nmap Output file's data has been processed" << endl;
	nmapOutputFile.close();
	deleteFile(log, nmapOutput);
}