#include "Important\Common.h"

// This is an interface to provide control functions for the CheeseStrategy to use
class ICheeseStrategyControls
{
public:
	virtual void buildInBase(BWAPI::UnitType building) = 0;
	virtual bool moreGas() = 0;
	virtual bool moreCheeseProbes() = 0;
};

class ICheeseStrategy
{
public: // Intilization section

	//// These variables must be set at construction

	// This detrmines which probe will be the probe given to the cheese strategy
	// 0 means the starting probe, greater values are the probe built to give, max 9;
	const int whichProbe;


	// For long asynchronous intilization actions
	virtual void init() = 0;

public: //Usage Section

	//// These variables will be set before any of the following functions are called
	BWAPI::Unit* enemyBase;
	BWAPI::TilePosition enemyStartLocation;


	// Will be called every time a new probe arrives at the cheese site
	virtual void newProbe(BWAPI::Unit* probe) = 0;
};