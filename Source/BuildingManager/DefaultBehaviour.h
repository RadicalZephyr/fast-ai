#pragma once

#include "Important\Common.h"
#include "IBuildingManagerBehaviour.h"

// A Default behaviour that basically does nothing except constantly attempt 
//  to build a unit at that building
class DefaultBehaviour :
	public IBuildingManagerBehaviour
{
public:
	DefaultBehaviour(BWAPI::Unit &building): m_building(building) {}

	virtual void postBuild(BWAPI::Unit *unit);
	virtual bool shouldBuild(BWAPI::UnitType type);
	virtual BWAPI::UnitType setBuildType(void);

private:
	BWAPI::Unit &m_building;
	UnitTypeList m_canBuildList;

	// Unimplemented to prevent assignment/copying
	DefaultBehaviour(DefaultBehaviour &);
	DefaultBehaviour &operator=(DefaultBehaviour &);
};