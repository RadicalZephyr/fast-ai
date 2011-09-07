#include "RoboticsBehaviour.h"
#include "UnitManager/Movement/ZealotWander.h"
#include "UnitManager/Movement/UnitGrouping.h"
#include "UnitManager/Movement/ObserverFollow.h"

void RoboticsBehaviour::postBuild(BWAPI::Unit *unit) {
   IUnitTrainingManagerBehaviour::postBuild(unit);
    new ObserverFollow(unit);
}

BWAPI::UnitType RoboticsBehaviour::shouldBuild(BWAPI::UnitType ) {
    if (g_resourceManager.gas() >= 75 && BWAPI::Broodwar->canMake(0, BWAPI::UnitTypes::Protoss_Observer) &&
      Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Observer) < m_maxObsCount) {

        return BWAPI::UnitTypes::Protoss_Observer;
    }
    else {
        return BWAPI::UnitTypes::None;
    }
}
