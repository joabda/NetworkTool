#include "LinuxNotification.h"

LinuxNotifyManager::LinuxNotifyManager()
{
    baseCommand_ = "notify-send ";
}

string LinuxNotifyManager::hostInfos(Host* newHost) const
{
    return '"' + newHost->getMacAdress() + " joined under ip: " + newHost->getIp() + '"' + "\n";
}

bool LinuxNotifyManager::notifyEvent(Host* newHost) const
{
    system( (baseCommand_+hostInfos(newHost) ).c_str() );
    
    // "Make sur the process is done"
    return  true;
}

