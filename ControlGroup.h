#pragma once

#include "Important/Common.h"

class ControlGroup
{
public:
	ControlGroup(void);
	~ControlGroup(void);

	void add(BWAPI::Unit *unit);
	void remove(BWAPI::Unit *unit);
	void attack(BWAPI::Unit *unit);
	void attack(BWAPI::Position destination);
	void move(BWAPI::Position destination);
	void patrol(BWAPI::Position destination);
	void stop();
	void holdPosition();
	int unitCount();

private:
	UnitSet m_unitsInGroup;
	int m_numUnits;
};

