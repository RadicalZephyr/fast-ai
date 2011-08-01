#pragma once

#include "Important\Common.h"
#include "IBuildingManagerBehaviour.h"

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
};