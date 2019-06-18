#include "Network.h"

Network::Network():
	name_("Network 1"),
	ip_("Undefined yet")
/*
	@det 		Default constructor of a Network will set the attributs to default values
	@param 		void
	@return 	void
*/
{
	log_ = ofstream("logFile.txt", std::ios_base::app);
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
	@det 		Constructor of a Network will set the attributs to given values
	@param 		string 	Name to be given to network
	@return 	void
*/
{
	log_ = ofstream("logFile.txt");
	if (!log_.is_open())
	{
		cout << "Error 3 : Log file could not be opened" << endl;
		exit(3);
	}
}

void Network::setName(const string& name) noexcept
/*
	@det 		This function will set the name of the network
	@param 		string 	Name to be given to the network
	@return 	void
*/
{
	name_ = name;
}

string Network::getName() const noexcept
/*
	@det 		This function will get the given name of the network
	@param 		void
	@return 	string	Name of the network
*/
{   	
    return name_;
} 

string Network::getIp() const noexcept
/*
	@det 		This function will get the Ip of the current network
	@param 		void
	@return 	string	Ip of the network
*/
{
    return ip_;
}

string Network::getPrefix() const noexcept
{
	return prefix_;
}

Host* Network::findHost(const string& macAdress) const noexcept
/*
	@det 		This function will find a host identifier by his mac adress, in the network's hosts list
	@param 		void
	@return 	Host*		Pointer to the found host, or nullptr if the host is not found
*/
{
	if(conteneur_.find(macAdress) != conteneur_.end())
		return conteneur_.at(macAdress);
	return nullptr;
}

void Network::nmapCommand()
/*
	@det 		This function will build the command string, (an nmap command) that will be executed on system, 
		in addition the command's output will be redirected to a .txt file
	@param		void
	@return 	void
*/
{
    string ip = ip_;
	cout << "Please enter your Super User's password in order to execute nmap properly." << endl;
	log_ << "Promping user for SU clearance" << endl;
	string nmapCommand = "sudo nmap -v -sS -A -T5 ";
	string command2 = " -oN NmapOutput.txt";
	unsigned positionDot = ip.rfind(".");

	if (positionDot != string::npos)
	{
		ip = ip.substr(0, positionDot + 1);
		log_ << "Executing Command on Nmap with" << endl;
		nmapCommand += ip + '*' + command2;
		log_ << "Network's IPs prefex is: " << ip << endl;
		prefix_ = ip;
		log_ << nmapCommand << endl;
		system(nmapCommand.c_str());
	}
	else
		log_ << "Could not truncate the IP" << endl;
}

void Network::findIp()
/*
	@det 		This function will find the subnet's ip, by executing a command, redirecting it's output and analyzing it.
	@param 		void
	@return 	void
*/
{
	log_ << "Executing command on CMD to find subnet's IP" << endl;
	system("ip route | grep default > temporary.txt");
	ifstream temporaryFile("temporary.txt");

	if (!temporaryFile.is_open())
		throw runtime_error("Error 3 : Could not open the temporary file\n"); 
	else
	{
		log_ << "The temporary file has been opened successfully." << endl;
		string line;
		while (!ws(temporaryFile).eof())
		{
			getline(temporaryFile, line);
			unsigned found = line.find("default via ");
			if (found != string::npos)
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

void Network::setPrefix(const string& prefix)
{
	prefix_ = prefix;
}

void Network::processNmapData()
{
	Algorithm treatFile(this, nmapOutputFileName);
	treatFile();
}

Network& Network::operator+= (Host* hostToAdd)
/*
	@det 		This function will add a host to the network's hosts list
	@param 		Host* 		Pointer to the host that should be added
	@return 	Network&	Reference to the network (in order to be able to do multiple +=)
*/
{
	add({hostToAdd->getMacAdress(), hostToAdd});
	return *this;
}

ostream& operator<< (ostream& os, const Network& networkPrint)
/*
	@det 		This function will print everything about a network on a specific stream
	@param 		ostream& 	Stream where to print the infos
	@return 	Network&	Reference to the network that we want to print out
*/
{
	os << "\t\t\t"  << networkPrint.name_ << " at: " << networkPrint.ip_ << endl;
	cout << "Nb elements in container: " << networkPrint.conteneur_.size() << endl;
	for_each(networkPrint.conteneur_.begin(), networkPrint.conteneur_.end(), [&os](pair<string,Host*> toPrint)
	{
		os << *(toPrint.second);
	}
	);
	return os;
}

void deleteFile(ostream &log, const string& toDelete)
/*
	@det 		This function will delete a certain file that is no longer needed
	@param 		ostream&	Log file where everything during the executing will be placed to analyse any error
	@return 	string&		Name of the file to be deleted
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

Network::~Network() 
/*
	@det 		Destructor of a Network, will delete all the hosts
	@param 		void
	@return 	void
*/
{
	// saveInDB();
	auto it = conteneur_.begin();
	for_each(it, conteneur_.end(), [](pair<string, Host*> pairToDelete) 
	{
		delete pairToDelete.second;
	}
	);
}