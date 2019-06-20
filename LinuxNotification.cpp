#include "LinuxNotification.h"

LinuxNotifyManager::LinuxNotifyManager(const string& imagePath, const string& appName)
/*
	@det 		Constructor of a Notification (default values available for both arguments)
	@param 		string  Path to an image 
                string  Application's namee
	@return 	void
*/
{
    baseCommand_ = "notify-send ";
    imagePath_ = imagePath;
    appName_ = appName;
}

string LinuxNotifyManager::addHostInfos(Host* newHost) const
/*
	@det 		Adding a host's informations to the notification's body
	@param 		Host*   host that will be showed 
	@return 	void
*/
{
    return QUOTE + "<b>" + newHost->getMacAdress() + "</b>" +
        " joined under ip: " + newHost->getIp() + QUOTE + " ";
}

string LinuxNotifyManager::addImage()
/*
	@det 		Adding a an image to the notification
	@param 		void
	@return 	void
*/
{
    system("pwd > currentDirectory.txt");
    ifstream pathFile("currentDirectory.txt");
    pathFile >> imagePath_;
    imagePath_ += "/warning.png";
	system("rm currentDirectory.txt");
    return "-i " + imagePath_ + " ";
}

string LinuxNotifyManager::addAppName() const
/*
	@det 		Adding the application's name
	@param 		void
	@return 	void
*/
{
    return "-a " + QUOTE + appName_ + QUOTE + " ";
}

bool LinuxNotifyManager::notifyEvent(Host* newHost)
/*
	@det 		Create the notification and execute it 
	@param 		Host*   host that will be showed 
	@return 	bool    true if executed successfully, else: false
*/
{
    string fullCommand = baseCommand_;
    fullCommand += QUOTE + "New Device on Network" + QUOTE + " ";
    fullCommand += addHostInfos(newHost);
    fullCommand += addImage();
    fullCommand += addAppName();

    int systemReturn = system( fullCommand.c_str() );

    if (WIFEXITED(systemReturn))
        return true;
    return false;
}