#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Host.h"
#include "Network.h"
#include "DataBaseException.h"

using namespace std;

class DataBase
{
    public:
        DataBase(const string& dbName, const string& networkIp);
        // void dbError(const int& dbReturn);
        void statementExec(const string& sqlCommand, const bool execute);
        string getNetworkTable() const;

        friend void operator<<(DataBase& dataBase, const Network& networkToSave);

    private:
        ofstream log_;
        sqlite3* db_;
        string networkTable_;
};
#endif