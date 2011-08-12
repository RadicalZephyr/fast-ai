#include "GatewayBehaviour.h"
#include "UnitManager/Movement/ZealotWander.h"

void GatewayBehaviour::postBuild(BWAPI::Unit *unit) {
	IUnitTrainingManagerBehaviour::postBuild(unit);
	new ZealotWander(unit);
}

BWAPI::UnitType GatewayBehaviour::shouldBuild(BWAPI::UnitType ) {
	if (BWAPI::Broodwar->self()->minerals() > 600 && BWAPI::Broodwar->canMake(0, BWAPI::UnitTypes::Protoss_Dragoon)) {
		return BWAPI::UnitTypes::Protoss_Dragoon;
	}

	return m_buildType;
}
