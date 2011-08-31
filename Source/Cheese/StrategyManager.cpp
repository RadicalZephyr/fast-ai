#include "StrategyManager.h"
#include "BaseManager/BaseManager.h"

CheeseStrategyManager::CheeseStrategyManager(ICheeseStrategy* strategy) : m_strategy(strategy), m_probe(4)
{
    SIGNAL_ON_START(CheeseStrategyManager);
    SIGNAL_ON_FRAME(CheeseStrategyManager);
    // strategy->init();
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
            // This is the problem child...
            m_scoutProbe = new ProbeControl((*first)->getControllee()->removeProbe(), boost::bind(&CheeseStrategyManager::foundEnemy, this, _1, _2));
              (*first)->getControllee()->onUnitDoneSignal().connect(boost::bind(&CheeseStrategyManager::onNewProbe, this, _1));
            m_base = (*first);
        }
        else
        {
              (*first)->getControllee()->onUnitDoneSignal().connect(boost::bind(&CheeseStrategyManager::onNewProbe, this, _1));
            m_base = (*first);
            m_scoutProbe = (ProbeControl*) 0xBADBEAF0;
        }
	}
}

void CheeseStrategyManager::onStart()
{
    //Signal::onFriendlyUnitCreate() . connect(boost::bind(&CheeseStrategyManager::onNewProbe, this, _1));
}

void CheeseStrategyManager::onNewProbe(BWAPI::Unit* unit)
{
    if (!unit->getType().isWorker())
        return;

    if (m_probe++ == m_strategy->whichProbe)
    {
        m_scoutProbe = new ProbeControl(m_base->getControllee()->removeProbe(), boost::bind(&CheeseStrategyManager::foundEnemy, this, _1, _2));
		m_strategy->init();
    }

    if (m_strategy->buildProbesTo != -1 && m_probe >= m_strategy->buildProbesTo)
    {
   m_base->getControllee()->setShouldBuild(false);
   m_base->getControllee()->onUnitDoneSignal().disconnect(boost::bind(&CheeseStrategyManager::onNewProbe, this, _1));
    }
}

void CheeseStrategyManager::foundEnemy(BWAPI::Unit *probe, BWAPI::Unit *enemyBase) {
    m_strategy->controls = this;

    m_strategy->setEnemyBase(enemyBase);
    m_strategy->setEnemyStartLocation(enemyBase ? enemyBase->getTilePosition() : TilePosition(0,0));
    m_strategy->newProbe(probe);
    m_strategy->setRunning(true);
    //setDebugSpeed(false);
}