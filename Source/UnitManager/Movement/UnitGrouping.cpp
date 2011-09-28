#include "UnitGrouping.h"
#include "UnitManager/Movement/UnitWander.h"

UnitGrouping::UnitGrouping(BWAPI::Unit *unit) : m_unit(unit), m_connection() {
    m_connection = Signal::onFrame().connect(boost::bind(&UnitGrouping::onFrame, this));
    m_rallyDestination = Broodwar->self()->getStartLocation().makeValid();
    m_minGroupSize = 10;
    m_defenseRadius = 750;
}

void UnitGrouping::onFrame(void) {
    if (!m_unit->exists()) {
        // BWAPI::Broodwar->printf("Unit has died");
        delete this;
        return;
    }

    BWAPI::Unit *enemy = visibleEnemy();

    int numSameUnits = Broodwar->self()->completedUnitCount(m_unit->getType());

    if (enemy && enemy->isDetected() && numSameUnits >= m_minGroupSize) {
        // BWAPI::Broodwar->printf("Attacking with a group");
        m_unit->attack(enemy->getPosition());

        while (!m_unit->isIdle()) {
        }

        SIGNAL_OFF_FRAME(UnitGrouping);
        m_connection.disconnect();

        new UnitWander(m_unit);
        // Broodwar->printf("This unit started wandering");
    }
    else if (enemy && enemy->isDetected() && enemy->getDistance(Position(Broodwar->self()->getStartLocation())) < m_defenseRadius) {
   BWAPI::Broodwar->printf("Defending Base");
   m_unit->attack(enemy->getPosition());

        SIGNAL_OFF_FRAME(UnitGrouping);
        m_connection.disconnect();

        new UnitWander(m_unit);
    }

}

BWAPI::Unit *UnitGrouping::visibleEnemy(void) {
   UnitSet units = BWAPI::Broodwar->enemy()->getUnits();
    return *units.begin();
}