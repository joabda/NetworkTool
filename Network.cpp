#include "Network.h"

Network::Network():
	name_("Network 1"),
	ip_("Undefined")
	// db_("Netwokrs", ip_)
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
	ip_("Undefined")
	// db_("Netwokrs", ip_)
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
	if(container_.find(macAdress) != container_.end())
		return container_.at(macAdress);
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
					log_ << "Error 1: Network's IP could not be found!" << endl;
                    exit(1);
                }
			}
		}
	}

	temporaryFile.close();
	string removeFile = "rm temporary.txt";
	system(removeFile.c_str());
	int returnOfDelete = remove("temporary.txt");
	if (returnOfDelete == 0)
		log_ << "temporary.txt" << " has been deleted successfully." << endl;
	else
		log_ << "Error: Unable to delete " << "temporary.txt" << "." << endl;
}

void Network::setPrefix(const string& prefix)
{
	prefix_ = prefix;
}

void Network::processNmapData()
{
	Algorithm processNmapAlgorithm(this, nmapOutputFileName);
	processNmapAlgorithm();
	log_ << "Nmap output has been treated." << endl;
}

void Network::compareToDB()
{
	DataBase db("Netwokrs", ip_);
	map<string, Host*>dbHosts = db.readDB();
	LinuxNotifyManager notification;
	for(auto& currHost : container_)
	{
		if(currHost.first != "No Available MAC Adress")
		{
			auto hostInDB = dbHosts.find(currHost.first);
			if(hostInDB == dbHosts.end())
			{
				log_ << currHost.first << " just joined the network using the following IP: " << currHost.second->getIp() << " ." << endl;
				notification.notifyEvent(currHost.second);
			}
			else
				if(hostInDB->second->getModel() != currHost.second->getModel())
					log_ << "There's a problem with " << currHost.first << " model do not match information from database." << endl;
		}
	}
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
	for_each(networkPrint.container_.begin(), networkPrint.container_.end(), [&os](pair<string,Host*> toPrint)
	{
		os << *(toPrint.second);
	}
	);
	return os;
}

Network::~Network() 
/*
	@det 		Destructor of a Network, will save the hosts to the DB before deleting them
	@param 		void
	@return 	void
*/
{
	DataBase db("Netwokrs", ip_);
	db << (*this);
	auto it = container_.begin();
	for_each(it, container_.end(), [](pair<string, Host*> pairToDelete) 
	{
		delete pairToDelete.second;
	}
	);
}