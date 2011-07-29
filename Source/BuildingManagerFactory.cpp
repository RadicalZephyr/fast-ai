#include "BuildingManagerFactory.h"
#include "BuildingManager.h"

using namespace BWAPI;

BuildingManagerFactory::BuildingManagerFactory(void) {

}


BuildingManagerFactory::~BuildingManagerFactory(void) {

}

void BuildingManagerFactory::onUnitCreate(Unit* unit) {

	UnitType type(unit->getType());

	if (type.canProduce()) {
		if (type.isResourceDepot()) {

		} else if (type.isRefinery()) {

		}
	}
}