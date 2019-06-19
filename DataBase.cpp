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
	int rc_ = sqlite3_open( (dbName + ".db").c_str(), &db_);
	if(rc_ != SQLITE_OK) 
		error("Could not establish a connecting to the databases"); 

	string createTable = "CREATE TABLE IF NOT EXISTS '" \
		+ networkTable_ + "'(" \
		"MAC TEXT PRIMARY	KEY 	NOT NULL,	" \
		"IP					TEXT 	NOT NULL,	" \
		"LATENCY			REAL,				" \
		"MODEL				TEXT,				" \
		"OS					TEXT);";

	rc_ = sqlite3_exec(db_, createTable.c_str(), nullptr, nullptr, &errorMessage_);
	if (rc_ != SQLITE_OK )
		error("SQL error");

	log_ << "Database opened successfully" << endl;
}

void DataBase::error(const string& message)
/*
	@det		Method to treat errors of database
	@param 		string customized message to be added
	@return 	void
*/
{
    fprintf(stderr, "%s: %s\n", message.c_str(), sqlite3_errmsg(db_));
    sqlite3_free(errorMessage_);
    sqlite3_close(db_);
}

// argc is the number of columns in the table
// argv are the values of the entries
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
   for(int i = 0; i < argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   printf("\n");
   return 0;
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
	string sqlCommandInsertBase = "INSERT OR IGNORE INTO '"	;
	for(auto& i : networkToSave.getContainer())
	{
		if(i.second != nullptr && i.first != "No Available MAC Adress")
		{	
			string sqlCommandInsert = sqlCommandInsertBase 
			+ dataBase.getNetworkTable()						+ "'"			\
			+ "(MAC, IP, LATENCY, MODEL, OS) VALUES ("    						\
			+ "'" + i.second->getMacAdress() 			+ "'" + ", " 	\
			+ "'" + i.second->getIp() 					+ "'" + ", " 	\
			+ to_string(i.second->getLatency()) 			+ ", " 			\
			+ "'" + i.second->getModel() 				+ "'" + ", " 	\
			+ "'" + i.second->getOs() 					+ "'" + ");"	;
			cout << sqlCommandInsert << endl << endl << endl;
			dataBase.rc_ = sqlite3_exec(dataBase.db_, sqlCommandInsert.c_str(), callback, nullptr, &dataBase.errorMessage_);
			if (dataBase.rc_ != SQLITE_OK )
				dataBase.error("SQL error");
		}
	}
}

DataBase::~DataBase()
{
	sqlite3_close(db_);
}