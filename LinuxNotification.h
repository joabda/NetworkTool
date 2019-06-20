#pragma once

#include "Host.h"
using namespace std;

class LinuxNotifyManager
{
public:
    LinuxNotifyManager();
    bool notifyEvent(Host* newHost) const;
    ~LinuxNotifyManager() {}

private:
    string baseCommand_;
    string hostInfos(Host* newHost) const;
};