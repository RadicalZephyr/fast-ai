#pragma once

#include "INexusBehaviourController.h"

class BaseManager :
	public INexusBehaviourController {

public:
	BaseManager(void);

	virtual ~BaseManager(void);

};

// Need to add a signal to the nexus behaviour so that the base manager can subscribe to it to cause maynard'ing
// BaseCoordinator class to coordinate the actions of the different bases!!