#include "Port.h"

/*
	@det		This function will set a port's number
	@param 		string	Number to be given to the port
	@return 	void
*/
Port::Port() :
	number_("0"),
    protocol_("0"),
    state_("0"),
    service_("0")
{} 

void Port::setNumber(const string& number)
/*
	@det		This function will set a port's number
	@param 		string	Number to be given to the port
	@return 	void
*/
{
    number_ = number;
}

void Port::setProtocol(const string& protocol)
/*
	@det		This function will set a port's protocol
	@param 		string	Protocol to be given to the port
	@return 	void
*/
{
    protocol_ = protocol;
}

void Port::setState(const string& state)
/*
	@det		This function will set a port's state
	@param 		string	State to be given to the port
	@return 	void
*/
{
    state_ = state;
}

void Port::setService(const string& service)
/*
	@det		This function will set a port's number
	@param 		string	Service to be given to the port
	@return 	void
*/
{
    service_ = service;
}

string Port::getNumber() const
/*
	@det		This function will get the given number of a port
	@param 		void
	@return 	string	Number of a Port
*/
{
    return number_;
}

string Port::getProtocol() const
/*
	@det		This function will get the given protocol of a port
	@param 		void
	@return 	string	Protocol of a Port
*/
{
    return protocol_;
}

string Port::getState() const
/*
	@det		This function will get the given state of a port
	@param 		void
	@return 	string	State of a Port
*/
{
    return state_;
}

string Port::getService() const
/*
	@det		This function will get the given service of a port
	@param 		void
	@return 	string	Service of a Port
*/
{
    return service_;
}

ostream& operator<< (ostream& os, const Port& portPrint)
/*
	@det		Fis function will print everything about a port on a specific stream
	@param 		ostream& 	stream where the infos will be printed
	@param		Port& 		reference to the port that should be printed
	@return 	Port&	 	Reference to the port that we want to print out
*/
{
    os 	<< "\t" << portPrint.number_ 
		<< "/"	<< portPrint.state_ 
		<< "," 	<< portPrint.protocol_ 
		<< ":" 	<< portPrint.service_ 	
		<< endl;
    return os;
}