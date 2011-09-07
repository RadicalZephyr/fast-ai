#pragma once

#include "Important/Common.h"
#include "UnitTrainingManager/IUnitTrainingManagerBehaviour.h"

class RoboticsBehaviour :
    public IUnitTrainingManagerBehaviour
{
public:
    RoboticsBehaviour(BWAPI::Unit *building) : m_building(building) {
   g_robotics.insert(RoboticsBehaviourPtr(this));
        m_maxObsCount = 3;
    }

    virtual void postBuild(BWAPI::Unit *unit);
    virtual BWAPI::UnitType shouldBuild(BWAPI::UnitType type);
    void setBuildType(BWAPI::UnitType type) {
        m_buildType = type;
    }

private:
    BWAPI::Unit *m_building;
    BWAPI::UnitType m_buildType;

    int m_maxObsCount;

    // Unimplemented to prevent assignment/copying
    RoboticsBehaviour(RoboticsBehaviour &);
    RoboticsBehaviour &operator=(RoboticsBehaviour &);
};
