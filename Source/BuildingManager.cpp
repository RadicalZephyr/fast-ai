#include "BuildingManager.h"

using namespace BWAPI;

// Constant for how far away units can be from their training building
const int BuildingManager::c_buildDistance = 100;

bool BuildingManager::buildUnit(UnitType buildType) {
	if (Broodwar->canMake(&m_building, buildType) &&
		(m_shouldBuild ? m_shouldBuild(buildType) : true)) {
			m_building.train(buildType);
			m_trainingUnit = 0;
            return true;
    } else {
        return false;
    }
}

void BuildingManager::onFrame(void) {
    doFrame();
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

void BuildingManager::onSendText(std::string text) {
    doSendText(text);
}

void BuildingManager::checkTraining(void) {
	if (m_trainingTime.isDone()) {
        if (m_postBuild) {
            m_postBuild(m_trainingUnit);
        }
        m_trainingUnit = 0;
	}
}

void BuildingManager::printDebug(void) {
    Broodwar->drawTextScreen(40, 40, "unitTraining isDone: %s\namountDone: %d", 
			(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone() );
}

bool BuildingManager::isMyUnitSelected(void) {
    return m_building.isSelected();
}