#include "UnitWander.h"
#include <random>

void UnitWander::onFrame(void) {
   static int timeout = 0;
    if (!m_unit->exists()) {
        //BWAPI::Broodwar->printf("Deleting zealot wanderer");
        delete this;
        return;
    }
    if (timeout++ < 3000) {

        if (m_attacking && !m_unit->isIdle()) {
            return;
        } else if (m_unit->isIdle()) {
            m_attacking = false;
            timeout = 0;
        }
    } else {
        timeout = 0;
    }
    BWAPI::Unit *enemy = nearestEnemy();
    if (enemy && enemy->isDetected()) {
   m_unit->attack(enemy->getPosition());
        m_attacking = true;
    } else if (m_unit->isIdle()) {
   m_visitedPositions.insert(m_unit->getPosition());
   m_unit->attack(newDestination());
    }
}

BWAPI::Position UnitWander::newDestination(void) {
    BWAPI::Position newPos(std::rand() % (BWAPI::Broodwar->mapWidth() * TILE_SIZE),
      std::rand() % (BWAPI::Broodwar->mapHeight() * TILE_SIZE));

    while (m_visitedPositions.find(newPos) != m_visitedPositions.end() && BWAPI::Broodwar->hasPath(m_unit->getPosition(), newPos)) {
        newPos = BWAPI::Position(std::rand() % BWAPI::Broodwar->mapWidth(),
          std::rand() % BWAPI::Broodwar->mapHeight());
    }
    return newPos;
}

BWAPI::Unit *UnitWander::nearestEnemy(void) {
   UnitSet units = BWAPI::Broodwar->enemy()->getUnits();
    return *units.begin();
}