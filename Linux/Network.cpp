#include "Network.h"

Network::Network() :
	name_("Network 1"),
	ip_("Undefined yet")
/*
	* Default constructor of a Network will set the attributs to default values
	@param 		Nothing
	@return 	Nothing
*/
{
	log_ = ofstream("logFile.txt");
	if (!log_.is_open())
	{
		cout << "Error 3 : Log file could not be opened" << endl;
		exit(3);
	}
}

Network::Network(const string& networkName) :
	name_(networkName),
	ip_("Undefined yet")
/*
	* Constructor of a Network will set the attributs to given values
	@param 		string 		==> Name to be given to network
	@return 	Nothing
*/
{
	log_ = ofstream("logFile.txt");
	if (!log_.is_open())
	{
		cout << "Error 3 : Log file could not be opened" << endl;
		exit(3);
	}
}

Network::~Network()
/*
	* Destructor of a Network, will delete all the hosts
	@param 		Nothing
	@return 	Nothing
*/
{
	for(auto& item : hosts_)
        delete item;
}

void Network::setName(const string& name)
/*
	* This function will set the name of the network
	@param 		string 		==> Name to be given to the network
	@return 	void
*/
{
	name_ = name;
}

string Network::getName() const
/*
	* This function will get the given name of the network
	@param 		Nothing
	@return 	string		==> Name of the network
*/
{   	
    return name_;
} 

string Network::getIp() const
/*
	* This function will get the Ip of the current network
	@param 		Nothing
	@return 	string		==> Ip of the network
*/
{
    return ip_;
}

Host* Network::findHost(const string& macAdress) const
/*
	* This function will find a host identifier by his mac adress, in the network's hosts list
	@param 	ostream log 	==> Log file where everything during the executing will be palced to analyse any error
	@return 	Host*		==> Pointer to the found host, or nullptr if the host is not found
*/
{
    for(auto& item : hosts_)
        if (item->getMacAdress() == macAdress) 
            return item;
    return nullptr;
}

void Network::nmapCommand()
/*
	* This function will build the command string, (an nmap command) that will be executed on system, in addition the command's output will be redirected to a .txt file
	@param 	ostream& 		==> Log file where everything during the executing will be palced to analyse any error
			string& 		==> String ip will be used to construct nmap command
	@return 	void
*/
{
    string ip = ip_;
	string nmapCommand = "nmap ";
	string command2 = " -oN NmapOutput.txt";
	unsigned positionDot = ip.rfind(".");

	if (positionDot != string::npos)
	{
		ip = ip.substr(0, positionDot + 1);

		log_ << "Executing Command on Nmap with" << endl;

		nmapCommand += ip + '*' + command2;

		log_ << nmapCommand << endl;

		system(nmapCommand.c_str());
	}
	else
		log_ << "Could not truncate the IP" << endl;
}

void Network::findIp()
/*
	* This function will find the subnet's ip, by executing a command, redirecting it's output and analyzing it.
	@param 		ostream&	==> Log file where everything during the executing will be palced to analyse any error
	@return 	void
*/
{
	log_ << "Executing command on CMD to find subnet's IP" << endl;

	system("ip route | grep default > temporary.txt");

	ifstream temporaryFile("temporary.txt");

	if (!temporaryFile.is_open())
    {
		log_ << "Could not open the temporary file" << endl;
        cout << "Error 3 : Could not open the temporary file" << endl;
        exit(3);
    }
	else
	{
		log_ << "The temporary file has been opened successfully." << endl;
		string line;
		while (!ws(temporaryFile).eof())
		{
			getline(temporaryFile, line);
			unsigned found = line.find("default via ");
			if (found != string::npos)
				// string::npos is returned by find when nothing is found 
			{
				found = 12;
				unsigned findSpace = line.find(" ", found+1);	
				if (findSpace != string::npos)
				{
					int length = findSpace - found;
					ip_ = line.substr(found, length);
					log_ << "The subnet's IP is: " << ip_ << endl;
				}
                else
                {
                    exit(1);
                    cout << "Error 1: Network's IP could not be found!" << endl;
                }
			}
		}
	}
	temporaryFile.close();
	deleteFile(log_, "temporary.txt");
}

