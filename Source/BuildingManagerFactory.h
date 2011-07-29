#pragma once

#include "Util\Debug.h"
#include "Important\Common.h"


class BuildingManagerFactory :
	private Debug {
public:
	BuildingManagerFactory(void);
	~BuildingManagerFactory(void);

	void onUnitCreate(BWAPI::Unit* unit);

private:

};

