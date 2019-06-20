#include "LinuxNotification.h"

LinuxNotifyManager::LinuxNotifyManager(const string& imagePath, const string& appName)
{
    baseCommand_ = "notify-send ";
    imagePath_ = imagePath;
    appName_ = appName;
}

string LinuxNotifyManager::addHostInfos(Host* newHost) const
{
    return QUOTE + "<b>" + newHost->getMacAdress() + "</b>" +
        " joined under ip: " + newHost->getIp() + QUOTE + " ";
}

string LinuxNotifyManager::addImage()
{
    system("pwd > currentDirectory.txt");
    ifstream pathFile("currentDirectory.txt");
    pathFile >> imagePath_;
    imagePath_ += "/warning.png";
	system("rm currentDirectory.txt");
    return "-i " + imagePath_ + " ";
}

string LinuxNotifyManager::addAppName() const
{
    return "-a " + QUOTE + appName_ + QUOTE + " ";
}

bool LinuxNotifyManager::notifyEvent(Host* newHost)
{
    string fullCommand = baseCommand_;
    fullCommand += QUOTE + "New Device on Network" + QUOTE + " ";
    fullCommand += addHostInfos(newHost);
    //if(imagePath_ != "NULL")
    fullCommand += addImage();
    fullCommand += addAppName();

    int systemReturn = system( fullCommand.c_str() );

    if (WIFEXITED(systemReturn))
        return true;
    return false;
}