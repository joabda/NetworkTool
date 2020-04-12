#include "Network.h"

using namespace std;

int main()
{
	Network testNetwork;
	ofstream log("logFile.txt");
	try {
		testNetwork.findIp();
	} catch(const runtime_error& error) {
		log 	<< error.what() 									<< endl;
		cout 	<< "Exiting program, could not find Network's IP" 	<< endl;
	}

	testNetwork.nmapCommand();
	testNetwork.processNmapData();
	ofstream testPrint("Hosts.txt");
	testPrint << testNetwork;
	testNetwork.compareToDB();
}