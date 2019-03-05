#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>
#include <iostream>
#include "Port.h"

using namespace std;

class Host
{
public:
    Host();
    ~Host();

    // Setters
    void setIp(const string& ip);
    void setStatus(int status);
    void setLatency(float latency);
    void setMacAdress(const string& macAdress);

    // Getters
    string getIp() const;
    int getSatus() const;
    float getLatency() const;
    string getMacAdress() const;

    Host& operator+= (Port* portAdd);
    friend ostream& operator<< (ostream& os, const Host& hostPrint);

private:
    string ip_;
    int status_;
    float latency_;
    string macAdress_;
    vector<Port*> listOfPorts_;
};
#endif