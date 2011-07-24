#pragma once

#include "Important/Common.h"
#include "DistanceSorter.h"

using BWAPI::Unit;

class NexusManager
{
public:
    NexusManager(Unit &theNexus);

    bool addMiner(Unit *probe);
    bool addGasser(Unit *probe);

    void findMinerals(void);

    void onFrame(void);
private:
    void adjustRemainingFrames();
    void buildProbe();
    bool findBuiltProbe();

    int remainingBuildFrames;
    bool lookingForProbe;
    bool building;
    // Want uniqueness and fast access, don't care about order
    UnitSet minGatherers;
    UnitSet gasGatherers;

    // minerals we don't care as much about uniqueness (should only be added once anyhow)
    // but ordering is nice (nearness to base)
    UnitList minerals;

    Unit *builder;
    Unit &nexus;

    // Not implemented to disallow assignment
    NexusManager& operator=(const NexusManager&);
};