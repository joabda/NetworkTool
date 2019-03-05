#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include "Host.h"

using namespace std;

class Network
{
public:
    Network();
    Network(const string& networkName);
    ~Network();

    //Setters
    void setName(const string& name);

    //Getters
    string getName() const;
    string getIp() const;

    Host* findHost(const string& macAdress) const;
    void nmapCommand();
    void findIp();
    void processNmapData();

    Network& operator+= (Host* addHost);
    friend ostream& operator<< (ostream& os, const Network& networkPrint); 

private:
    string name_;
    string ip_;
    ofstream log_;
    vector<Host*> hosts_;
};

void deleteFile(ostream &log, const string& toDelete);

#endif