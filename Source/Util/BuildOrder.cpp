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
	try
	{
		if (m_probe -> getHitPoints() <= 0)
		{
			SIGNAL_OFF_FRAME(BuildOrder);
			m_onEnd(m_probe);
		}

		if (m_probe -> isIdle())
		{
			while (!m_buildQueue . front() . position . isValid())
			{ m_buildQueue . pop(); }

			if (!m_buildQueue . empty()
			&& BWAPI::Broodwar -> canBuildHere(m_probe , m_buildQueue . front() . position ,  m_buildQueue . front() . type)
			&& m_probe -> build(m_buildQueue . front() . position , m_buildQueue . front() . type)) 
			{
				m_currentBuildOrder = & m_buildQueue . front();
				m_currentBuildOrder -> onStart(m_currentBuildOrder , m_probe);
				m_buildQueue . pop();

				m_probe->move(idlePosition, true);

				clearOptionals();

				if (m_buildQueue . empty())
				{
					m_onEnd(m_probe);
				}
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

						m_probe->move(idlePosition, true);

						break;
					}
				}
			}
		}

		if (m_probe->isAttacking() || m_probe ->getOrderTarget() || !m_probe ->isMoving() && !m_probe ->isConstructing() && !m_probe -> isUnderAttack())
		{
			m_probe -> stop();
		}
	}
	catch (void* e)
	{
		SIGNAL_OFF_FRAME(BuildOrder);
		m_onEnd(m_probe);
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