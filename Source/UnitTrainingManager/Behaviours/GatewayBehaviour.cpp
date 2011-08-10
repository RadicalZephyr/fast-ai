#include "GatewayBehaviour.h"
#include "ZealotWander.h"

void GatewayBehaviour::postBuild(BWAPI::Unit *unit) {
	IUnitTrainingManagerBehaviour::postBuild(unit);
	new ZealotWander(unit);
}

BWAPI::UnitType GatewayBehaviour::shouldBuild(BWAPI::UnitType ) {
	return m_buildType;
}
