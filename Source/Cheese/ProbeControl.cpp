#include "ProbeControl.h"
using namespace BWAPI;


//const int NexusManager::s_mineralDistance = 270;
ProbeControl::ProbeControl(BWAPI::Unit *newProbe, onFindCallbackFunction callback) : m_probe(newProbe),
													m_callback(callback),
													timeout(0)
{
	SIGNAL_ON_FRAME(ProbeControl);
	Signal::onUnitDiscover().connect(boost::bind(&ProbeControl::onUnitDiscover, this, _1));

	if (m_probe == 0) {
		Broodwar->printf("ERROR: ProbeControl: onStart: null pointer, disconnecting");
		SIGNAL_OFF_FRAME(ProbeControl);
		return;
	}
	
	std::set<TilePosition> & startLocations = Broodwar->getStartLocations();

	TilePosition myPlace = Broodwar->self()->getStartLocation();
	myPlace.makeValid();
	
	startLocations.erase(myPlace);

	m_scoutLocations = startLocations.cbegin();

	Position nextPlace(*m_scoutLocations);
	nextPlace.makeValid();

	m_probe->move(nextPlace);
}

void ProbeControl::onFrame()
{
	if(120 > m_probe->getPosition().getApproxDistance(m_probe->getTargetPosition())) {

		Position nextPlace(*(++m_scoutLocations));
		nextPlace.makeValid();

		timeout = 0;

		m_probe->move(nextPlace);
	}
	if (g_frame % 10 == 0) {
		Broodwar->setScreenPosition(m_probe->getPosition() - Position(300, 200));
	}
	if (timeout++ > 1600)
	{
		m_callback(m_probe, 0);
	}
}

void ProbeControl::onUnitDiscover(BWAPI::Unit *unit) {
	if (unit->getType().isResourceDepot() && unit->getPlayer() != Broodwar->self() && 
		unit->getTilePosition() == m_probe->getTargetPosition()) {
			Broodwar->printf("PC: onUnitDiscover: found a %s at (%d, %d)", unit->getType().getName().c_str(), unit->getPosition().x(), unit->getPosition().y());
			m_probe->stop();
			m_callback(m_probe, unit);
			SIGNAL_OFF_FRAME(ProbeControl);
			Signal::onUnitDiscover().disconnect(boost::bind(&ProbeControl::onUnitDiscover, this, _1));
			delete this;
	}
}