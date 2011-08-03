#include "CannonAwesome.h"
#include "Base.h"
#include <BWAPI.h>
#include <set>
#include "Util/BuildingRelativeBuildingPlacer.h"
using namespace BWAPI;

Unit* getGasPlacement(Position here)
{
	Position posMody, posModx;

	// getGeysers won't tell us where their geyser is UNLESS we've seen it!!!
	// so this is almost GUARANTEED to do the WRONG thing (i.e. it's probably going to grab our geyser)
	std::set<Unit*> gas = Broodwar->getGeysers();
	std::set<Unit*>::iterator g;
	g = gas.begin();
	Unit* thisOne = *g;
	for (g = gas.begin(); g != gas.end(); g++)
		//for (unsigned int i = 1; i < gas.size(); i++)
	{
		//if (abs((*g)->getPosition() - here) < 300)
		if ((*g)->getPosition().getDistance(here) < thisOne->getPosition().getDistance(here))
		{
			Broodwar->pingMinimap(thisOne->getPosition());
			thisOne = *g;
		}
	}
	return thisOne;
	//	if (thisOne->getPosition().y() - here.y() < 0)
	//{
	//	return thisOne->getTilePosition() + TilePosition(-1,-2);
	//}
	//if (thisOne->getPosition().y() - here.y() > 0)
	//{
	//	return thisOne->getTilePosition() + TilePosition(2,3);
	//}
	//if (thisOne->getPosition().x() - here.x() < 0)
	//{
	//	return thisOne->getTilePosition() + TilePosition(-2,3);
	//}
	//if (thisOne->getPosition().x() - here.x() > 0)
	//{
	//	return thisOne->getTilePosition() + TilePosition(+2,-1);
	//}
}

void CheeseStrategies::CannonAwesome::onUnitDiscover(BWAPI::Unit *unit) {
	if (unit->getType().isResourceContainer() && !unit->getType().isMineralField()) {
		Signal::onUnitDiscover().disconnect(boost::bind(&CheeseStrategies::CannonAwesome::onUnitDiscover, this, _1));
		m_probe->move(unit->getPosition() + Position(10, 10));
		Unit* thisOne = getGasPlacement((Position(this->getEnemyStartLocation())));

		//BuildingRelativeBuildingPlacer gas (*thisOne);
		Position here = (Position(this->getEnemyStartLocation()));

		TilePosition Pylon, Forge, Cannon, Gateway;

		/*  !!!!!!!!!!!!!!!!!!!! ATTENTION : all of these tile positions are NOT doing what you want them to
		if you look in the top left corner of the map, you
		will see circles that are located at these calculated positions*/
		if (thisOne->getPosition().y() - here.y() < 0)
		{

			Pylon = TilePosition(thisOne->getPosition().x()-1*TILE_SIZE, thisOne->getPosition().y()-2*TILE_SIZE);
			Forge = TilePosition(thisOne->getPosition().x()+3*TILE_SIZE, thisOne->getPosition().y()-3*TILE_SIZE);
			Cannon = TilePosition(thisOne->getPosition().x()+1*TILE_SIZE, thisOne->getPosition().y()-2*TILE_SIZE);

		}
		if (thisOne->getPosition().y() - here.y() > 0)
		{

			Pylon = TilePosition(thisOne->getPosition().x()+2*TILE_SIZE, thisOne->getPosition().y()+3*TILE_SIZE);
			Forge = TilePosition(thisOne->getPosition().x()+3*TILE_SIZE, thisOne->getPosition().y()-3*TILE_SIZE);
			Cannon = TilePosition(thisOne->getPosition().x()+1*TILE_SIZE, thisOne->getPosition().y()-2*TILE_SIZE);
		}
		if (thisOne->getPosition().x() - here.x() < 0)
		{
			Pylon = TilePosition(thisOne->getPosition().x()-2*TILE_SIZE, thisOne->getPosition().y()+3*TILE_SIZE);
			Forge = TilePosition(thisOne->getPosition().x()+3*TILE_SIZE, thisOne->getPosition().y()-3*TILE_SIZE);
			Cannon = TilePosition(thisOne->getPosition().x()+1*TILE_SIZE, thisOne->getPosition().y()-2*TILE_SIZE);
		}
		if (thisOne->getPosition().x() - here.x() > 0)
		{
			Pylon = TilePosition(thisOne->getPosition().x()+2*TILE_SIZE, thisOne->getPosition().y()-1*TILE_SIZE);
			Forge = TilePosition(thisOne->getPosition().x()+3*TILE_SIZE, thisOne->getPosition().y()-3*TILE_SIZE);
			Cannon = TilePosition(thisOne->getPosition().x()+1*TILE_SIZE, thisOne->getPosition().y()-2*TILE_SIZE);
		}
		/**/

			m_printer.printf("enemy gas: (%d, %d)\nEnemyStartLocation: (%d, %d)\nPylon (%d, %d)\nForge (%d, %d)\nCannon (%d, %d)\nGateway (%d, %d)",
			thisOne->getPosition().x(), thisOne->getPosition().y(),
			here.x(), here.y(), Pylon.x(), Pylon.y(), Forge.x(), Forge.y(), Cannon.x(), Cannon.y(), Gateway.x(), Gateway.y());

		m_tileList.push_back(Pylon.makeValid());
		m_tileList.push_back(Forge.makeValid());
		m_tileList.push_back(Cannon.makeValid());
		m_tileList.push_back(Gateway.makeValid());

		//m_probe->move(BWAPI::Position(Pylon));
		//m_probe->build(Pylon,UnitTypes::Protoss_Pylon);
		//bool built;
		//built = false;
		//while(!built)
		//{
		//	built = m_probe->build(Forge,UnitTypes::Protoss_Forge);
		//}
		//built = false;
		//while(!built)
		//{
		//	built = m_probe->build(Cannon,UnitTypes::Protoss_Photon_Cannon);
		//}
	}
}

