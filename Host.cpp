#include "Host.h"

/*
	@det		Default constructor of a host, init all atributes to 0
	@param 		void
	@return 	void
*/
Host::Host() :
    ip_("0"),
    status_(0),
    latency_(0.0),
    macAdress_("0")
{}

/*
	@det		Deestructor of a host
	@param 		void
	@return 	void
*/
Host::~Host()
{
	for_each(conteneur_.begin(), conteneur_.end(), [](Port* toDelete) 
	{
		delete toDelete;
	}
	);
}

void Host::setIp(const string& ip)
/*
	@det		This function will set the ip of a Host
	@param 		string 		Ip to be given to a Host
	@return 	void
*/
{
	
    ip_ = ip;
}

void Host::setStatus(int status)
/*
	@det		This function will set the status of a Host
	@param 		int		Status to be given to a Host
	@return 	void
*/
{
    status_ = status;
}

void Host::setLatency(float latency)
/*
	@det		This function will set the latency of a Host
	@param 		float	Latency to be given to a Host
	@return 	void
*/
{
    latency_ = latency;
}

void Host::setMacAdress(const string& macAdress)
/*
	@det		This function will set the macAdress of a Host
	@param 		string	MAC Adress to be given to a Host
	@return 	void
*/
{
    macAdress_ = macAdress;
}

void Host::setModel(const string& model)
{
	model_ = model;	
}

void Host::setOs(const string& os)
{
	os_ = os;
}

void Host::setOsVersion(const string& osVersion)
{
	osVersion_ = osVersion;
}

void Host::setManufacturer(const string& manufacturer)
{
	manufacturer_ = manufacturer;
}

string Host::getIp() const
/*
	@det		This function will get the ip of the current Host
	@param 		void
	@return 	string	Ip of the Host
*/
{
    return ip_;
}

int Host::getStatus() const
/*
	@det		This function will get the status of the current Host
	@param 		void
	@return 	int	Status of the Host
*/
{
    return status_;
}

float Host::getLatency() const
/*
	@det		This function will get the latency of the current Host
	@param 		void
	@return 	float	Latency of the Host
*/
{
    return latency_;
}

string Host::getMacAdress() const
/*
	@det		This function will get the MAC Adress of the current Host
	@param 		void
	@return 	string	MAC Adress of the Host
*/
{
    return macAdress_;
}

string Host::getModel() const
{
	return model_;
}

string Host::getOs() const
{
	return os_;
}

string Host::getOsVersion() const
{
	return osVersion_;
}

string Host::getManufacturer() const
{
	return manufacturer_;
}


Host& Host::operator+= (Port* portAdd)
/*
	@det		This function will add a port to the host's list of ports
	@param 		Port*	Pointer to the port that should be added
	@return 	Host&	Reference to the host (in order to be able to do multiple +=)
*/
{
    // listOfPorts_.push_back(portAdd);
	add(portAdd);
    return *this;
}

/*
	@det		This function will print everything about a host on a specific stream
	@param 		ostream&	Stream where the infos will be printed
	@param		Host&		Host to be printed
	@return 	Host&	  	Reference to the host that we want to print out
*/
ostream& operator<<(ostream& os, const Host& toPrint)
{
    os << toPrint.ip_ << endl;
	if(toPrint.status_ == 1)
		os << " Host is up" 	<< endl;
	else
		os << " Host is down"	<< endl;
		
	os << " Latency: " 		<< toPrint.latency_ 	<< "s" 	<< endl;
	os << " MAC Adress: "	<< toPrint.macAdress_   << endl;
	for_each(toPrint.conteneur_.begin(), toPrint.conteneur_.end(),  [&os](Port* toPrint)
	{
		os << *toPrint;
	}
	);
	os << endl;
	return os;
}