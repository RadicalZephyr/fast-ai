#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <BWAPI.h>

// This file compiles the globals in.
#define COMPILE_GLOBAL
#include "Common.h"

#include "../Cannonball.h"
#include "BWAPIadditions/BuildsWhat.h"

namespace BWAPI { 
	Game* Broodwar; 

	UnitTypeSet const &buildsWhat(UnitType unitType) {
		static BuildsWhat buildsWhatMap;
		return buildsWhatMap.lookupBuildsWhat(unitType);
	}
}

BOOL APIENTRY DllMain( HANDLE, 
                       DWORD  ul_reason_for_call, 
                       LPVOID
					 )
{
    
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
    BWAPI::BWAPI_init();
		break;
	case DLL_PROCESS_DETACH:
		break;
	}


	return TRUE;
}

 extern "C" __declspec(dllexport) BWAPI::AIModule* newAIModule(BWAPI::Game* game)
{
  // Explicitly ignoring the return value.  This call is solely to initialize the buildsWhat static
  //  data structure
  (void)BWAPI::buildsWhat(BWAPI::UnitTypes::getUnitType("Protoss Nexus"));
  BWAPI::Broodwar=game;
  return new Cannonball();
}

