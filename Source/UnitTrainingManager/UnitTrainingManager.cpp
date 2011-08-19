#include "UnitTrainingManager.h"

using namespace BWAPI;

// Constant for how far away units can be from their training building
const int UnitTrainingManager::c_buildDistance = 115;


// Public methods, only meant to be called via the signals the class registers for at construction

void UnitTrainingManager::onFrame(void) {
	if (m_building.isCompleted()) {
		checkTraining();
	}
}

void UnitTrainingManager::onUnitCreate(Unit* unit) {
	if (m_building.isTraining() && unit && !unit->isCompleted() && unit->getType() == m_lastType &&
		m_building.getPosition().getApproxDistance(unit->getPosition()) < c_buildDistance) {
		m_trainingUnit = unit;
		m_trainingTime.reset(unit->getType().buildTime());
    m_unitConnection.block();
	}
}


// Private methods

bool UnitTrainingManager::buildUnit(void) {
	if (Broodwar->canMake(&m_building, m_trainingType) && m_behaviour &&
		checkShouldBuild() != UnitTypes::None) {
			m_building.train(m_trainingType);
			m_trainingUnit = 0;
      m_lastType = m_trainingType;
      m_unitConnection.unblock();
      return true;
    } else {
      return false;
    }
}

void UnitTrainingManager::checkTraining(void) {
	if (m_trainingType != UnitTypes::None && m_trainingUnit && 
		m_building.isTraining() && m_trainingTime.isDone()) {
		if (m_behaviour) {
			m_behaviour->postBuild(m_trainingUnit);
		}
        m_trainingUnit = 0;
	} else if (!m_building.isTraining()) {
		if (m_trainingType != UnitTypes::None) {
			buildUnit();
		} else {
			checkShouldBuild();
		}
	}
}

void UnitTrainingManager::printDebug(void) {
    Broodwar->drawTextMap(m_building.getPosition().x()+55, m_building.getPosition().y()+30, 
							"\x03trainingType: \x04%s \x03 \nunitTraining isDone: \x04%s \x03 \namountDone: \x04%d",
							(m_trainingType ? m_trainingType.getName().c_str() : "none"),
							(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone());
    Broodwar->drawCircleMap(m_building.getPosition().x(), m_building.getPosition().y(), c_buildDistance, BWAPI::Colors::White);
}

bool UnitTrainingManager::isMyUnitSelected(void) {
    return m_building.isSelected();
}
