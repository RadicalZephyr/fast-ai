#pragma once

#include "Important/Common.h"
#include "FunctionObjects/DistanceSorter.h"
#include "Util/Timed.h"

using namespace BWAPI;

class ProbeControl
{
public:
	ProbeControl(BWAPI::Unit *newProbe);

private:
	void onFrame();

	BWAPI::Unit *m_probe;
	std::set<TilePosition>::const_iterator m_scoutLocations;
	ProbeControl& operator= (const ProbeControl&);
};
