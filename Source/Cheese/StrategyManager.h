#pragma once

#include "Important\Common.h"
#include "Strategy.h"

#include "boost/bind.hpp"

class CheeseStrategyManager : ICheeseStrategyControls
{
public:
	CheeseStrategyManager(ICheeseStrategy* strategy) : m_strategy(strategy)
	{
		Signal::onStart().connect(boost::bind(&CheeseStrategyManager::onStart, this));
		Signal::onFrame().connect(boost::bind(&CheeseStrategyManager::onFrame, this));
	}

	// ICheeseStrategyControls
	virtual void buildInBase(BWAPI::UnitType building);
	virtual bool moreGas();
	virtual bool moreCheeseProbes();

private:
	void onStart();
	void onFrame();

	ICheeseStrategy* m_strategy;
};