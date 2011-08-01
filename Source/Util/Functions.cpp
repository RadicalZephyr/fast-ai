
#include "Functions.h"
#include "BuildingManager/BuildingManager.h"

using namespace BWAPI;

// Takes: Worker whose building attempt failed, Original position of failed build, 
// Building type that has failed, Angle for the most optimal building placement 
// from the failed original.
// 
// Returns: A position for the new build placement
// Raises an exception if there is no immediate possible building location.
TilePosition ReconsiderBuildLocation(Unit * builder, TilePosition original_position, UnitType Attempted_Build, int distance)
{
	// Test each tile for buildability
	for (int x = -distance; x <= distance; x++)
	{
		for (int y = -distance; y <= distance; y++)
		{
			TilePosition offset(x, y);
			if (Broodwar->canBuildHere(builder, original_position + offset, Attempted_Build))
				return offset;
		}
	}
}


void checkForBuildings(BWAPI::Unit *unit, BuildingManager_factoryMap watchMap) {
	BuildingManager_factoryMap::iterator itr;
	if ((itr = watchMap.find(unit->getType())) != watchMap.end()) {
		g_managers.insert(BuildingManagerPtr(new BuildingManager(*unit, itr->second->Create(unit))));
	}
}
