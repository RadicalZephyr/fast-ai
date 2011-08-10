#pragma once

#include "Important/Common.h"

// This is an interface to provide control functions for the CheeseStrategy to use
class ICheeseStrategyControls
{
public:
	virtual void buildInBase(BWAPI::UnitType building) = 0;
	virtual bool moreGas() = 0;
	virtual bool moreMinerals() = 0;
	virtual bool moreCheeseProbes() = 0;

	// This will resume building probes
	virtual void resumeEcon() = 0;
};

class ICheeseStrategy abstract
{
public: // Intilization section

	//// These variables must be set at construction

	// This detrmines which probe will be the probe given to the cheese strategy
	// 0 means the starting probe, greater values are the probe built to give, max 9;
	int whichProbe;

	// This determines the limit we build probes to, -1 means infinity
	int buildProbesTo;

	// For long asynchronous intilization actions
	virtual void init() = 0;

public: //Usage Section

	//// These variables will be set before any of the following functions are called
	void setEnemyBase(BWAPI::Unit *base) {enemyBase = base;}
	BWAPI::Unit *getEnemyBase(void) {return enemyBase;}

	void setEnemyStartLocation(BWAPI::TilePosition tile) {enemyStartLocation = tile;}
	BWAPI::TilePosition getEnemyStartLocation(void) {return enemyStartLocation;}

	ICheeseStrategyControls* controls;

	// Will be called every time a new probe arrives at the cheese site
	virtual void newProbe(BWAPI::Unit* probe) = 0;

	virtual void setRunning(bool isRunning) = 0;
	ICheeseStrategy() {}
private:
	BWAPI::Unit* enemyBase;
	BWAPI::TilePosition enemyStartLocation;
};
