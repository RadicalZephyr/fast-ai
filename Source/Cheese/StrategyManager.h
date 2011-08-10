#pragma once

#include "Important/Common.h"
#include "Strategy.h"

#include <boost/bind.hpp>

#include "UnitTrainingManager/Behaviours/NexusBehaviour.h"
#include "ProbeControl.h"

class CheeseStrategyManager : ICheeseStrategyControls
{
public:
	CheeseStrategyManager(ICheeseStrategy* strategy);

	// ICheeseStrategyControls
	virtual void buildInBase(BWAPI::UnitType building);
	virtual bool moreGas();
	virtual bool moreMinerals();
	virtual bool moreCheeseProbes();
	virtual void resumeEcon();

private:
	void onStart();
	void onFrame();

	void onNewProbe(BWAPI::Unit* unit);
	void foundEnemy(BWAPI::Unit *probe, BWAPI::Unit *enemyBase);

	ICheeseStrategy* m_strategy;

	BaseManagerPtr m_base;
	ProbeControl* m_scoutProbe;
	int m_probe;
};
