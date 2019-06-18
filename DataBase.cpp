#include "DataBase.h"

DataBase::DataBase(const string& dbName, const string& networkIp)
/*
	@det		Constructor of a DataBase class
	@param 		string	name of the network to be given to the database
	@return 	void
*/
{
	ofstream log_("logFile.txt", std::ios_base::app);
	networkTable_ = networkIp;
	int dbReturn = sqlite3_open( (dbName + ".db").c_str(), &db_);
	if(dbReturn != SQLITE_OK) 
		throw sqlite3_openError("Could not establish a connecting to the databases"); 

	string createTable = "CREATE TABLE IF NOT EXISTS '" \
		+ networkTable_ + "'(" \
		"MAC TEXT PRIMARY	KEY 	NOT NULL," \
		"IP					TEXT 	NOT NULL," \
		"STATUS				REAL," \
		"LATENCY			REAL);";
	statementExec(createTable, false);

	log_ << "Database opened successfully" << endl;
}

void DataBase::statementExec(const string& sqlCommand, const bool execute)
/*
	@det		This method will execute an SQL statement
	@param 		string	sql command to be eexecute
	@param		a boolean indicating weather to use exec or step (depends on the statements' needs)
	@return 	void
*/
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
	else // Not all commands can use step
	{
		dbReturn = sqlite3_exec(db_, sqlCommand.c_str(), NULL, NULL, NULL); // Running the statement
		if(dbReturn != SQLITE_OK)
			throw sqlite3_executionError(sqlCommand + " " + sqlite3_errmsg(db_));
	}
	sqlite3_finalize(stmt); // Destroying object statement 
}

string DataBase::getNetworkTable() const
/*
	@det		This function will get a network's given table name in the database
	@param 		void
	@return 	string	table's name
*/
{
	return networkTable_;
}

void operator<<(DataBase& dataBase, const Network& networkToSave)
/*
	@det		Overloading operator << to save a network into a database
	@param 		DataBase	database where to save the data
	@param		Network		network to save into the database
	@return 	void
*/
{
	string sqlCommandInsert = "INSERT OR IGNORE INTO '"	;
			
	for_each(networkToSave.getContainer().begin(), networkToSave.getContainer().end(), [&](pair<string, Host*> hostPair)
	{
		if(hostPair.second->getMacAdress() != "No Available MAC Adress")
		{	
			sqlCommandInsert+= 
			dataBase.getNetworkTable()				+ "'"	\
			+ "(MAC, IP, STATUS, LATENCY) VALUES ("    			\
			+ hostPair.second->getMacAdress() 			+ ", " 	\
			+ hostPair.second->getIp() 					+ ", " 	\
			+ to_string(hostPair.second->getStatus()) 	+ ", " 	\
			+ to_string(hostPair.second->getLatency()) 	+ ") ";
			dataBase.statementExec(sqlCommandInsert ,false);
		}
	}
	);
}