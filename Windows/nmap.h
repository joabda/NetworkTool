#pragma once

#pragma region "Inclusions" //{

#include "Utility.h"
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#pragma endregion //}

#pragma region "D�clarations" //{

#pragma region "Globaux" //{

void findSubnetIp(ostream &log, string& ip);

void nmap(ostream &log, string& ip);

#pragma endregion //}

#pragma endregion //}