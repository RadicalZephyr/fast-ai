#include "ZealotWander.h"
#include <random>

void ZealotWander::onFrame(void) {
	if (!m_unit->isVisible()) {
		BWAPI::Broodwar->printf("Deleting zealot wanderer");
		delete this;
	} else if (m_unit->isAttacking()) {
		;
	} else if (!m_unit->isMoving()) {
		m_unit->attack(newDestination());
	} else {
		m_visitedPositions.insert(m_unit->getPosition());
	}
}

BWAPI::Position ZealotWander::newDestination(void) {
	BWAPI::Position newPos(std::rand() % BWAPI::Broodwar->mapWidth(),
						   std::rand() % BWAPI::Broodwar->mapHeight());

	while (m_visitedPositions.find(newPos) != m_visitedPositions.end() && BWAPI::Broodwar->hasPath(m_unit->getPosition(), newPos)) {
		newPos = BWAPI::Position(std::rand() % BWAPI::Broodwar->mapWidth(),
								 std::rand() % BWAPI::Broodwar->mapHeight());
	}
	return newPos;
}
