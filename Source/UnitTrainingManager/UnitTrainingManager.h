#pragma once

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Timed.h"
#include "UnitTrainingManager/IUnitTrainingManagerBehaviour.h"

using BWAPI::Unit;
using BWAPI::UnitType;

class UnitTrainingManager : private Debug {
public:
	explicit UnitTrainingManager(Unit &theBuilding, IUnitTrainingManager_BehaviourPtr theBehaviour): m_trainingType(BWAPI::UnitTypes::None),
																			    m_trainingUnit(0),
																			    m_trainingTime(),
												 							    m_building(theBuilding),
												 							    m_behaviour(theBehaviour) {
		Signal::onFrame().connect(boost::bind(&UnitTrainingManager::onFrame, this));
		Signal::onFriendlyUnitCreate().connect(boost::bind(&UnitTrainingManager::onUnitCreate, this, _1));
	}

	bool buildUnit(BWAPI::UnitType buildType);

	bool setUnitType(UnitType newType) {m_trainingType = newType;}

	UnitType getUnitType(void) {return m_trainingType;}

	void onFrame(void);
	void onUnitCreate(Unit* unit);

private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

    void checkTraining(void);

	const static int c_buildDistance;

	UnitType m_trainingType;
	Unit *m_trainingUnit;
	Timed m_trainingTime;

	Unit &m_building;

	IUnitTrainingManager_BehaviourPtr m_behaviour;

    // Not implemented to disallow assignment
	UnitTrainingManager(void);
	UnitTrainingManager(UnitTrainingManager &);
	UnitTrainingManager &operator=(const UnitTrainingManager&);
};
