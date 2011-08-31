#include <BWAPI.h>
#include <set>
using namespace BWAPI;

bool pylonCheck()
{
   std::set<Unit*> buildings = BWAPI::Broodwar->self()->getUnits();
   std::set<Unit*>::iterator p;
   int foodneeded = 0;
    //for(unsigned int i = 0; i < buildings.size(); i++)
    for (p = buildings.begin(); p != buildings.end(); p++)
    {
        if ((*p)->getType().isBuilding())
        {
            if ((*p)->getRemainingTrainTime() <= BWAPI::UnitTypes::Protoss_Pylon.buildTime())
            {
                foodneeded += (*p)->getTrainingQueue().begin()->supplyRequired();
                //if ((*p)->getT
            }
            if ((*p)->getType() == BWAPI::UnitTypes::Protoss_Pylon && (*p)->isBeingConstructed()) //ProtossPylon
            {
                foodneeded -= BWAPI::UnitTypes::Protoss_Pylon.supplyProvided();
            }
        }
    }
    // BWAPI::Broodwar->printf("supplyused: %d    foodneeded: %d   supplytotal: %d",BWAPI::Broodwar->self()->supplyUsed(), foodneeded, BWAPI::Broodwar->self()->supplyTotal());
    if(BWAPI::Broodwar->self()->supplyUsed() + foodneeded > BWAPI::Broodwar->self()->supplyTotal())
    {
        return true;
    }
    return false;
}