#include "ResourceManager.h"
#include "Important/Common.h"
using namespace BWAPI;

ResourceManager::ResourceManager(void)
{
    generateIDCount = 0;
    Signal::onFrame().connect(boost::bind(&ResourceManager::checkResources,this));
}


ResourceManager::~ResourceManager(void)
{
}

//Request the resource manager to allocate the given resources
int ResourceManager::requestResources(int minerals, int gas, int priority)
{
    //make a request and add it to the queue
    Request newRequest(generateID(), minerals, gas);
    switch (priority)
    {
    case 1:
        priorityOne.push(newRequest);
        break;
    case 2:
        priorityTwo.push(newRequest);
        break;
    case 3:
        priorityThree.push(newRequest);
        break;
    case 4:
        priorityFour.push(newRequest);
        break;
    default:
        priorityFive.push(newRequest);
    }
    return newRequest.ID;
}

//Request the resource manager to allocate the resources required to build the count given of the unit type
int ResourceManager::requestResources(BWAPI::UnitType requestedUnit, int count, int priority)
{
    //call the more general version of request resources
    return requestResources(requestedUnit.mineralPrice() * count, requestedUnit.gasPrice() * count, priority);
}

//Request the resource manager to allocate the resources required to build a unit of this type
int ResourceManager::requestResources(BWAPI::UnitType requestedUnit, int priority)
{
    //call the more general version of request resources
    return requestResources(requestedUnit, 1, priority);
}

//Check the
void ResourceManager::checkResources()
{
    //approve from the top down, things on the queue wich can be afforded
    int totalMinerals = Broodwar->self()->minerals();
    int totalGas = Broodwar->self()->gas();
    totalMinerals -= allocatedMinerals;
    totalGas -= allocatedGas;
    bool done = false;



    //attempt to approve as many priority one items as possible
    while (!done)
    {
        //start with priority one items
        if (!priorityOne.empty())
        {
            //When there are priority one items check if they may be approved
            if ((priorityOne.front().mineralCost <= totalMinerals) && (priorityOne.front().gasCost <= totalGas))
            {
                totalMinerals -=priorityOne.front().mineralCost;
                allocatedMinerals += priorityOne.front().mineralCost;
                totalGas -= priorityOne.front().gasCost;
                allocatedGas += priorityOne.front().gasCost;
                approved.push_back(Request(priorityOne.front().ID, priorityOne.front().mineralCost, priorityOne.front().gasCost));
                priorityOne.pop();
            }
            else
            {
                //there are stil priority one items, do not approve anything else until they can be approved
                return;
            }
        }
        else
        {
            //check priority two items
            if (!priorityTwo.empty())
            {
                //when there are priority two items check if they may be approved
                if ((priorityTwo.front().mineralCost <= totalMinerals) && (priorityTwo.front().gasCost <= totalGas))
                {
                    totalMinerals -=priorityTwo.front().mineralCost;
                    allocatedMinerals += priorityTwo.front().mineralCost;
                    totalGas -= priorityTwo.front().gasCost;
                    allocatedGas += priorityTwo.front().gasCost;
                    approved.push_back(Request(priorityTwo.front().ID, priorityTwo.front().mineralCost, priorityTwo.front().gasCost));
                    priorityTwo.pop();
                }
                else
                {
                    //there are still priority two items, do not approve anything lower until they can be approved
                    return;
                }
            }
            else
            {
                //check priority three items
                if (!priorityThree.empty())
                {
                    //when there are priority two items check if they may be approved
                    if ((priorityThree.front().mineralCost <= totalMinerals) && (priorityThree.front().gasCost <= totalGas))
                    {
                        totalMinerals -=priorityThree.front().mineralCost;
                        allocatedMinerals += priorityThree.front().mineralCost;
                        totalGas -= priorityThree.front().gasCost;
                        allocatedGas += priorityThree.front().gasCost;
                        approved.push_back(Request(priorityThree.front().ID, priorityThree.front().mineralCost, priorityThree.front().gasCost));
                        priorityThree.pop();
                    }
                    else
                    {
                        //there are still priority Three items, do not approve anything lower until they can be approved
                        return;
                    }
                }
                else
                {
                    //check priority four items
                    if (!priorityFour.empty())
                    {
                        //when there are priority four items check if they may be approved
                        if ((priorityFour.front().mineralCost <= totalMinerals) && (priorityFour.front().gasCost <= totalGas))
                        {
                            totalMinerals -=priorityFour.front().mineralCost;
                            allocatedMinerals += priorityFour.front().mineralCost;
                            totalGas -= priorityFour.front().gasCost;
                            allocatedGas += priorityFour.front().gasCost;
                            approved.push_back(Request(priorityFour.front().ID, priorityFour.front().mineralCost, priorityFour.front().gasCost));
                            priorityFour.pop();
                        }
                        else
                        {
                            //there are still priority Four items, do not approve anything lower until they can be approved
                            return;
                        }
                    }
                    else
                    {
                        //Check priority five items
                        if (!priorityFive.empty())
                        {
                            //When there are priority five items, check if they may be approved
                            if ((priorityFive.front().mineralCost <= totalMinerals) && (priorityFive.front().gasCost <= totalGas))
                            {
                                totalMinerals -=priorityFive.front().mineralCost;
                                allocatedMinerals += priorityFive.front().mineralCost;
                                totalGas -= priorityFive.front().gasCost;
                                allocatedGas += priorityFive.front().gasCost;
                                approved.push_back(Request(priorityFive.front().ID, priorityFive.front().mineralCost, priorityFive.front().gasCost));
                                priorityFive.pop();
                            }
                            else
                            {
                                //there are still priority Five items, do not approve anything lower until they can be approved
                                return;
                            }
                        }
                        else
                        {
                            return; //there are no longer any items
                        }
                    }
                }
            }
        }
    }
}

//Generate an ID for a request, increment the value so future ID's are Unique
int ResourceManager::generateID()
{
    generateIDCount++;
    return generateIDCount;
}

//check if a request has been approved
bool ResourceManager::checkReady(int ID)
{
    for (unsigned int i = 0; i < approved.size(); i++)
    {
        if (ID == approved[i].ID)
        {
            return true;
        }
    }
    return false;
}

void ResourceManager::resourcesUsed(int ID)
{
    for (unsigned int i = 0; i < approved.size(); i++)
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