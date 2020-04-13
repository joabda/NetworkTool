#include "../header/DataBase.h"
#include <utility>

DataBase::DataBase(const string& dbName, const string& networkIp)
/*
	@det		Constructor of a DataBase class
	@param 		string	name of the network to be given to the database
	@return 	void
*/
{
	ofstream log_("logFile.txt", std::ios_base::app);
	networkTable_ = networkIp;
	dbName_ = dbName;
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

	log_ << "Database opened." << endl;
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


map<string, Host*> DataBase::readDB()
/*
	@det		This function will retrieve existring hosts from database
	@param 		void
	@return 	string	table's name
*/
{
	rc_ = sqlite3_open((dbName_ + ".db").c_str(), &db_);

	if (rc_ != SQLITE_OK)
		error("Cannot open database");

	string read = "SELECT * from " + networkTable_  + ";";
	sqlite3_stmt* stmt;
	rc_ = sqlite3_prepare_v2(db_, read.c_str(), -1, &stmt, nullptr);

	if (rc_ != SQLITE_OK)
		error("Select Error");
	string createRuleParameters[6];

	map<string, Host*> dbHosts;

	while( (rc_ = sqlite3_step(stmt) ) == SQLITE_ROW)
	{
		for (int i = 0; i < 5; i++)
			createRuleParameters[i] = string(reinterpret_cast< char const* >(sqlite3_column_text(stmt, i)));
		dbHosts.insert(make_pair(createRuleParameters[0], new Host(createRuleParameters[0], createRuleParameters[1], atof(createRuleParameters[2].c_str()),
			createRuleParameters[3], createRuleParameters[4]) ));
	}

	while(rc_ == SQLITE_ROW)
	{
		for(int i=0; i < 6; i++)
			fprintf(stderr, "'%s' ", sqlite3_column_text(stmt, i));
		fprintf(stderr, "\n");
		rc_ = sqlite3_step(stmt);
	}
		
	return dbHosts;
}

bool DataBase::isInDB(const string& mac)
{
	rc_ = sqlite3_open((dbName_ + ".db").c_str(), &db_);
	
	if (rc_ != SQLITE_OK)
		error("Cannot open database");

	string read = "SELECT * from " + networkTable_ + " WHERE MAC = '" + mac + "';";
	sqlite3_stmt* stmt;
	rc_ = sqlite3_prepare_v2(db_, read.c_str(), -1, &stmt, nullptr);
	cout << mac << " is in db: " <<  boolalpha << (rc_ == SQLITE_OK) << endl;
	cout << rc_ << endl;
	return (rc_ = sqlite3_step(stmt) ) == SQLITE_ROW;
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

			dataBase.rc_ = sqlite3_exec(dataBase.db_, sqlCommandInsert.c_str(), callback, nullptr, &dataBase.errorMessage_);
			if (dataBase.rc_ != SQLITE_OK )
				dataBase.error("SQL error");
		}
	}
}

DataBase::~DataBase()
/*
	@det		Destructor of Database class, will close the connection and 
					print that in the logfile
	@param 		void
	@return 	void
*/
{
	if(!log_.is_open())
	{ // most probably log_ will be closed, cause c++ calls detructors in inverted orders
		ofstream log("logFile.txt", ios::out | ios::app); 
		log << "DataBase closed." << endl;
	}
	sqlite3_close(db_);
}