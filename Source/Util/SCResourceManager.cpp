#include "SCResourceManager.h"
#include "Important/Common.h"
using namespace BWAPI;

SCResourceManager::SCResourceManager(void)
{
	generateIDCount = 0;
	Signal::onFrame().connect(boost::bind(&SCResourceManager::checkResources ,this));
}


SCResourceManager::~SCResourceManager(void)
{
}

//Request the resource manager to allocate the given resources
int SCResourceManager::requestResources(int minerals, int gas)
{
	//make a request and add it to the queue
	Request newRequest(generateID(), minerals, gas);
	requests.push(newRequest);
	return newRequest.ID;
}

//Request the resource manager to allocate the resources required to build the count given of the unit type
int SCResourceManager::requestResources(BWAPI::UnitType requestedUnit, int count)
{
	//call the more general version of request resources
	return requestResources(requestedUnit.mineralPrice() * count, requestedUnit.gasPrice() * count);
}

//Request the resource manager to allocate the resources required to build a unit of this type
int SCResourceManager::requestResources(BWAPI::UnitType requestedUnit)
{
	//call the more general version of request resources
	return requestResources(requestedUnit, 1);
}

//Check the 
void SCResourceManager::checkResources()
{
	//approve from the top down, things on the queue wich can be afforded
	int totalMinerals = Broodwar -> self() -> minerals();
	int totalGas = Broodwar -> self() -> gas();
	totalMinerals -= allocatedMinerals;
	totalGas -= allocatedGas;
	bool done = false;
	while (!done)
	{
		if (requests.empty())
			done = true;

		if ((requests.front().mineralCost <= totalMinerals) && (requests.front().gasCost <= totalGas))
		{
			totalMinerals -= requests.front().mineralCost;
			allocatedMinerals += requests.front().mineralCost;
			totalGas -= requests.front().gasCost;
			allocatedGas += requests.front().gasCost;
			approved.push_back(Request(requests.front().ID, requests.front().mineralCost, requests.front().gasCost));
			requests.pop();
		}
	}
}

//Generate an ID for a request, increment the value so future ID's are Unique
int SCResourceManager::generateID()
{
	generateIDCount++;
	return generateIDCount;
}

//check if a request has been approved
bool SCResourceManager::checkReady(int ID)
{
	for (int i = 0; i < approved.size(); i++)
	{
		if (ID == approved[i].ID)
		{
			return true;
		}
	}
	return false;
}

void SCResourceManager::resourcesUsed(int ID)
{
	for (int i = 0; i < approved.size(); i++)
	{
		if (ID == approved[i].ID)
		{
			allocatedMinerals -= approved[i].mineralCost;
			allocatedGas -= approved[i].gasCost;
			approved.erase(approved.begin()+i);
			return;
		}
	}
}