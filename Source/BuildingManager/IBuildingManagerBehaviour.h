#pragma once
#include "Important\Common.h"
#include <boost\shared_ptr.hpp>
#include <typeinfo>

// abstract base class for creating objects to implement behaviour for specific buildings' BuildingManagers
// Usage: publicly inherit from this base class, and override the virtual functions
//          Then, in onStart in Cannonball.cpp, add an entry to the managerWatchMap mapping the UnitType
//          of your specific building to a BM_BehaviourFactory< YourBehaviourClassName > object
class IBuildingManagerBehaviour
{
public:

	virtual ~IBuildingManagerBehaviour(void) {}

	virtual void postBuild(BWAPI::Unit *unit) = 0;
	virtual bool shouldBuild(BWAPI::UnitType *) {return true;}
	virtual BWAPI::UnitType *setBuildType(void) {return 0;}
};


// The abstract base class that allows us to make a map containing templated factory objects
struct BM_BaseBehaviourFactory {
	virtual ~BM_BaseBehaviourFactory(void) {}
	virtual IBM_BehaviourPtr Create(BWAPI::Unit *unit) = 0;
};

template<class T>
struct BM_BehaviourFactory : BM_BaseBehaviourFactory {

	virtual IBM_BehaviourPtr Create(BWAPI::Unit *unit) {
		Broodwar->printf("Creating a behaviour for: %s", unit->getType().getName().c_str());
		return IBM_BehaviourPtr(static_cast<IBuildingManagerBehaviour *>(new T(*unit)));
	}
};