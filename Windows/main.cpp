/*
 This is a program that will use Nmap to scan for the host available on your network
	The program will then save them in a text file


 *Host Status:
	 0= Not running
	 1= Up and running

 */

#include <iostream>
#include <fstream>
#include <string>
#include "Utility.h"
#include "nmap.h"
#include "Process.h"
#include "Output.h"
#include "Compare.h"
using namespace std;

int main()
{
	ofstream log("logfile.txt");
	string ip;

	if (!log.is_open())
	{
		log << "Log file could not be opened." << endl;
		exit(0);
	}
	findSubnetIp(log, ip);
	nmap(log, ip);

	ListOfHosts hostsList = { 0,10 };
	hostsList.element = new Host*[hostsList.capacity];
	process(log, hostsList);
	comparingData(log, hostsList);
}