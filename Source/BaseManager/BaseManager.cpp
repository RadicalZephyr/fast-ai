#include "BaseManager.h"
#include "Util/RelativeSide.h"
#include <random>

using namespace BWAPI;

bool BaseManager::constructBuilding(BWAPI::UnitType type) {
	m_buildQueue.push(type);
	return true;
}

void BaseManager::onFrame(void) {
	if (!m_buildQueue.empty() && m_probe && !m_probe->isConstructing()) {
		doBuildCheck();

	} /*else if (m_probe && !m_probe->isConstructing()) {
		m_controllee->addProbe(m_probe);
		m_probe = 0;
	}*/
}


void BaseManager::onUnitCreate(BWAPI::Unit *unit) {
	if (unit->getPosition() == m_lastTilePos) {
		m_buildQueue.pop();
		m_lastBuilding = unit;
	}
}

bool BaseManager::doBuildCheck(void) {
	UnitType type = m_buildQueue.front();

	if (m_lastBuilding == 0) {
		// Create a first building in the area
		return m_probe->build(m_lastTilePos = getRandomBuildPos(m_controllee->getNexus(), type), type);
	} else {
		return m_probe->build(m_lastTilePos = getRandomBuildPos(m_lastBuilding, type), type);
	}
	return false;
}

TilePosition BaseManager::getRandomBuildPos(BWAPI::Unit *refUnit, BWAPI::UnitType type) {
	RelativeSide placer(refUnit);
	TilePosition newPos;
	int i = 0;

	while (i < 5) {
		switch (std::rand() % 4) {
		case 0:
			if (placer.CheckAndPlace(type, RelativeSide::Top | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, std::rand() % 3, 0, newPos))
				break;
		case 1:
			if (placer.CheckAndPlace(type, RelativeSide::Left | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, std::rand() % 3, 0, newPos))
				break;
		case 2:
			if (placer.CheckAndPlace(type, RelativeSide::Left | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, std::rand() % 3, 0, newPos))
				break;
		case 3:
			if (placer.CheckAndPlace(type, RelativeSide::Left | RelativeSide::OrthoLineCenter | RelativeSide::CenterOnOrthoLine, std::rand() % 3, 0, newPos))
				break;
			continue;
		default:
			break;
		}
		break;
	}
	Broodwar->printf("randomPos: (%d, %d)", newPos.x(), newPos.y());
	return newPos;
}
