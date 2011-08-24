//This is a resource manager for all tasks that we perform. It is imperitive for this manager to be effective that it is used
//in every instance where we need resources. 

//The procedure is: When some part of the AI wants to build something...
//Call the requestResources function and give it the number of resources needed(or a unit type and number of requested units)
//as well as a priority so the resource manger knows how important the request is.
//The requestResources function will return an integer wich is your callback number.
//When you want to check if your request has been approved call check ready and give your callback number.
//After your request has been approved, please use the resourcesUsed function immedately after you use the resources so
//the manager will know that it doesnt need to hold those resources anymore.
//FREEING UP RESOURCES WITH RESOURCESUSED IS VERY IMPORTANT!!!


#pragma once

#include <BWAPI.h>
#include <queue>

using namespace BWAPI;
using namespace std;

class ResourceManager
{
public:
	//requests return a number that the client can use to check back and see when its request has been approved
	ResourceManager(void);
	~ResourceManager(void);

	//Request the resources manager to allocate the given amount of resources
	int requestResources(int minerals, int gas, int priority); 
	int requestResources(BWAPI::UnitType requestedUnit, int count, int priority);
	int requestResources(BWAPI::UnitType requestedUnit, int priority);

	bool checkReady(int ID); //give your number and this function returns true if your request is ready
	void resourcesUsed(int ID); //when your request is ready, use the resources allocated and then call this function giving your number

	int minerals(void) {return Broodwar->self()->minerals() - allocatedMinerals;}
	int gas(void) {return Broodwar->self()->gas() - allocatedGas;}
private:
	//Structure wich represents a request for resources
	struct Request
	{
		Request(int inID, int inmineralCost, int ingasCost):ID(inID),
															mineralCost(inmineralCost),
															gasCost(ingasCost) {}
		int ID;
		int mineralCost;
		int gasCost;
	};

	int generateIDCount;
	int generateID(); //generates an id for the client
	int allocatedMinerals; //total minerals that have been reserved
	int allocatedGas; //total gas that has been reserved

	queue<Request> priorityOne; //highest priority
	queue<Request> priorityTwo; //second
	queue<Request> priorityThree; //third
	queue<Request> priorityFour; //fourth
	queue<Request> priorityFive; //fifth
	vector<Request> approved; //approved requests
	void checkResources(); //during every frame check if there are enough resources for the top of the queue
};