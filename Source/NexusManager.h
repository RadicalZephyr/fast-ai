#pragma once

#include "Important/Common.h"
#include "Function Objects/DistanceSorter.h"
#include "Util/Timed.h"

using BWAPI::Unit;

class NexusManager
{
public:
    NexusManager(Unit &theNexus);

    bool addMiner(Unit *probe);
    bool addGasser(Unit *probe);

    void findMinerals(void);

    void onFrame(void);
	void onUnitCreate(Unit* unit);
private:
    void adjustRemainingFrames();
	void checkTraining(void);
    void buildProbe(void);
    bool findBuiltProbe();

	const static int s_mineralDistance;

	const int c_unitTrainTime;
	Unit *m_trainingUnit;
	Timed m_trainingTime;

    // Want uniqueness and fast access, don't care about order
    UnitSet m_minGatherers;
    UnitSet m_gasGatherers;

    // minerals we don't care as much about uniqueness (should only be added once anyhow)
    // but ordering is nice (nearness to base)
    UnitList m_minerals;

    Unit *m_builder;
    Unit &m_nexus;

    // Not implemented to disallow assignment
    NexusManager& operator=(const NexusManager&);
};