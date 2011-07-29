#include <BWAPI.h>
#include <vector>

using namespace BWAPI;

// Takes: Worker whose building attempt failed, Original position of failed build, 
// Building type that has failed, Angle for the most optimal building placement 
// from the failed original.
// 
// Returns: A position for the new build placement
// Raises an exception if there is no immediate possible building location.
TilePosition ReconsiderBuildLocation(Unit * builder, TilePosition original_position, UnitType Attempted_Build, int distance = 2)
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