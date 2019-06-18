#include <iostream>
#include <string>

using namespace std;

class sqlite3_exception : public runtime_error
{
public:
	sqlite3_exception(const string& exceptionMessage) throw() : runtime_error(exceptionMessage), exceptionMessage_(exceptionMessage) {}
	virtual string what (const string& addsOn) const throw ()
	{
		return exception::what();
	}
	
protected:
    string exceptionMessage_;
};

class sqlite3_openError : public sqlite3_exception
{
public:
	sqlite3_openError(const string& exceptionMessage) : sqlite3_exception("DataBase open error " + exceptionMessage) {}	
};

class sqlite3_statementError : public sqlite3_exception
{
public:
	sqlite3_statementError(const string& exceptionMessage) : sqlite3_exception("DataBase stement prepration error " + exceptionMessage) {}	
};

class sqlite3_executionError : public sqlite3_exception
{
public:
	sqlite3_executionError(const string& exceptionMessage) : sqlite3_exception("DataBase execution error " + exceptionMessage) {}
};

class sqlite3_stepError : public sqlite3_exception
{
public:
	sqlite3_stepError(const string& exceptionMessage) : sqlite3_exception("DataBase step error " + exceptionMessage) {}
};