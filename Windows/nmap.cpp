#include "Utility.h"
#include "nmap.h"
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void findSubnetIp(ostream &log, string& ip)
// This function will find the subnet's ip to use it in nmap command, 
// it will copy ifconfig's output to a temporary file and search for subnet's ip
{
	const char *ret;
	log << "Executing command on CMD to find subnet's IP" << endl;

	system("ipconfig > temporary.txt");

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
			ret = strstr(line.c_str(), "Wireless LAN adapter Wi-Fi:");
			if (ret != NULL)
			{
				while (line.compare(0, 18, "   Default Gateway") != 0)
					getline(temporaryFile, line);

				ret = strstr(line.c_str(), "Default Gateway");

				if (ret != NULL)
				{
					ret = ret + 36;
					ip += ret;
					log << "The subnet's IP is: " << ip << endl;
				}
			}
		}
	}
	temporaryFile.close();
	deleteFile(log, temporary);
}

void nmap(ostream &log, string& ip)
// in this command we are formating the ip we got in find_subnet_ip to fit the nmap command
// we created the nmap command into a string, we than executed that command
// and saved it into a file called "NmapOutput"
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