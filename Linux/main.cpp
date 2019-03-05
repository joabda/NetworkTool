#include "Network.h"

using namespace std;

int main()
{
	Network networkTest("Home");
	networkTest.findIp();
	networkTest.nmapCommand();
	networkTest.processNmapData();

	ofstream dataFile("data.txt");
	dataFile << networkTest << endl;

	// comparingData(log, hostsList);
}