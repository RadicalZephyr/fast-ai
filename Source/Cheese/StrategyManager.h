#pragma once

#include "Important\Common.h"
#include "Strategy.h"

#include "boost/bind.hpp"

#include "BuildingManager/NexusBehaviour.h"
#include "ProbeControl.h"

class CheeseStrategyManager : ICheeseStrategyControls
{
public:
	CheeseStrategyManager(ICheeseStrategy* strategy);

	// ICheeseStrategyControls
	virtual void buildInBase(BWAPI::UnitType building);
	virtual bool moreGas();
	virtual bool moreCheeseProbes();

private:
	void onStart();
	void onFrame();

	void onNewProbe(BWAPI::Unit* unit);

	ICheeseStrategy* m_strategy;

	NexusBehaviour* m_behaviour;
	ProbeControl* m_scoutProbe;
	int m_probe;
};