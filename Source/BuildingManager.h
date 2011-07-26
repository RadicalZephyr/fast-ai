#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"

#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

using BWAPI::Unit;
using BWAPI::UnitType;

typedef boost::function<bool (BWAPI::UnitType)> boolUnitTypeFunc;
typedef boost::function<void (BWAPI::Unit *)> voidUnitFunc;

class BuildingManager : private Debug {
public:
    explicit BuildingManager(Unit &theBuilding): m_trainingType(0),
												 m_trainingUnit(0),
												 m_trainingTime(),
												 m_building(theBuilding),
												 m_shouldBuild(0),
                                                 m_postBuild(0) {}

	bool buildUnit(BWAPI::UnitType *buildType);

    void setShouldBuild(boolUnitTypeFunc newPredicate) {m_shouldBuild = newPredicate;}
    void setPostBuild(voidUnitFunc newPostBuild) {m_postBuild = newPostBuild;}
	bool setUnitType(UnitType *newType) {m_trainingType = newType;}
	
	boolUnitTypeFunc getShouldBuild(void) {return m_shouldBuild;}
	voidUnitFunc getPostBuild(void) {return m_postBuild;}
	UnitType *getUnitType(void) {return m_trainingType;}

	void onFrame(void);
	void onUnitCreate(Unit* unit);
    void onSendText(std::string text);
private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    void checkTraining(void);

	const static int c_buildDistance;

	UnitType *m_trainingType;
	Unit *m_trainingUnit;
	Timed m_trainingTime;

	Unit &m_building;

	boolUnitTypeFunc m_shouldBuild;
    voidUnitFunc m_postBuild;

    // Not implemented to disallow assignment
	BuildingManager &operator=(const BuildingManager&);
};

// BuildingManagerFactory function, used for essentially registering a factory producer function in onUnitCreate
// make a default 'postBuild' function and a 'shouldBuild' function, pass it to the factory along with the unittype 
// that it goes with, and the function will register every instance of that 

typedef boost::shared_ptr<BuildingManager> BuildingManagerPtr;

typedef boost::tuple<BWAPI::UnitType, boolUnitTypeFunc, voidUnitFunc> managerWatchTriple;
typedef std::vector<managerWatchTriple> managerWatchVector;

BuildingManagerPtr checkForBuildings(Unit *unit, managerWatchVector watchVector);