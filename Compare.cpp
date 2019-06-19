#include "Compare.h"

void Compare::operator(map<string,Host*> recentScan, map<string, Host*>& fromDB) ()
{
    for(auto& currHost : container_)
	{
		if(currHost.first != "No Available MAC Adress")
		{
			auto hostInDB = dbHosts.find(currHost.first);
			if(hostInDB == dbHosts.end())
				log_ << currHost.first << " just joined the network using the following IP: " << currHost.second->getIp() << " ." << endl;
			else
				if(hostInDB->second->getModel() != currHost.second->getModel())
					log_ << "There's a problem with " << currHost.first << " model do not match information from database." << endl;
		}
	}
}