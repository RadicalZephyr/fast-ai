
// Takes: Worker whose building attempt failed, Original position of failed build, 
// Building type that has failed, Angle for the most optimal building placement 
// from the failed original.
// 
// Returns: A position for the new build placement
// Raises an exception if there is no immediate possible building location.
TilePosition ReconsiderBuildLocation(Unit * builder, TilePosition original_position, UnitType Attemped_Build, int suggested_angle = 0, int distance = 1)
{
	// 0 = right, 1 = top-right, 2 = top, 3 = top-left, 4 = left, 5 = bot-left, 6 = bot, 7 = bot-right
	int octodrant = (suggested_angle % 360 / 45);
	int x_offset; int y_offset;
	bool available[distance * 2 + 1][distance * 2 + 1];

	// Test each tile for buildability
	for (int x = -distance; x <= distance; x++)
	{
		for (int y = -distance; y <= distance; y++)
		{
			TilePosition offset(x, y);
			available[x + distance][y + distance] = canBuildHere(builder, original_position + offset, Attempted_Build);
		}
	}

	// Return the most apropriate
	// Currently returns top left, scanning downwards then rightwards.
	for (int x = -distance; x <= distance; x++)
	{
		for (int y = -distance; y <= distance; y++)
		{
			if (available[x][y])
			{
				TilePosition offset(x, y);
				return original_position + offset;
			}
		}
	}
}