#pragma once

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
#include "DataBase.h"
#include "Compare.h"
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
    void compareToDB();

    Network& operator+= (Host* hostToAdd);
    friend ostream& operator<< (ostream& os, const Network& networkPrint); 

private:
    //DataBase db_;
    string name_;
    string ip_;
    string prefix_;
    ofstream log_;
};