#include "DefaultBehaviour.h"

void DefaultBehaviour::postBuild(BWAPI::Unit *) {
   BWAPI::Broodwar->printf("DefBehaviour: postBuild");
}

BWAPI::UnitType DefaultBehaviour::shouldBuild(BWAPI::UnitType ) {
   BWAPI::Broodwar->printf("DefBehaviour: shouldBuild");
    if (m_canBuildList.empty()) {
   UnitTypeSet buildSet = BWAPI::buildsWhat(m_building->getType());
   m_canBuildList.assign(buildSet.begin(), buildSet.end());
    }

    for (UnitTypeList::iterator itr = m_canBuildList.begin();
      itr != m_canBuildList.end(); ++itr) {
        if (BWAPI::Broodwar->canMake(m_building, *itr)) {
            return *itr;
        }
    }
    return BWAPI::UnitTypes::None;
}
