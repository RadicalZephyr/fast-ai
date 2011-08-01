#include "UnitTrainingManager.h"

using namespace BWAPI;

// Constant for how far away units can be from their training building
const int UnitTrainingManager::c_buildDistance = 100;

bool UnitTrainingManager::buildUnit(UnitType buildType) {
	if (Broodwar->canMake(&m_building, buildType) && m_behaviour &&
		m_behaviour->shouldBuild(buildType)) {
			m_building.train(buildType);
			m_trainingUnit = 0;
            return true;
    } else {
        return false;
    }
}

void UnitTrainingManager::onFrame(void) {
	if (m_building.isCompleted()) {
		checkTraining();
	}
}

void UnitTrainingManager::onUnitCreate(Unit* unit) {
	if (m_building.isTraining() && unit && !unit->isCompleted() &&
		m_building.getPosition().getApproxDistance(unit->getPosition()) < c_buildDistance) {
		m_trainingUnit = unit;
		m_trainingTime.reset(unit->getType().buildTime());
	}
}

void UnitTrainingManager::checkTraining(void) {
	if (m_trainingType != BWAPI::UnitTypes::None && m_trainingUnit && 
		m_building.isTraining() && m_trainingTime.isDone()) {
		if (m_behaviour) {
			m_behaviour->postBuild(m_trainingUnit);
		}
        m_trainingUnit = 0;
	} else if (!m_building.isTraining()) {
		if (m_trainingType != BWAPI::UnitTypes::None) {
			buildUnit(m_trainingType);
		} else {
			m_trainingType = m_behaviour->setBuildType();
		}
	}
}

void UnitTrainingManager::printDebug(void) {
    Broodwar->drawTextMap(m_building.getPosition().x()+30, m_building.getPosition().y()+30, 
							"trainingType: %s\nunitTraining isDone: %s\namountDone: %d",
							(m_trainingType ? m_trainingType.getName().c_str() : "none"),
							(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone());
}

bool UnitTrainingManager::isMyUnitSelected(void) {
    return m_building.isSelected();
}
