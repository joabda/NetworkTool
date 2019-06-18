#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Host.h"
#include "Network.h"
#include "DataBaseException.h"

class DataBase
{
public:

	DataBase(const string& dbName)
	{
		ofstream log_("logFile.txt");
		int dbReturn = sqlite3_open( (dbName + ".db").c_str(), &db_);
		if(dbReturn != SQLITE_OK) 
			throw sqlite3_openError("Could not establish a connecting to the databases"); 

		string createTable = "CREATE TABLE IF NOT EXISTS Hosts(" \
					"MAC TEXT PRIMARY	KEY 	NOT NULL," \
					"IP					TEXT 	NOT NULL," \
					"STATUS				REAL," \
					"LATENCY			REAL);";
		statementExec(createTable, false);

		log_ << "Database opened successfully" << endl;
	}

	bool statementExec(const string& sqlCommand, const bool execute)
	{
		int dbReturn = 0;
		sqlite3_stmt* stmt; // Creating an object statement

		// "If the nByte argument is negative, then zSql is read up to the first zero terminator." - sqlite.ord
		dbReturn = sqlite3_prepare_v2(db_, sqlCommand.c_str(), -1, &stmt, NULL); // Preparation of the statement
		if(dbReturn != SQLITE_OK)
			throw sqlite3_statementError(sqlCommand + " " + sqlite3_errmsg(db_));
		
		if(execute)
		{
			dbReturn = sqlite3_step(stmt); // Running the statement
			if(dbReturn != SQLITE_OK)
				throw sqlite3_stepError(sqlCommand + " " + sqlite3_errmsg(db_));
		}
		else
		{
			dbReturn = sqlite3_exec(db_, sqlCommand.c_str(), NULL, NULL, NULL); // Running the statement
			if(dbReturn != SQLITE_OK)
				throw sqlite3_executionError(sqlCommand + " " + sqlite3_errmsg(db_));
		}
		sqlite3_finalize(stmt); // Destroying object statement 
	}

	void fonctionOperateurAffichage()
	{
		int dbReturn = 0;

		string tableExistance = "select count(type) from sqlite_master where type='table' and name='TABLE_NAME_TO_CHECK';";
		try{
			statementExec(tableExistance, true);
		}
		catch (sqlite3_executionError error ){
			cout << error.what("\n") << endl;
		}
	
	}

	void addToDB(Host* toAdd)
	{
		string sqlCommandInsert = "INSERT INTO Hosts (MAC, IP, STATUS, LATENCY) VALUES (" 
				+ toAdd->getMacAdress() 			+ ", "\
				+ toAdd->getIp() 					+ ", " \
				+ to_string(toAdd->getStatus()) 	+ ", " \
				+ to_string(toAdd->getLatency()) 	+ ")"; 
		statementExec(sqlCommandInsert ,true);
	}
private:
	ofstream log_;
	sqlite3* db_;
};

int main()
{

}	