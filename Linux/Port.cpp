#include "Port.h"

Port::Port() :
	number_("0"),
    protocol_("0"),
    state_("0"),
    service_("0")
{} 

void Port::setNumber(const string& number)
/*
	* This function will set a port's number
	@param 		string  ==> Number to be given to the port
	@return 	void
*/
{
    number_ = number;
}

void Port::setProtocol(const string& protocol)
/*
	* This function will set a port's protocol
	@param 		string  ==> Protocol to be given to the port
	@return 	void
*/
{
    protocol_ = protocol;
}

void Port::setState(const string& state)
/*
	* This function will set a port's state
	@param 		string  ==> State to be given to the port
	@return 	void
*/
{
    state_ = state;
}

void Port::setService(const string& service)
/*
	* This function will set a port's number
	@param 		string  ==> Service to be given to the port
	@return 	void
*/
{
    service_ = service;
}

string Port::getNumber() const
/*
	* This function will get the given number of a port
	@param 		Nothing
	@return 	string  ==> Number of a Port
*/
{
    return number_;
}

string Port::getProtocol() const
/*
	* This function will get the given protocol of a port
	@param 		Nothing
	@return 	string  ==> Protocol of a Port
*/
{
    return protocol_;
}

string Port::getState() const
/*
	* This function will get the given state of a port
	@param 		Nothing
	@return 	string  ==> State of a Port
*/
{
    return state_;
}

string Port::getService() const
/*
	* This function will get the given service of a port
	@param 		Nothing
	@return 	string  ==> Service of a Port
*/
{
    return service_;
}

ostream& operator<< (ostream& os, const Port& portPrint)
/*
	* This function will print everything about a port on a specific stream
	@param 		ostream&    ==> Log file where everything during the executing will be placed to analyse any error
	@return 	Port&	    ==> Reference to the port that we want to print out
*/
{
    os << "\t" << portPrint.number_ << "/" << portPrint.state_ << "," << portPrint.protocol_ << ":" << portPrint.service_ << endl;
    return os;
}