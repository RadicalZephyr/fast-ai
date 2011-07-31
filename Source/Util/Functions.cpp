
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

//BuildingManagerPtr checkForBuildings(Unit *unit, managerWatchVector watchVector) {
//	for (managerWatchVector::const_iterator itr = watchVector.begin(); itr != watchVector.end(); ++itr) {
//
//		// Check if the unit is of a type given in the watchVector
//		if (unit->getType() == (*itr).get<0>()) {
//			BuildingManagerPtr newManager(new BuildingManager(*unit));
//			newManager->setShouldBuild(itr->get<1>());
//			newManager->setPostBuild(itr->get<2>());
//			return newManager;
//		}
//	}
//}