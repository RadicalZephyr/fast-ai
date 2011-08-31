#pragma once

#include "Important/Common.h"
#include "FunctionObjects/DistanceSorter.h"
#include "Util/Timed.h"

using namespace BWAPI;

class ProbeControl
{
public:
    typedef boost::function<void (Unit *probe, Unit *enemyBase)> onFindCallbackFunction;

    ProbeControl(BWAPI::Unit *newProbe, onFindCallbackFunction callback);


private:
    void onFrame();
    void onUnitDiscover(BWAPI::Unit *unit);

    onFindCallbackFunction m_callback;
    BWAPI::Unit *m_probe;

    std::set<TilePosition>::const_iterator m_scoutLocations;
    ProbeControl& operator= (const ProbeControl&);

    int timeout;
};
