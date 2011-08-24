#pragma once

#include <BWAPI.h>
#include <queue>
#include "UnitTrainingManager/Behaviours/NexusBehaviour.h"

// Future design considerations
//   This class could potentially several 'types' of delegate/behaviour (queueing discipline, base layout, etc.)
//   The question is how to implement this.  As multiple sets of abstract bases?  Or as a single base class that
//   contains multiple 'sections' and default implementations of all the different behaviours

// Two major differences between the different designs: one has mandatory multiple inheritance, the other is single
//  the MI model would also require three base classes, instead of one...
// More files means that each one is smaller, the implemenation details of each thing aren't going to be wrapped up with eachother
// 

// Ideal model: 3 base classes with default implementations.  In order to customize this, you subclass just the class you want to customize.
//   then, in order to make a class that can actually be used with the basemanager, you create a leaf class that inherits from the customized
//   versions that you developed (plus any other classes you want to use)

// Inheritance hierarchy looks like this (left = root, right = base)
//  
//  BasicQueueing -> CustomQueueingOne -> CustomQueueingOnePointTwo ->  LeafClass
//  BasicLayout   -> CustomLayout  ----------------------------------->/
// and then LeafClass is used as the delegate/behaviour of your BaseManager


class RelativePosition;

class BaseManager {

public:

  // Use 'explicit' keyword to avoid allowing an implicit type conversion
	explicit BaseManager(NexusBehaviour *nexusBehaviour): m_controllee(nexusBehaviour),
														  m_lastBuildings(),
														  m_buildQueue() {
		m_frameConnection = Signal::onFrame().connect(boost::bind(&BaseManager::onFrame, this));
		m_unitCreateConnection = Signal::onFriendlyUnitCreate().connect(boost::bind(&BaseManager::onUnitCreate, this, _1));
		m_morphCreateConnection = Signal::onUnitMorph().connect(boost::bind(&BaseManager::onUnitMorph, this, _1));
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
	void onUnitMorph(BWAPI::Unit *unit);

private:
	
	bool doBuildCheck(void);
	BWAPI::TilePosition getRandomBuildPos(BWAPI::UnitType type);

	NexusBehaviour *m_controllee;

	BWAPI::Unit *m_probe;

	BWAPI::TilePosition m_lastTilePos;

	boost::signals::connection m_frameConnection;
	boost::signals::connection m_unitCreateConnection;
	boost::signals::connection m_morphCreateConnection;

	std::queue<BWAPI::UnitType> m_buildQueue;

	UnitVector m_lastBuildings;
};

// Need to add a signal to the nexus behaviour so that the base manager can subscribe to it to cause maynard'ing
// BaseCoordinator class to coordinate the actions of the different bases!!