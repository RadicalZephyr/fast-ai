#include "BaseManager.h"
#include "Util/Functions.h"
#include "Util/RelativeSide.h"
#include <random>


using namespace BWAPI;

// Public function for other modules requesting that the basemanager queue a building to be built
// internal queueing mechanism is simple FIFO
// This is probably ripe for generalization (i.e. we could implement a whole set of classes with a
//   abstract base that could be used interchangeably to change the behaviour of the buildingmaneger's queueing)
bool BaseManager::constructBuilding(BWAPI::UnitType type) {
	m_buildQueue.push(type);
	if (m_probe == NULL)
	{
		//setDebugSpeed(false);
		m_lastTilePos = BWAPI::Broodwar->self()->getStartLocation();
		m_probe = m_controllee->removeProbe();
		m_probe->move(Position(Broodwar->self()->getStartLocation()));
	}
	return true;
}

void BaseManager::onFrame(void) {
	
	if (!m_buildQueue.empty() && m_probe && !m_probe->isConstructing()) 
	{
		BWAPI::Broodwar->printf("1");
		doBuildCheck();

	} else if (BWAPI::Broodwar->self()->supplyTotal() < 400 && m_buildQueue.empty() && pylonCheck() && g_resourceManager.minerals() >= 100)
	{
		BWAPI::Broodwar->printf("2");
		m_buildQueue.push(BWAPI::UnitTypes::Protoss_Pylon);
	}
	else if (m_buildQueue.empty() && g_resourceManager.minerals() > 500)
	{
		BWAPI::Broodwar->printf("3");
		m_buildQueue.push(BWAPI::UnitTypes::Protoss_Gateway);
	}




	//else if (m_buildQueue.empty() && m_probe && !m_probe->isConstructing() && g_resourceManager.minerals() > 200) {
	//	if (Broodwar->self()->supplyTotal() - 7 >= Broodwar->self()->supplyUsed()) {
	//		m_buildQueue.push(BWAPI::UnitTypes::Protoss_Pylon);
	//	} else {
	//		m_buildQueue.push(BWAPI::UnitTypes::Protoss_Gateway);
	//	}
}		/*else if (m_probe && !m_probe->isConstructing()) {  // This section is supposed to keep the 'building' probe from sitting idle
		m_controllee->addProbe(m_probe);                    //  sending it back to work when there's no buildings in the queue
		m_probe = 0;
		}*/


// The building list should probably be a type-keyed multiMap
//  and/or we should generalize that part too
void BaseManager::onUnitCreate(BWAPI::Unit *unit) {
	if (unit->getTilePosition().getDistance(m_lastTilePos) < 1.0 && m_buildQueue.front() == unit->getType()) {
		m_buildQueue.pop();
		m_lastBuildings.push_back(unit);
	}
}

bool BaseManager::doBuildCheck(void) {
	UnitType type = m_buildQueue.front();

	return m_probe->build(m_lastTilePos = getRandomBuildPos(type), type);
}


// This is another piece that could do with some generalization or extension
//  could have it's own section of different objects that can be plugged in to
//  the base manager to provide the location of the next building to be built
TilePosition BaseManager::getRandomBuildPos(BWAPI::UnitType type) {
	TilePosition newPos;
	RelativeSide* placer;

	if (m_lastBuildings.empty()) {
		// Create a first building in the area
		placer = new RelativeSide(m_controllee->getNexus());
	} else {
		Unit* last = m_lastBuildings[std::rand() % m_lastBuildings.size()];
		placer = new RelativeSide(last);
	}

	int i = 0;

	while (i++ < 5) {
		switch (std::rand() % 4) {
		case 0:
			if (placer->CheckAndPlace(type, RelativeSide::Top | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, (std::rand() % 3) + 1, 0, newPos))
				break;
		case 1:
			if (placer->CheckAndPlace(type, RelativeSide::Left | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, (std::rand() % 3) + 1, 0, newPos))
				break;
		case 2:
			if (placer->CheckAndPlace(type, RelativeSide::Bottom | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, (std::rand() % 3) + 1, 0, newPos))
				break;
		case 3:
			if (placer->CheckAndPlace(type, RelativeSide::Right | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, (std::rand() % 3) + 1, 0, newPos))
				break;
			continue;
		default:
			break;
		}
		break;
	}

	delete placer;

	return newPos;
}
