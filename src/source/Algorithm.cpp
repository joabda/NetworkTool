#include "../header/Algorithm.h"

static int lengthOfMacAdress = 17;

Algorithm::Algorithm(Network* currentNetwork, const string& nmapOutputFileName) :
	currentNetwork_(currentNetwork),
	nmapFileName_(nmapOutputFileName)
{
	
}

bool Algorithm::findNextUpHost(istream& nmapFile)
/*
	@det 		Method to find the next host in file
	@param 		istream 	stream to read from
	@return 	bool		true if the next host has been found, else false
*/
{
	while(!ws(nmapFile).eof())
	{
		if(line_.find("Nmap scan report for") != string::npos
			&& line_.find("host down") == string::npos)
				return true;
		else
			getline(nmapFile, line_);
	}
	return false;
}

string Algorithm::findIp(istream& nmapFile) const
/*
	@det 		Find ip of current host
	@param 		istream 	stream to read from
	@return 	string 		ip of the host
*/
{
	int startOfIp = line_.find(currentNetwork_->getPrefix());
	unsigned endParentheses = line_.find(")");
	if(endParentheses != string::npos)
		return(line_.substr(startOfIp, endParentheses-startOfIp));
	else
		return(line_.substr(startOfIp, line_.find("\n")-startOfIp));
}

float Algorithm::findLatency(istream& nmapFile)
/*
	@det 		Find latency of current host
	@param 		istream 	stream to read from
	@return 	string 		latency of the host
*/
{
	getline(nmapFile, line_);
	int positionStart = line_.find("(")+1;
	int positionEnd = line_.find("s", positionStart+1);
	return atof(line_.substr(positionStart, positionEnd-positionStart).c_str());
}

string Algorithm::findMac(istream& nmapFile)
/*
	@det 		Find MAC adress of current host
	@param 		istream 	stream to read from
	@return 	string 		MAC adress of the host
*/
{
	while(!ws(nmapFile).eof() && line_.find("Nmap scan report for") == string::npos)
	{
		if(line_.find("MAC Address:") == string::npos)
			getline(nmapFile, line_);
		else
			return line_.substr(13, lengthOfMacAdress);
	}
	return "No Available MAC Adress";
}

string Algorithm::findModel() const
/*
	@det 		Find model of current host
	@param 		void
	@return 	string 		model of the host
*/
{
	unsigned startParenthese = line_.find("(")+1;
	if(startParenthese != string::npos)
		return line_.substr(startParenthese, line_.find(")")-startParenthese);
}

string Algorithm::findOs(istream& nmapFile)
/*
	@det 		Find operating system of current host
	@param 		istream 	stream to read from
	@return 	string 		operating system of the host
*/
{
	while(!ws(nmapFile).eof() && line_.find("Nmap scan report for") == string::npos)
	{
		if(line_.find("OS details:") == string::npos)
			getline(nmapFile, line_);
		else
			return line_.substr(12, line_.find("\n")-12);
	}
	return "Too many fingerprints match this host to give specific OS details";
}

void Algorithm::operator() ()
/*
	@det 		Overloading of the () operator, this will make the whole algorithm process the file
					and add the discovered to hosts to the network taken in the constructor
	@param 		void
	@return 	void
*/
{
    ifstream nmapFile(nmapOutputFileName);
	while(findNextUpHost(nmapFile))
	{
		Host currHost;
		currHost.setIp(findIp(nmapFile));
		currHost.setLatency(findLatency(nmapFile));
		currHost.setMacAdress(findMac(nmapFile));
		currHost.setModel(findModel());
		currHost.setOs(findOs(nmapFile));
		currentNetwork_->add(make_pair<string, Host*>(currHost.getMacAdress(), new Host(currHost)));
	}
}