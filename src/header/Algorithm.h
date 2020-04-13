#pragma once

#include "Network.h"
#include "Manager.h"
#include "Host.h"
class Network;

using namespace std;

class Algorithm
{
public:
    Algorithm(Network* currentNetwork, const string& nmapOutputFileName);
    void operator() ();
    ~Algorithm() {}

private:
    Network* currentNetwork_;
    string nmapFileName_;
    string line_;

    bool findNextUpHost(istream& nmapFile);
    string findIp(istream& nmapFile) const;
    float findLatency(istream& nmapFile);
    string findMac(istream& nmapFile);
    string findModel() const;
    string findOs(istream& nmapFile);
};
