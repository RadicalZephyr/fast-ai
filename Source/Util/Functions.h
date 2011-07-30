#pragma once

#include "Important\Common.h"


BWAPI::TilePosition ReconsiderBuildLocation(BWAPI::Unit * builder, BWAPI::TilePosition original_position, BWAPI::UnitType Attempted_Build, int distance = 2);

//BuildingManagerPtr checkForBuildings(BWAPI::Unit *unit, managerWatchVector watchVector);