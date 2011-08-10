#include "GatewayBehaviour.h"
#include "ZealotWander.h"
#include "ZealotGroup.h"

void GatewayBehaviour::postBuild(BWAPI::Unit *unit) {
	IUnitTrainingManagerBehaviour::postBuild(unit);
	ZealotWanderPtr newZealot(new ZealotWander(unit));
	g_zealotControl().add(newZealot);
	newZealot->setSelf(newZealot);
}

BWAPI::UnitType GatewayBehaviour::shouldBuild(BWAPI::UnitType ) {
	if (BWAPI::Broodwar->self()->minerals() > 600 && BWAPI::Broodwar->canMake(0, BWAPI::UnitTypes::Protoss_Dragoon)) {
		return BWAPI::UnitTypes::Protoss_Dragoon;
	}

	return m_buildType;
}
