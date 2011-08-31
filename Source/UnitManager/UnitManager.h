#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"

using BWAPI::Unit;
using BWAPI::UnitType;

class UnitManager : private Debug {
public:
    explicit UnitManager(IUnitManager_BehaviourPtr theBehaviour) : {

    }

    UnitType getUnitType(void) {
        return m_trainingType;
    }

    void onFrame(void);
    void onUnitCreate(Unit* unit);
    IUnitManager_BehaviourPtr getBehaviour(void) {
        return m_behaviour;
    }

private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    bool buildUnit(void);
    void checkTraining(void);
    UnitType checkShouldBuild(void) {
        return m_trainingType = m_behaviour->shouldBuild(m_trainingType);
    }

    const static int c_buildDistance;

    UnitType m_trainingType;
    Unit *m_trainingUnit;
    Timed m_trainingTime;

    Unit &m_building;

    IUnitManager_BehaviourPtr m_behaviour;

    boost::signal<void (BWAPI::Unit*)> m_unitDoneSignal;

    // Not implemented to disallow assignment
    UnitManager(void);
    UnitManager(UnitManager &);
    UnitManager &operator=(const UnitManager&);
};
