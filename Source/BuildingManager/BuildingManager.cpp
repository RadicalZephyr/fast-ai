#include "BuildingManager.h"

using namespace BWAPI;

// Constant for how far away units can be from their training building
const int BuildingManager::c_buildDistance = 100;

bool BuildingManager::buildUnit(UnitType buildType) {
	if (Broodwar->canMake(&m_building, buildType) && m_behaviour &&
		m_behaviour->shouldBuild(buildType)) {
			m_building.train(buildType);
			m_trainingUnit = 0;
            return true;
    } else {
        return false;
    }
}

void BuildingManager::onFrame(void) {
	checkTraining();
}

void BuildingManager::onUnitCreate(Unit* unit) {
	if (m_building.isTraining() && unit && !unit->isCompleted() &&
		m_building.getPosition().getApproxDistance(unit->getPosition()) < c_buildDistance) {
		Broodwar->printf("Inside unitcreate if");
		m_trainingUnit = unit;
		m_trainingTime.reset(unit->getType().buildTime());
	}
}

void BuildingManager::checkTraining(void) {
	if (m_building.isTraining() && m_trainingUnit && 
		m_trainingTime.isDone()) {
		if (m_behaviour) {
			m_behaviour->postBuild(m_trainingUnit);
		}
        m_trainingUnit = 0;
	} else if (!m_building.isTraining()) {
		if (m_trainingType) {
			buildUnit(m_trainingType);
		} else {
			m_trainingType = m_behaviour->setBuildType();
		}
	}
}

void BuildingManager::printDebug(void) {
    Broodwar->drawTextMap(m_building.getPosition().x()+30, m_building.getPosition().y()+30, 
							"trainingType: %s\nunitTraining isDone: %s\namountDone: %d",
							(m_trainingType ? m_trainingType.getName().c_str() : "none"),
							(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone());
}

bool BuildingManager::isMyUnitSelected(void) {
    return m_building.isSelected();
}