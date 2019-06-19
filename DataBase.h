#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Host.h"
#include "Network.h"

using namespace std;

class DataBase
{
    public:
        DataBase(const string& dbName, const string& networkIp);
        void error(const string& message);
        string getNetworkTable() const;

        friend void operator<<(DataBase& dataBase, const Network& networkToSave);
        ~DataBase();

    private:
        ofstream log_;
        sqlite3* db_;
        int rc_;
        char* errorMessage_;
        string networkTable_;
};
#endif