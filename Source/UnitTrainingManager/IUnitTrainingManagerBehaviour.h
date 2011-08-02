#pragma once
#include "Important/Common.h"
#include <boost/shared_ptr.hpp>
#include <typeinfo>

// abstract base class for creating objects to implement behaviour for specific buildings' UnitTrainingManagers
// Usage: publicly inherit from this base class, and override the virtual functions
//          Then, in onStart in Cannonball.cpp, add an entry to the g_managerWatchMap mapping the UnitType
//          of your specific building to a BM_BehaviourFactory< YourBehaviourClassName > object
class IUnitTrainingManagerBehaviour
{
public:

	virtual ~IUnitTrainingManagerBehaviour(void) {}

	virtual void postBuild(BWAPI::Unit *unit) = 0;
	virtual BWAPI::UnitType shouldBuild(BWAPI::UnitType ) {return BWAPI::UnitTypes::None;}

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
