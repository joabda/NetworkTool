#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Host.h"
#include "Network.h"
class Network;
using namespace std;

class DataBase
{
    public:
        DataBase(const string& dbName, const string& networkIp);
        void error(const string& message);
        string getNetworkTable() const;
        map<string, Host*> readDB();
        friend void operator<<(DataBase& dataBase, const Network& networkToSave);
        ~DataBase();

    private:
        ofstream log_;
        sqlite3* db_;
        string dbName_;
        int rc_;
        char* errorMessage_;
        string networkTable_;
};