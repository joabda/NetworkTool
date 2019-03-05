#include "Utility.h"
#include "nmap.h"
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void findSubnetIp(ostream &log, string& ip)
/*
	* This function will find the subnet's ip, by executing a command, redirecting it's output and analyzing it.
	* \param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
				string& ip  	==> String ip, where the subnet ip will be saved
	* \return 	void
*/
{
	log << "Executing command on CMD to find subnet's IP" << endl;

	system("ip route | grep default > temporary.txt");

	string temporary = "temporary.txt";
	ifstream temporaryFile(temporary);

	if (!temporaryFile.is_open())
		log << "Could not open the temporary file" << endl;
	else
	{
		log << "The temporary file has been opened successfully." << endl;
		string line;
		while (!ws(temporaryFile).eof())
		{
			getline(temporaryFile, line);
			int found = line.find("default via ");
			if (found != string::npos)
				// string::npos is returned by find when nothing is found 
			{
				found = 12;
				int findSpace = line.find(" ", found+1);	
				if (findSpace != string::npos)
				{
					int length = findSpace - found;
					ip = line.substr(found, length);
					log << "The subnet's IP is: " << ip << endl;
				}
			}
		}
	}
	temporaryFile.close();
	deleteFile(log, temporary);
}

void nmap(ostream &log, string& ip)
/*
	* This function will build the command string, (an nmap command) that will be executed on system, in addition the command's output will be redirected to a .txt file
	* \param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
				string& ip  	==> String ip will be used to construct nmap command
	* \return 	void
*/
{
	string nmapCommand = "nmap ";
	string command2 = " -oN NmapOutput.txt";
	int positionDot = ip.rfind(".");

	if (positionDot != string::npos)
	{
		ip = ip.substr(0, positionDot + 1);

		log << "Executing Command on Nmap with" << endl;

		nmapCommand += ip + '*' + command2;

		log << nmapCommand << endl;

		system(nmapCommand.c_str());
	}
	else
		log << "Could not truncate the IP" << endl;
}