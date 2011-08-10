#include "BuildOrder.h"

void BuildOrderElementOnStartVoid(BuildOrderElement* orderElement, BWAPI::Unit* builderProbe) {return;}
void BuildOrderElementOnDoneVoid(BWAPI::Unit* finishedBuilding) {return;}

void BuildOrder::addOrderElement(BuildOrderElement const & newOrder)
{
	m_buildQueue . push(newOrder);
}
void BuildOrder::addOptionalElement(BuildOrderElement const& newOrder)
{
	m_optionals . push_back(newOrder);
}
void BuildOrder::start(BWAPI::Unit * probe)
{
	m_probe = probe;
	SIGNAL_ON_FRAME(BuildOrder);
	clearOptionals();
}

BWAPI::Unit * BuildOrder::stop()
{
	SIGNAL_OFF_FRAME(BuildOrder);
	return m_probe;
}

void BuildOrder::onFrame()
{
	if (m_probe -> getHitPoints() <= 0)
		m_onEnd(m_probe);

	if (m_probe -> isIdle())
	{
		while (!m_buildQueue . front() . position . isValid())
		{ m_buildQueue . pop(); }

		if (BWAPI::Broodwar -> canBuildHere(m_probe , m_buildQueue . front() . position ,  m_buildQueue . front() . type)
		&& m_probe -> build(m_buildQueue . front() . position , m_buildQueue . front() . type)) 
		{
			m_currentBuildOrder = & m_buildQueue . front();
			m_currentBuildOrder -> onStart(m_currentBuildOrder , m_probe);
			m_buildQueue . pop();
			clearOptionals();
		}
		else
		{
			for (std::list<BuildOrderElement>::iterator it = m_optionals . begin() ; it != m_optionals . end() ; it ++)
			{
				if (BWAPI::Broodwar -> canBuildHere(m_probe , (*it) . position ,  (*it) . type)
				&& m_probe -> build((*it) . position , (*it) . type)) 
				{
					m_currentBuildOrder = & (*it);
					m_currentBuildOrder -> onStart(m_currentBuildOrder , m_probe);
					m_optionals . erase(it);
					break;
				}
			}
		}
	}
	else if (m_probe -> isAttacking())
	{
		m_probe -> stop();
	}
}

void BuildOrder::clearOptionals()
{
	while (m_buildQueue . front() . optional)
	{
		m_optionals . push_back(m_buildQueue . front());
		m_buildQueue . pop();
	}
}