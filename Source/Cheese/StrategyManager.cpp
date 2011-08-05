#include "StrategyManager.h"
#include "BaseManager/BaseManager.h"

CheeseStrategyManager::CheeseStrategyManager(ICheeseStrategy* strategy) : m_strategy(strategy)
{
	SIGNAL_ON_START(CheeseStrategyManager);
	SIGNAL_ON_FRAME(CheeseStrategyManager);
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

void CheeseStrategyManager::onFrame(void) 
{
	if (m_strategy->whichProbe == 0 && m_scoutProbe == 0)
	{
		BaseManagerSet::iterator first = g_baseManagers.begin();
		m_scoutProbe = new ProbeControl((*first)->getControllee()->removeProbe(), boost::bind(&CheeseStrategyManager::foundEnemy, this, _1, _2));
	}
}

void CheeseStrategyManager::onStart()
{

}

void CheeseStrategyManager::onNewProbe(BWAPI::Unit* unit)
{
	if (!unit->getType().isWorker())
		return;

	if (m_probe == m_strategy->whichProbe)
		m_scoutProbe = new ProbeControl(0,0);
}

void CheeseStrategyManager::foundEnemy(BWAPI::Unit *probe, BWAPI::Unit *enemyBase) {
	m_strategy->setEnemyBase(enemyBase);
	m_strategy->setEnemyStartLocation(enemyBase->getTilePosition());
	m_strategy->newProbe(probe);
	m_strategy->setRunning(true);
	setDebugSpeed(false);
}