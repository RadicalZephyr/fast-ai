#include "DefaultBehaviour.h"

void DefaultBehaviour::postBuild(BWAPI::Unit *) {
	BWAPI::Broodwar->printf("postBuild of DefaultBehaviour");
}

bool DefaultBehaviour::shouldBuild(BWAPI::UnitType ) {
	return true;
}

BWAPI::UnitType DefaultBehaviour::setBuildType(void) {
	UnitTypeSet buildSet = BWAPI::buildsWhat(m_building.getType());

	for (UnitTypeSet::iterator itr = buildSet.begin();
			itr != buildSet.end(); ++itr) {
		if (BWAPI::Broodwar->canMake(&m_building, *itr)) {
			return *itr;
		}
	}
}