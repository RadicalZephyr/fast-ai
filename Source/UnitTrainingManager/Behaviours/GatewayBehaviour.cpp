#include "GatewayBehaviour.h"
#include "UnitManager/Movement/UnitWander.h"
#include "UnitManager/Movement/UnitGrouping.h"

void GatewayBehaviour::postBuild(BWAPI::Unit *unit) {
   IUnitTrainingManagerBehaviour::postBuild(unit);
    if (std::rand() % 10 == 1) {
        // Broodwar->printf("Unit Wanderer Created");
        new UnitWander(unit);
    }
    else {
        // Broodwar->printf("Unit Grouper Created");
        new UnitGrouping(unit);
    }
}

BWAPI::UnitType GatewayBehaviour::shouldBuild(BWAPI::UnitType ) {
    if (g_resourceManager.gas() > 50 && BWAPI::Broodwar->canMake(0, BWAPI::UnitTypes::Protoss_Dragoon)) {
        return BWAPI::UnitTypes::Protoss_Dragoon;
    }

    return m_buildType;
}