void CheeseStrategies::CannonAwesome::start()
{   // I don't think that this method is going to be good for anything, except trying to find the geyser manually
	// that is, walking in a circle around their startLocation
	Signal::onUnitDiscover().connect(boost::bind(&CheeseStrategies::CannonAwesome::onUnitDiscover, this, _1));

	UnitSet nearProbe = m_probe->getUnitsInRadius(270);
	for (UnitSet::iterator itr = nearProbe.begin(); itr != nearProbe.end(); ++itr) {
		if ((*itr)->getType().isResourceContainer() && !(*itr)->getType().isMineralField())  {
			Signal::onUnitDiscover()(*itr);
		}
	}

	Position newPos(getEnemyStartLocation());
	newPos += Position(20, 20);
	m_probe->move(newPos);

	newPos += Position(-40, 20);
	m_probe->move(newPos, true);

	newPos += Position(0, -40);
	m_probe->move(newPos, true);

	newPos += Position(40, 0);
	m_probe->move(newPos, true);
}


void CheeseStrategies::CannonAwesome::onFrame() {
	for (std::list<BWAPI::TilePosition>::iterator itr = m_tileList.begin(); itr != m_tileList.end(); ++itr) {
		Broodwar->drawCircleMap(Position(*itr).x(), Position(*itr).y(), 25, BWAPI::Colors::Cyan, true);
	}

	if (m_isRunning && m_probe->isIdle()) {
		switch (m_buildOrder) {
		case 0:
			if (m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Pylon)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}

			break;
		case 1:
			if (m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Forge)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			break;
		case 2:
			if (m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Photon_Cannon)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			break;
		case 3:
			if (m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Gateway)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			break;
		default:
			break;
		}

	}
}

void CheeseStrategies::CannonAwesome::printDebug(void) {
	BWAPI::Broodwar->drawTextMap(m_probe->getPosition().x()+10, m_probe->getPosition().y(), 
		"Build step: %d\n", m_buildOrder);

	for (std::list<BWAPI::TilePosition>::iterator itr = m_tileList.begin(); 
		itr != m_tileList.end(); ++itr) {
			BWAPI::Broodwar->drawCircleMap(itr->x(), itr->y(), 15, BWAPI::Colors::Cyan, true);
	}
	BaseCheeseStrategy::printDebug();
}