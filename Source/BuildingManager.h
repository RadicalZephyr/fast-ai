#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"
#include <boost/function.hpp>

using BWAPI::Unit;

typedef boost::function<bool (BWAPI::UnitType)> boolUnitTypeFunc;
typedef boost::function<void (BWAPI::Unit *)> voidUnitFunc;

class BuildingManager : private Debug {
public:
    explicit BuildingManager(Unit &theBuilding): m_trainingUnit(0),
												 m_trainingTime(),
												 m_building(theBuilding),
												 m_shouldBuild(0),
                                                 m_postBuild(0) {}

	bool buildUnit(BWAPI::UnitType buildType);
    void setShouldBuild(boolUnitTypeFunc newPredicate) {m_shouldBuild = newPredicate;}
    void setPostBuild(voidUnitFunc newPostBuild) {m_postBuild = newPostBuild;}

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
	boolUnitTypeFunc m_shouldBuild;
    voidUnitFunc m_postBuild;

    // Not implemented to disallow assignment
	BuildingManager &operator=(const BuildingManager&);
};