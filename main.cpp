#include "Network.h"
#include "menu.h"
#include "Host.h"
#include "DataBase.h"
#include <algorithm>

using namespace std;

int main()
{
	Network testNetwork;
	testNetwork.setName("Test Network");
	testNetwork.setPrefix("192.168.1.");
	// ofstream log("logFile.txt");
	// try
	// {
	// 	testNetwork.findIp();
	// }
	// catch(const runtime_error& error)
	// {
	// 	log 	<< error.what() 									<< endl;
	// 	cout 	<< "Exiting program, could not find Network's IP" 	<< endl;
	// }

	// testNetwork.nmapCommand();
	testNetwork.processNmapData();
	ofstream testPrint("print.txt");
	testPrint << testNetwork;
	//DataBase testDB("TestPrint", testNetwork.getIp());
	//testDB << testNetwork;
}