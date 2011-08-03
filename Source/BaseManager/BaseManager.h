#pragma once

#include "INexusBehaviourController.h"
#include "UnitTrainingManager/Behaviours/NexusBehaviour.h"

class BaseManager :
	public INexusBehaviourController {

public:
	explicit BaseManager(void): m_controllee(0),
								m_lastBuilding(0) {
		Signal::onFrame().connect(boost::bind(&BaseManager::onFrame, this));
	}

	explicit BaseManager(NexusBehaviour *nexusBehaviour): m_controllee(nexusBehaviour),
														  m_lastBuilding(0) {
		Signal::onFrame().connect(boost::bind(&BaseManager::onFrame, this));
	}

	virtual ~BaseManager(void) {}

	bool hasLocation(void) {return m_controllee != 0;}
	void setControllee(NexusBehaviour *controllee) {m_controllee = controllee;}
	NexusBehaviour *getControllee(void) {return m_controllee;}

	bool constructBuilding(BWAPI::UnitType type);

	void onFrame(void);

private:
	
	NexusBehaviour *m_controllee;

	BWAPI::Unit *m_probe;

	BWAPI::Unit *m_lastBuilding;

};

// Need to add a signal to the nexus behaviour so that the base manager can subscribe to it to cause maynard'ing
// BaseCoordinator class to coordinate the actions of the different bases!!