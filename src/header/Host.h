#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <iterator>
#include "Manager.h"
#include "Port.h"

using namespace std;

class Host : public Manager<Port*, set<Port*>>    
{
public:
    Host();
    Host(const string& ip, const string& macAdress, int latency, const string& model, const string& os);

    // Setters
    void setIp(const string& ip);
    void setStatus(int status);
    void setLatency(float latency);
    void setMacAdress(const string& macAdress);
    void setModel(const string& model);
    void setOs(const string& os);
    void setManufacturer(const string& manufacturer);

    // Getters
    string getIp() const;
    int getStatus() const;
    float getLatency() const;
    string getMacAdress() const;
    string getModel() const;
    string getOs() const;
    string getManufacturer() const;

    Host& operator+= (Port* portAdd);
    friend ostream& operator<<(ostream& os, const Host& toPrint);

    ~Host();    

private:
    string ip_;
    int status_;
    float latency_;
    string macAdress_;
    string model_;
    string os_;
    string manufacturer_;
};