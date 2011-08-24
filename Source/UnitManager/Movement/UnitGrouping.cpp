#include "UnitGrouping.h"
#include "UnitManager/Movement/ZealotWander.h"

UnitGrouping::UnitGrouping(BWAPI::Unit *unit) : m_unit(unit), m_connection() {
  m_connection = Signal::onFrame().connect(boost::bind(&UnitGrouping::onFrame, this));
	m_rallyDestination = Broodwar->self()->getStartLocation().makeValid();
	m_minGroupSize = 10;
}

void UnitGrouping::onFrame(void) {
	if (!m_unit->isVisible() && m_unit->getHitPoints() < 0) {
		//BWAPI::Broodwar->printf("Unit has died");
		delete this;
		return;
	}

	BWAPI::Unit *enemy = visibleEnemy();

	int numSameUnits = Broodwar->self()->completedUnitCount(m_unit->getType());

	if (enemy && numSameUnits >= m_minGroupSize) {
		// BWAPI::Broodwar->printf("Attacking with a group");
		m_unit->attack(enemy->getPosition());

		while (!m_unit->isIdle()) {
		}

		SIGNAL_OFF_FRAME(UnitGrouping);
		m_connection.disconnect();
				
		new ZealotWander(m_unit);
		// Broodwar->printf("This unit started wandering");
	}

}

BWAPI::Unit *UnitGrouping::visibleEnemy(void) {
	UnitSet units = BWAPI::Broodwar->enemy()->getUnits();
	return *units.begin();
}