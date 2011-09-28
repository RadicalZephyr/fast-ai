#pragma once

#include "Important/Common.h"

class UnitWander
{
public:
    UnitWander(BWAPI::Unit *unit) : m_unit(unit), m_connection(),
                                    m_visitedPositions(), m_attacking(false) {
        m_connection = Signal::onFrame().connect(boost::bind(&UnitWander::onFrame, this));
    }

    ~UnitWander(void) {
   m_connection.disconnect();
    }

    void onFrame(void);

private:
    BWAPI::Position newDestination(void);
    BWAPI::Unit *nearestEnemy(void);

    BWAPI::Unit *m_unit;
    boost::signals::connection m_connection;

    std::set<BWAPI::Position> m_visitedPositions;
    bool m_attacking;
};
