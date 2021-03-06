#pragma once

#include <fstream>
#include "Host.h"
using namespace std;

static string QUOTE = "\"";

class LinuxNotifyManager
{
public:
    LinuxNotifyManager(const string& imagePath = "NULL", const string& appName = "NetworkTool");
    bool notifyEvent(Host* newHost);
    ~LinuxNotifyManager() {}

private:
    string baseCommand_;
    string imagePath_;
    string appName_;
    string addHostInfos(Host* newHost) const;
    string addImage();
    string addAppName() const;
};