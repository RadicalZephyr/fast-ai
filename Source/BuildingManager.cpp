#include "BuildingManager.h"

using namespace BWAPI;

// Constant for how far away units can be from their training building
const int BuildingManager::c_buildDistance = 100;

BuildingManager::BuildingManager(Unit &theBuilding) :m_trainingUnit(0),
												     m_trainingTime(),
												     m_building(theBuilding),
												     m_shouldBuild(0) {


}

void BuildingManager::setShouldBuild(boolUnitFunc newPredicate) {
	m_shouldBuild = newPredicate;
}

void BuildingManager::buildUnit(UnitType buildType) {
	if (Broodwar->canMake(&m_building, buildType) &&
		(m_shouldBuild ? m_shouldBuild(buildType) : true)) {
			m_building.train(buildType);
			m_trainingUnit = 0;
	}
}

void BuildingManager::onFrame(void) {
    Broodwar->drawTextScreen(40, 40, "unitTraining isDone: %s\namountDone: %d", 
			(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone() );
	checkTraining();
}

void BuildingManager::onUnitCreate(Unit* unit) {
	if (m_building.isTraining() && !unit->isCompleted() &&
		m_building.getPosition().getApproxDistance(unit->getPosition()) < c_buildDistance) {
		Broodwar->printf("Inside unitcreate if");
		m_trainingUnit = unit;
		m_trainingTime.reset(unit->getType().buildTime());
	}
}

void BuildingManager::checkTraining(void) {
	if (m_trainingTime.isDone()) {


	}
}