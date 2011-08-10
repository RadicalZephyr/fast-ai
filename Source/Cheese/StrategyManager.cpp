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
	m_base->constructBuilding(building);
}

bool CheeseStrategyManager::moreGas()
{
	return false;
}

bool CheeseStrategyManager::moreMinerals()
{
	return false;
}

bool CheeseStrategyManager::moreCheeseProbes()
{
	return false;
}

void CheeseStrategyManager::resumeEcon()
{
	m_base->getControllee()->setShouldBuild(true);
}

void CheeseStrategyManager::onFrame(void) 
{
	if (m_scoutProbe == 0)
	{
		BaseManagerSet::iterator first = g_baseManagers.begin();
		if (m_strategy->whichProbe == 0)
		{
			m_scoutProbe = new ProbeControl((*first)->getControllee()->removeProbe(), boost::bind(&CheeseStrategyManager::foundEnemy, this, _1, _2));
		}
		else
		{
			//(*first)->
		}
	}
}

void CheeseStrategyManager::onStart()
{
	//Signal::onFriendlyUnitCreate().connect(boost::bind(&CheeseStrategyManager::onNewProbe, this, _1));
}

void CheeseStrategyManager::onNewProbe(BWAPI::Unit* unit)
{
	if (!unit->getType().isWorker())
		return;

	if (m_probe++ == m_strategy->whichProbe)
		m_scoutProbe = new ProbeControl(0,0);

	if (m_strategy->buildProbesTo != -1 && m_probe >= m_strategy->buildProbesTo)
	{
		m_base->getControllee()->setShouldBuild(false);
	}
}

void CheeseStrategyManager::foundEnemy(BWAPI::Unit *probe, BWAPI::Unit *enemyBase) {
	BaseManagerSet::iterator first = g_baseManagers.begin();
	m_base = (*first);

	m_strategy->controls = this;

	m_strategy->setEnemyBase(enemyBase);
	m_strategy->setEnemyStartLocation(enemyBase->getTilePosition());
	m_strategy->newProbe(probe);
	m_strategy->setRunning(true);
	setDebugSpeed(false);
}