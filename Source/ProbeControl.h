#pragma once

#include "Important/Common.h"
#include "DistanceSorter.h"
#include "Util/Timed.h"

using namespace BWAPI;

class ProbeControl
{
public:
	ProbeControl(BWAPI::Unit *newProbe);
    bool addProbe();
	bool inLocation();
	void nextLocation();


    /*void findMinerals(void);

    void onFrame(void);
	void onUnitCreate(Unit* unit);*/
private:
	BWAPI::Unit *myProbe;	
	std::set<TilePosition> & myTiles;
	std::set<TilePosition>::iterator it;
	ProbeControl& operator= (const ProbeControl&);

    /*void adjustRemainingFrames();
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
    NexusManager& operator=(const NexusManager&);*/
};