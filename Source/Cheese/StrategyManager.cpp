#include "StrategyManager.h"
#include "BaseManager/BaseManager.h"

CheeseStrategyManager::CheeseStrategyManager(ICheeseStrategy* strategy) : m_strategy(strategy)
{
	SIGNAL_ON_START(CheeseStrategyManager);

	strategy->init();
}

// ICheeseStrategyControls
void CheeseStrategyManager::buildInBase(BWAPI::UnitType building)
{

}

bool CheeseStrategyManager::moreGas()
{
	return false;
}

bool CheeseStrategyManager::moreCheeseProbes()
{
	return false;
}


void CheeseStrategyManager::onStart()
{

	if (m_strategy->whichProbe == 0)
	{
		BaseManagerSet::iterator first = g_baseManagers.begin();
		
		m_scoutProbe = new ProbeControl((*first)->getControllee()->removeProbe());
	}
}

void CheeseStrategyManager::onNewProbe(BWAPI::Unit* unit)
{
	if (!unit->getType().isWorker())
		return;

	if (m_probe == m_strategy->whichProbe)
		m_scoutProbe = new ProbeControl(0);
}
