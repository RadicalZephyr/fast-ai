#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"

using BWAPI::Unit;
using BWAPI::UnitType;

class BuildingManager : private Debug {
public:
    explicit BuildingManager(Unit &theBuilding): m_trainingType(0),
												 m_trainingUnit(0),
												 m_trainingTime(),
												 m_building(theBuilding),
												 m_shouldBuild(0),
                                                 m_postBuild(0) {}

	bool buildUnit(BWAPI::UnitType *buildType);

    void setShouldBuild(BM_shouldBuildFunc newPredicate) {m_shouldBuild = newPredicate;}
    void setPostBuild(BM_postBuildFunc newPostBuild) {m_postBuild = newPostBuild;}
	bool setUnitType(UnitType *newType) {m_trainingType = newType;}
	
	BM_shouldBuildFunc getShouldBuild(void) {return m_shouldBuild;}
	BM_postBuildFunc getPostBuild(void) {return m_postBuild;}
	UnitType *getUnitType(void) {return m_trainingType;}

	void onFrame(void);
	void onUnitCreate(Unit* unit);
    //void onSendText(std::string text);
private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    void checkTraining(void);

	const static int c_buildDistance;

	UnitType *m_trainingType;
	Unit *m_trainingUnit;
	Timed m_trainingTime;

	Unit &m_building;

	BM_shouldBuildFunc m_shouldBuild;
    BM_postBuildFunc m_postBuild;

    // Not implemented to disallow assignment
	BuildingManager(void);
	BuildingManager(BuildingManager &);
	BuildingManager &operator=(const BuildingManager&);
};

// BuildingManagerFactory function, used for essentially registering a factory producer function in onUnitCreate
// make a default 'postBuild' function and a 'shouldBuild' function, pass it to the factory along with the unittype 
// that it goes with, and the function will register every instance of that unit with those functions



// New plan for how buildingmanager works.  No function pointers, instead it has a 'behaviour' (delegate) 
// object that has a bunch of virtual functions defined on it (i.e. a protocol) some of which are pure 
// virtual (required) and some of which are simple virtual (optional).

// If no 'behaviour' is provided, then there are reasonable defaults... or rather, a default behaviour is always specified