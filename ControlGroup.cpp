#include "ControlGroup.h"


ControlGroup::ControlGroup(void) {
	m_numUnits = 0;
}

ControlGroup::~ControlGroup(void) {

}

void ControlGroup::add(BWAPI::Unit *unit) {
	m_unitsInGroup.insert(unit);
	m_numUnits++;
}

void ControlGroup::remove(BWAPI::Unit *unit) {
	m_unitsInGroup.erase(unit);
	m_numUnits--;
}

void ControlGroup::attack(BWAPI::Unit *unit) {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->attack(unit);
	}
}

void ControlGroup::attack(BWAPI::Position destination) {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->attack(destination);
	}
}

void ControlGroup::move(BWAPI::Position destination) {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->move(destination);
	}
}

void ControlGroup::patrol(BWAPI::Position destination) {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->patrol(destination);
	}
}

void ControlGroup::stop() {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->stop();
	}
}

void ControlGroup::holdPosition() {
	UnitSet::iterator it;
	for (it = m_unitsInGroup.begin(); it != m_unitsInGroup.end(); ++it) {
		BWAPI::Unit *currentUnit;
		currentUnit = *it;
		currentUnit->holdPosition();
	}
}

int ControlGroup::unitCount() {
	return m_numUnits;
}