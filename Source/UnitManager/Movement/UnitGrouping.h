#pragma once

#include "Important/Common.h"

class UnitGrouping
{
public:
	UnitGrouping(BWAPI::Unit *unit);

	~UnitGrouping(void) { m_connection.disconnect(); }

	void onFrame(void);

private:
	BWAPI::Unit *m_unit;
	boost::signals::connection m_connection;

	BWAPI::TilePosition m_rallyDestination;
	BWAPI::TilePosition m_attackDestination(void);
	int m_minGroupSize;

	BWAPI::Unit *visibleEnemy(void);

};

