#ifndef PORT_H
#define PORT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Port
{
public:
    Port();
   // Port(const string& number, const string& protocol, const string& state, const string& service);
    
    //Setters
    void setNumber(const string& number);
    void setProtocol(const string& protocol);
    void setState(const string& state);
    void setService(const string& service);

    //Getters
    string getNumber() const;
    string getProtocol() const;
    string getState() const;
    string getService() const;

    friend ostream& operator<< (ostream& os, const Port& portPrint); 
    
private:
    string number_;
    string protocol_;
    string state_;
    string service_;
};
#endif