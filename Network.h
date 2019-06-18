#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <iterator>
#include "Algorithm.h"
#include "Manager.h"
#include "Host.h"
using namespace std;

static string nmapOutputFileName = "NmapOutput.txt";

class Network: public Manager<pair<string,Host*>, map<string,Host*>>    
{
public:
    Network();
    Network(const string& networkName);
    ~Network();

    //Setters
    void setName(const string& name) noexcept;
    void setPrefix(const string& prefix);
 
    //Getters
    string getName() const noexcept;
    string getIp() const noexcept;
    string getPrefix() const noexcept;

    Host* findHost(const string& macAdress) const noexcept;
    void nmapCommand();
    void findIp();
    void processNmapData();

    Network& operator+= (Host* hostToAdd);
    friend ostream& operator<< (ostream& os, const Network& networkPrint); 

private:
    string name_;
    string ip_;
    string prefix_;
    ofstream log_;
};

void deleteFile(ostream &log, const string& toDelete);

#endif