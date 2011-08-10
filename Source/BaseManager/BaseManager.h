#pragma once

#include <BWAPI.h>
#include <queue>
#include "INexusBehaviourController.h"
#include "UnitTrainingManager/Behaviours/NexusBehaviour.h"

class RelativePosition;

class BaseManager :
	public INexusBehaviourController {

public:

	explicit BaseManager(NexusBehaviour *nexusBehaviour): m_controllee(nexusBehaviour),
														  m_lastBuildings(),
														  m_buildQueue() {
		m_frameConnection = Signal::onFrame().connect(boost::bind(&BaseManager::onFrame, this));
		m_unitCreateConnection = Signal::onFriendlyUnitCreate().connect(boost::bind(&BaseManager::onUnitCreate, this, _1));
	}

	virtual ~BaseManager(void) {
		m_frameConnection.disconnect();
		m_unitCreateConnection.disconnect();
	}

	bool hasLocation(void) {return m_controllee != 0;}
	void setControllee(NexusBehaviour *controllee) {m_controllee = controllee;}
	NexusBehaviour *getControllee(void) {return m_controllee;}

	bool constructBuilding(BWAPI::UnitType type);

	void onFrame(void);
	void onUnitCreate(BWAPI::Unit *unit);

private:
	
	bool doBuildCheck(void);
	BWAPI::TilePosition getRandomBuildPos(BWAPI::UnitType type);

	NexusBehaviour *m_controllee;

	BWAPI::Unit *m_probe;

	BWAPI::TilePosition m_lastTilePos;

	boost::signals::connection m_frameConnection;
	boost::signals::connection m_unitCreateConnection;

	std::queue<BWAPI::UnitType> m_buildQueue;

	UnitVector m_lastBuildings;
};

// Need to add a signal to the nexus behaviour so that the base manager can subscribe to it to cause maynard'ing
// BaseCoordinator class to coordinate the actions of the different bases!!