#pragma once

#include "Important/Common.h"
#include <set>

// abstract base class for creating objects to implement behaviour for specific units behaviors
// Usage: publicly inherit from this base class, and override the virtual functions
class IUnitManagerBehaviour
{
public:

	virtual ~IUnitManagerBehaviour(void) {}

	virtual void manageUnit(BWAPI::Unit *unit) = 0;
	virtual std::set<BWAPI::UnitType> const& manageableUnits() = 0;

};


// The abstract base class that allows us to make a map containing templated factory objects
struct UnitTrainingManager_BaseBehaviourFactory {
	virtual ~UnitTrainingManager_BaseBehaviourFactory(void) {}
	virtual IUnitTrainingManager_BehaviourPtr Create(BWAPI::Unit *unit) = 0;
};

// This is a factory class template.  Intended to be used with the g_managerWatchMap global variable
// create a new instance of this class, templatized on the Behaviour that you wish to have it create
// and hand the UnitType and behaviour instance to the g_managerWatchMap
// Example usages are in Cannonball.cpp
template<class T>
struct BM_BehaviourFactory : UnitTrainingManager_BaseBehaviourFactory {

	virtual IUnitTrainingManager_BehaviourPtr Create(BWAPI::Unit *unit) {
		Broodwar->printf("Creating a behaviour for: %s", unit->getType().getName().c_str());
		return IUnitTrainingManager_BehaviourPtr(static_cast<IUnitTrainingManagerBehaviour *>(new T(*unit)));
	}
};
