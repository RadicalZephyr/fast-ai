#pragma once

#include <BWAPI.h>
#include <queue>

using namespace BWAPI;
using namespace std;

class SCResourceManager
{
public:
	//requests return a number that the client can use to check back and see when its request has been approved
	SCResourceManager(void);
	~SCResourceManager(void);

	int requestResources(int minerals, int gas); //Request the resources manager to allocate the given amount of resources
	int requestResources(BWAPI::UnitType requestedUnit, int count); //Request the resources manager to allocate the amount of resources required to build this unit count times
	int requestResources(BWAPI::UnitType requestedUnit); //Request the resources manager to allocate the resources to build this unit

	bool checkReady(int ID); //give your number and this function returns true if your request is ready
	void resourcesUsed(int ID); //when your request is ready, use the resources allocated and then call this function giving your number
private:

	struct Request
	{
		Request(int inID, int inmineralCost, int ingasCost):ID(inID),
			mineralCost(inmineralCost),
			gasCost(ingasCost)
		{
	
		}

		int ID;
		int mineralCost;
		int gasCost;
	};

	int generateIDCount;
	int generateID(); //generates an id for the client
	int allocatedMinerals; //total minerals that have been reserved
	int allocatedGas; //total gas that has been reserved

	queue<Request> requests; //active requests
	vector<Request> approved; //approved requests
	void checkResources(); //during every frame check if there are enough resources for the top of the queue
};