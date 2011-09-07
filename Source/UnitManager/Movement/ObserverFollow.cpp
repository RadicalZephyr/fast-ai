#include "ObserverFollow.h"


ObserverFollow::ObserverFollow(BWAPI::Unit *unit) : m_unit(unit), m_connection() {
    m_connection = Signal::onFrame().connect(boost::bind(&ObserverFollow::onFrame, this));
    m_following = NULL;
}

void ObserverFollow::onFrame(void) {
    if (!m_unit->exists()) {
        //BWAPI::Broodwar->printf("Unit has died");
        delete this;
        return;
    }

    if (m_following && !m_following->exists()) {
        m_following = NULL;
        // Broodwar->printf("Unit to follow has died");
    }

    BWAPI::Unit *cEnemy = cloakedEnemy();

    if (!m_following && !cEnemy) { // Not currently following a unit
        followNewUnit();
        // Broodwar->printf("Observer following new unit");
    }

    if (cEnemy) {  // Cloaked enemy is present
        m_following = NULL;
        m_unit->move(cEnemy->getPosition());
        // Broodwar->printf("Observer moving to cloaked enemy");
    }
}

void ObserverFollow::followNewUnit(void) {
   UnitSet myUnits = Broodwar->self()->getUnits();
   UnitSet::iterator it;

   int distance = 999999;

    for (it=myUnits.begin(); it!=myUnits.end(); it++) {
        if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Dragoon && m_unit->getDistance(*it) < distance) {
            distance = m_unit->getDistance(*it);
            m_following = (*it);
        }
    }

    m_unit->follow(m_following);
}

BWAPI::Unit *ObserverFollow::cloakedEnemy(void) {
   BWAPI::Unit *enemy = NULL;

   UnitSet enemyUnits = Broodwar->enemy()->getUnits();
   UnitSet::iterator it;

   int distance = 999999;

    for (it=enemyUnits.begin(); it!=enemyUnits.end(); it++) {
        if (!(*it)->isDetected() && (*it)->getDistance(Position(Broodwar->self()->getStartLocation())) < distance) {
            distance = (*it)->getDistance(Position(Broodwar->self()->getStartLocation()));
            enemy = (*it);
        }
    }

    return enemy;
}