#include "StandardPlay.h"
#include "BaseManager\BaseManager.h"

void CheeseStrategies::StandardPlay::onFrame() {
	
}

void CheeseStrategies::StandardPlay::init() {
	BaseManagerSet::iterator first = g_baseManagers.begin();
	m_base = *first;

	startBuilding();
}

void CheeseStrategies::StandardPlay::startBuilding() {
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Assimilator);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Cybernetics_Core);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
	m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
}