#include <BWAPI.h>

using namespace BWAPI;

// Takes: Worker whose building attempt failed, Original position of failed build, 
// Building type that has failed, Angle for the most optimal building placement 
// from the failed original.
// 
// Returns: A position for the new build placement
// Raises an exception if there is no immediate possible building location.
TilePosition ReconsiderBuildLocation(Unit * builder, TilePosition original_position, UnitType Attempted_Build, int suggested_angle = 0)
{
	// Multidimensional array
	bool available[9];

	// Test each tile for buildability
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			TilePosition offset(x, y);
			available[(x + 1) * 3 + (y + 1)] = Broodwar->canBuildHere(builder, original_position + offset, Attempted_Build);
		}
	}

	// Return the most apropriate
	// Currently returns top left, scanning downwards then rightwards.
	for (int x = 0; x <= 2; x++)
	{
		for (int y = 0; y <= 2; y++)
		{
			if (available[x * 3 + y])
			{
				TilePosition offset(x, y);
				return original_position + offset;
			}
		}
	}
}