#pragma once
#include "Important\Common.h"

using BWAPI::Unit;

class NexusFunc {
public:
	NexusFunc(Unit &nexus);

	void operator()(Unit *unit);
	bool operator()(BWAPI::UnitType);

	void setShouldBuild(bool newFlag) {m_shouldBuild = newFlag;}

private:
	void findMinerals(void);

    bool addMiner(Unit *probe);
    bool addGasser(Unit *probe);
	bool NexusFunc::addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList);

	const static int s_mineralDistance;

	Unit &m_nexus;

	UnitList m_gas;
	UnitList m_minerals;

	UnitSet m_minGatherers;
	UnitSet m_gasGatherers;

	bool m_shouldBuild;

	// Not implemented to disallow assignment
	// and default construction
	NexusFunc(void);
	NexusFunc(NexusFunc &rhs);
	NexusFunc &operator=(NexusFunc &rhs);
};