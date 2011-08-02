#pragma once

#include "Important/Common.h"
#include "UnitTrainingManager/Interfaces/IUnitTrainingManagerBehaviour.h"

// A Default behaviour that basically does nothing except constantly attempt 
//  to build a unit at that building
class DefaultBehaviour :
	public IUnitTrainingManagerBehaviour
{
public:
	DefaultBehaviour(BWAPI::Unit &building): m_building(building) {}

	virtual void postBuild(BWAPI::Unit *unit);
	virtual BWAPI::UnitType shouldBuild(BWAPI::UnitType type);

private:
	BWAPI::Unit &m_building;
	UnitTypeList m_canBuildList;

	// Unimplemented to prevent assignment/copying
	DefaultBehaviour(DefaultBehaviour &);
	DefaultBehaviour &operator=(DefaultBehaviour &);
};
