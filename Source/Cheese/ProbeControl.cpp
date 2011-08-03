#include "ProbeControl.h"
using namespace BWAPI;


//const int NexusManager::s_mineralDistance = 270;
ProbeControl::ProbeControl(BWAPI::Unit *newProbe, onFindCallbackFunction callback) : m_probe(newProbe),
													m_callback(callback)
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

	//Position newPlace(*m_tiles.begin());
	//for(m_startLocations = m_tiles.begin(); m_startLocations != m_tiles.end(); m_startLocations++){
	//	if((*m_startLocations) == myPlace)
	//		m_tiles.erase(m_startLocations);
	//}

	m_scoutLocations = startLocations.cbegin();

	Position nextPlace(*m_scoutLocations);
	nextPlace.makeValid();

	m_probe->move(nextPlace);
}

void ProbeControl::onFrame()
{
	if(256 == m_probe->getPosition().getApproxDistance(m_probe->getTargetPosition())) {

		Position nextPlace(*(++m_scoutLocations));
		nextPlace.makeValid();

		m_probe->move(nextPlace);
	}
}

void ProbeControl::onUnitDiscover(BWAPI::Unit *unit) {
	if (unit->getType().isResourceDepot() && unit->getPlayer() != Broodwar->self() && 
		unit->getTilePosition() == m_probe->getTargetPosition()) {
			m_callback(m_probe, unit);
			SIGNAL_OFF_FRAME(ProbeControl);
			Signal::onUnitDiscover().disconnect(boost::bind(&ProbeControl::onUnitDiscover, this, _1));
			delete this;
	}
}