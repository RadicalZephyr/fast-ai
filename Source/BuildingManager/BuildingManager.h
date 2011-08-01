#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"
#include "IBuildingManagerBehaviour.h"

using BWAPI::Unit;
using BWAPI::UnitType;

class BuildingManager : private Debug {
public:
	explicit BuildingManager(Unit &theBuilding, IBM_BehaviourPtr theBehaviour): m_trainingType(BWAPI::UnitTypes::None),
																			    m_trainingUnit(0),
																			    m_trainingTime(),
												 							    m_building(theBuilding),
												 							    m_behaviour(theBehaviour) {
		Signal::onFrame().connect(boost::bind(&BuildingManager::onFrame, this));
		Signal::onFriendlyUnitCreate().connect(boost::bind(&BuildingManager::onUnitCreate, this, _1));
	}

	bool buildUnit(BWAPI::UnitType buildType);

	bool setUnitType(UnitType newType) {m_trainingType = newType;}

	UnitType getUnitType(void) {return m_trainingType;}

	void onFrame(void);
	void onUnitCreate(Unit* unit);

private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    void checkTraining(void);

	const static int c_buildDistance;

	UnitType m_trainingType;
	Unit *m_trainingUnit;
	Timed m_trainingTime;

	Unit &m_building;

	IBM_BehaviourPtr m_behaviour;

    // Not implemented to disallow assignment
	BuildingManager(void);
	BuildingManager(BuildingManager &);
	BuildingManager &operator=(const BuildingManager&);
};

// BuildingManagerFactory function, used for essentially registering a factory producer function in onUnitCreate
// make a default 'postBuild' function and a 'shouldBuild' function, pass it to the factory along with the unittype 
// that it goes with, and the function will register every instance of that unit with those functions



// New plan for how buildingmanager works.  No function pointers, instead it has a 'behaviour' (delegate) 
// object that has a bunch of virtual functions defined on it (i.e. a protocol) some of which are pure 
// virtual (required) and some of which are simple virtual (optional).

// If no 'behaviour' is provided, then there are reasonable defaults... or rather, a default behaviour is always specified