#include "CannonAwesome.h"
#include "Base.h"
#include <BWAPI.h>
#include <set>
#include "Util/BuildingRelativeBuildingPlacer.h"
using namespace BWAPI;

Unit* getGasPlacement(Position here)
{
	Position posMody, posModx;

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

void CheeseStrategies::CannonAwesome::start()
{
	//::MessageBoxA(0, "BLARGH", "BLARGH", 0);
	Unit* thisOne = getGasPlacement((Position(this->getEnemyStartLocation())));

	//BuildingRelativeBuildingPlacer gas (*thisOne);
	Position here = (Position(this->getEnemyStartLocation()));

	Broodwar->printf("enemy gas: (%d, %d)\nEnemyStartLocation: (%d, %d)",
						thisOne->getPosition().x(), thisOne->getPosition().y(),
						here.x(), here.y());

	TilePosition Pylon, Forge, Cannon, Gateway;

/*  !!!!!!!!!!!!!!!!!!!! ATTENTION : all of these tile positions are NOT doing what you want them to
									  if you look in the top left corner of the map, you
									  will see circles that are located at these calculated positions*/
	if (thisOne->getPosition().y() - here.y() < 0)
	{

		Pylon = thisOne->getTilePosition() + TilePosition(-1,-2);
		Forge = thisOne->getTilePosition() + TilePosition(3,-3);
		Cannon = thisOne->getTilePosition() + TilePosition(1,-2);

	}
	if (thisOne->getPosition().y() - here.y() > 0)
	{

		Pylon = thisOne->getTilePosition() + TilePosition(2,3);
	}
	if (thisOne->getPosition().x() - here.x() < 0)
	{
		Pylon = thisOne->getTilePosition() + TilePosition(-2,3);
	}
	if (thisOne->getPosition().x() - here.x() > 0)
	{
		Pylon = thisOne->getTilePosition() + TilePosition(+2,-1);
	}
	/**/

	m_tileList.push_back(Pylon.makeValid());
	m_tileList.push_back(Forge.makeValid());
	m_tileList.push_back(Cannon.makeValid());
	m_tileList.push_back(Gateway.makeValid());

	m_probe->move(BWAPI::Position(Pylon));
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


void CheeseStrategies::CannonAwesome::onFrame() {
	for (std::list<BWAPI::TilePosition>::iterator itr = m_tileList.begin(); itr != m_tileList.end(); ++itr) {
		Broodwar->drawCircleMap(itr->x(), itr->y(), 25, BWAPI::Colors::Cyan, true);
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