#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"
#include <boost/function.hpp>

using BWAPI::Unit;

typedef boost::function<bool (BWAPI::UnitType)> boolUnitFunc;

class BuildingManager : private Debug {
public:
	BuildingManager(Unit &theBuilding);

	void buildUnit(BWAPI::UnitType buildType);
	void setShouldBuild(boolUnitFunc newPredicate);
	void onFrame(void);
	void onUnitCreate(Unit* unit);
    void onSendText(std::string text);
private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    void checkTraining(void);

	const static int c_buildDistance;

	Unit *m_trainingUnit;
	Timed m_trainingTime;

	Unit &m_building;
	boolUnitFunc m_shouldBuild;

    // Not implemented to disallow assignment
	BuildingManager &operator=(const BuildingManager&);
};