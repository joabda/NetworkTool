#pragma once

#include "DataBase.h"

class Compare
{
    Compare() = delete;
    void operator() (map<string,Host*> recentScan, map<string, Host*>& fromDB);
    ~Compare() {}
};