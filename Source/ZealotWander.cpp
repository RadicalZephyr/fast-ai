#include "ZealotWander.h"
#include <random>

void ZealotWander::onFrame(void) {
	if (!m_unit->getHitPoints() < 1) {
		BWAPI::Broodwar->printf("Deleting zealot wanderer");
		delete this;
		return;
	}
	
	if (m_attacking && !m_unit->isIdle()) {
		return;
	} else if (m_unit->isIdle()) {
		m_attacking = false;
	}

	BWAPI::Unit *enemy = nearestEnemy();
	if (enemy) {
		m_unit->attack(enemy);
		m_attacking = true;
	} else if (m_unit->isIdle()) {
		m_visitedPositions.insert(m_unit->getPosition());
		m_unit->attack(newDestination());
	}
}

BWAPI::Position ZealotWander::newDestination(void) {
	BWAPI::Position newPos(std::rand() % (BWAPI::Broodwar->mapWidth() * TILE_SIZE),
						   std::rand() % (BWAPI::Broodwar->mapHeight() * TILE_SIZE));

	while (m_visitedPositions.find(newPos) != m_visitedPositions.end() && BWAPI::Broodwar->hasPath(m_unit->getPosition(), newPos)) {
		newPos = BWAPI::Position(std::rand() % BWAPI::Broodwar->mapWidth(),
								 std::rand() % BWAPI::Broodwar->mapHeight());
	}
	return newPos;
}

BWAPI::Unit *ZealotWander::nearestEnemy(void) {
	UnitSet units = BWAPI::Broodwar->enemy()->getUnits();
	BWAPI::Broodwar->printf("number of enemy units: %d", units.size());
	return 0;
}