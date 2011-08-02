#pragma once

#include "Important/Common.h"
#include "UnitTrainingManager/Interfaces/IUnitTrainingManagerBehaviour.h"

BWAPI::TilePosition ReconsiderBuildLocation(BWAPI::Unit * builder, BWAPI::TilePosition original_position, BWAPI::UnitType Attempted_Build, int distance = 2);

void checkForBuildings(BWAPI::Unit *unit, UnitTrainingManager_factoryMap);