void findMACAdress(const string& line, Host* currHost)
/*
	* This function will find a host's MAC Adress
	@param 		string 		==> The line where the MAC adress will be found
				Host*	 	==> A pointer to the current host where to save the MAC Adress
	@return 	void
*/
{
	int position = line.find(" ");
	position = line.find(" ", position + 1);
	currHost->setMacAdress( line.substr(position + 1, 17) );
}

void Network::processNmapData()
/*
	* This function will read line by line from nmap redirected output, in order to process data and save host's informations (IP, Status, and Ports)
	@param 		ostream&		==> Log file where everything during the executing will be palced to analyse any error
				ListofHosts  	==> Structure where the data will be saved
	@return 	void
*/
{
	ifstream nmapOutputFile("NmapOutput.txt");
	string line;
	unsigned position = 0;
	if (!nmapOutputFile.is_open())
	{
		log_ << "Error 3 : Nmap Output file could not be opened" << endl;
		exit(3);
	}
	else
		log_ << "Nmap Output file has been opened for processing" << endl;
	while (!ws(nmapOutputFile).eof())
	{
		getline(nmapOutputFile, line);
		if ( line.find("Nmap scan report for ") != string::npos)
		{
			Host* currHost = new Host;
			if(line[21] <= '9' && line[21] >= '0')
				currHost->setIp( line.substr(21) );
			else
			{
				position = line.find('(');
				unsigned positionEnd = line.find(')');
				currHost->setIp( line.substr(position+1, (positionEnd-position - 1) ) );
			}

			getline(nmapOutputFile, line);
			if (line.find("Host is up") != string::npos)
			{
				currHost->setStatus(1);
				line = line.substr(12);
				position = line.find("s");
				line = line.substr(0, position);
				currHost->setLatency( stof(line, NULL) );
				getline(nmapOutputFile, line);
				getline(nmapOutputFile, line);

				if (line.find("PORT") != string::npos)
				{ 
					getline(nmapOutputFile, line);
					while (line.find("MAC Address") == string::npos)
					{
						if (line == "")
							break;
						Port* currPort = new Port;
						
						position = line.find("/");
						currPort->setNumber( line.substr(0, position) );
						
						line = line.substr(position + 1);

						position = line.find(" ");
						currPort->setProtocol( line.substr(0,position) );

						line = line.substr(position + 1);

						position = line.find(" ");
						currPort->setState( line.substr(0, position) );

						currPort->setService( line.substr(position+2) );
						getline(nmapOutputFile, line);
						*currHost += currPort;
					}
					findMACAdress(line, currHost);
				}
				// else
				// {
				// 	while(!ws(nmapOutputFile).eof())
				// 	{
				// 		getline(nmapOutputFile, line);
				// 		if(line.find("MAC Adress"))
				// 			findMACAdress(line, currHost);
				// 	}
				// }
			}
			else
				currHost->setMacAdress(0);
			*this += currHost;
		}
	}
	log_ << "Nmap Output file's data has been processed" << endl;
	nmapOutputFile.close();
	deleteFile(log_, "NmapOutput.txt");
}

Network& Network::operator+= (Host* addHost)
/*
	* This function will add a host to the network's hosts list
	@param 		Host* 		==> Pointer to the host that should be added
	@return 	Network&	==> Reference to the network (in order to be able to do multiple +=)
*/
{
	hosts_.push_back(addHost);
	return *this;
}

ostream& operator<< (ostream& os, const Network& networkPrint)
/*
	* This function will print everything about a network on a specific stream
	@param 		ostream& 	==> Log file where everything during the executing will be placed to analyse any error
	@return 	Network&	==> Reference to the network that we want to print out
*/
{
	os << "\t\t\t"  << networkPrint.name_ << " at: " << networkPrint.ip_ << endl;

	for(auto& item : networkPrint.hosts_)
        os << *item;
	return os;
}

void deleteFile(ostream &log, const string& toDelete)
/*
	* This function will delete a certain file that is no longer needed
	@param 		ostream&    ==> Log file where everything during the executing will be placed to analyse any error
	@return 	string&	    ==> Name of the file to be deleted
*/
{
	string removeFile = "rm " + toDelete;
	system(removeFile.c_str());
	int returnOfDelete = remove(toDelete.c_str());
	if (returnOfDelete == 0)
		log << toDelete << " has been deleted successfully." << endl;
	else
		log << "Error: Unable to delete " << toDelete << "." << endl;
}