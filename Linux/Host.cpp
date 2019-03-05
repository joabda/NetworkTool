#include "Host.h"

Host::Host() :
    ip_("0"),
    status_(0),
    latency_(0.0),
    macAdress_("0")
{}

Host::~Host()
{
    for(auto& item : listOfPorts_)
        delete item;
}

void Host::setIp(const string& ip)
/*
	* This function will set the ip of a Host
	@param 		string  ==> Ip to be given to a Host
	@return 	void
*/
{
    ip_ = ip;
}

void Host::setStatus(int status)
/*
	* This function will set the status of a Host
	@param 		int     ==> Status to be given to a Host
	@return 	void
*/
{
    status_ = status;
}

void Host::setLatency(float latency)
/*
	* This function will set the latency of a Host
	@param 		float   ==> Latency to be given to a Host
	@return 	void
*/
{
    latency_ = latency;
}

void Host::setMacAdress(const string& macAdress)
/*
	* This function will set the macAdress of a Host
	@param 		float   ==> MAC Adress to be given to a Host
	@return 	void
*/
{
    macAdress_ = macAdress;
}

string Host::getIp() const
/*
	* This function will get the ip of the current Host
	@param 		Nothing
	@return 	string		==> Ip of the Host
*/
{
    return ip_;
}

int Host::getSatus() const
/*
	* This function will get the status of the current Host
	@param 		Nothing
	@return 	string		==> Status of the Host
*/
{
    return status_;
}

float Host::getLatency() const
/*
	* This function will get the latency of the current Host
	@param 		Nothing
	@return 	string		==> Latency of the Host
*/
{
    return latency_;
}

string Host::getMacAdress() const
/*
	* This function will get the MAC Adress of the current Host
	@param 		Nothing
	@return 	string		==> MAC Adress of the Host
*/
{
    return macAdress_;
}

Host& Host::operator+= (Port* portAdd)
/*
	* This function will add a port to the host's list of ports
	@param 		Port* 		==> Pointer to the port that should be added
	@return 	Host&	    ==> Reference to the host (in order to be able to do multiple +=)
*/
{
    listOfPorts_.push_back(portAdd);
    return *this;
}

ostream& operator<< (ostream& os, const Host& hostPrint)
/*
	* This function will print everything about a host on a specific stream
	@param 		ostream& 	==> Log file where everything during the executing will be placed to analyse any error
	@return 	Host&	    ==> Reference to the host that we want to print out
*/
{
    os << hostPrint.ip_ << endl;
	if(hostPrint.status_ == 1)
		os << " Host is up" << endl;
	else
		os << " Host is down" << endl;
	
	
	os << " Latency: " << hostPrint.latency_ << "s." << endl;
	os << " MAC Adress: " << hostPrint.macAdress_ << endl;

   for(auto& item : hostPrint.listOfPorts_)
        os << *item;
    os << endl;
    return os;
}