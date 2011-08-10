#pragma once

#include "Important/Common.h"
#include "UnitTrainingManager/IUnitTrainingManagerBehaviour.h"

// A Default behaviour that basically does nothing except constantly attempt 
//  to build a unit at that building
class GatewayBehaviour :
	public IUnitTrainingManagerBehaviour
{
public:
	GatewayBehaviour(BWAPI::Unit *building): m_building(building),
											 m_buildType(BWAPI::UnitTypes::Protoss_Zealot) {}

	virtual void postBuild(BWAPI::Unit *unit);
	virtual BWAPI::UnitType shouldBuild(BWAPI::UnitType type);
	void setBuildType(BWAPI::UnitType type) {m_buildType = type;}

private:
	BWAPI::Unit *m_building;
	BWAPI::UnitType m_buildType;

	// Unimplemented to prevent assignment/copying
	GatewayBehaviour(GatewayBehaviour &);
	GatewayBehaviour &operator=(GatewayBehaviour &);
};
