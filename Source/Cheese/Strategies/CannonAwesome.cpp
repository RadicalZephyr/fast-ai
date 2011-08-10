#include "CannonAwesome.h"
#include "Base.h"
#include <BWAPI.h>
#include <set>
#include "Util/RelativeSide.h"
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
		
		//m_probe->move(g_position.unitVectorRelativeTo(Position(getEnemyStartLocation()), unit->getPosition()) * 15);
		Unit* thisOne = unit; // getGasPlacement((Position(this->getEnemyStartLocation())));

		m_geyserTile = thisOne->getTilePosition();

		//BuildingRelativeBuildingPlacer gas (*thisOne);
		Position here = (Position(this->getEnemyStartLocation()));

		TilePosition Pylon, Forge, Cannon, Gateway;

		RelativeSide geyser(thisOne);

		if (thisOne->getPosition().y() - here.y() > 0)
		{ //Geyser Below
			Pylon = geyser.Place(UnitTypes::Protoss_Pylon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0);
			Forge = geyser.Place(UnitTypes::Protoss_Forge, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0);
			Cannon = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);
			Gateway = geyser.Place(UnitTypes::Protoss_Gateway, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
			if (!Gateway.isValid())
				Gateway = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
		}
		else
		{ //Geyser Above
			Pylon = geyser.Place(UnitTypes::Protoss_Pylon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0);
			Forge = geyser.Place(UnitTypes::Protoss_Forge, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0);
			Cannon = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);
			Gateway = geyser.Place(UnitTypes::Protoss_Gateway, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
			if (!Gateway.isValid())
				Gateway = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
		}
		/**/

			m_printer.printf("enemy gas: (%d, %d)\nEnemyStartLocation: (%d, %d)\nPylon (%d, %d)\nForge (%d, %d)\nCannon (%d, %d)\nGateway (%d, %d)",
			thisOne->getPosition().x(), thisOne->getPosition().y(),
			here.x(), here.y(), Pylon.x(), Pylon.y(), Forge.x(), Forge.y(), Cannon.x(), Cannon.y(), Gateway.x(), Gateway.y());

		m_tileList.push_back(Pylon.makeValid());
		m_tileList.push_back(Forge.makeValid());
		m_tileList.push_back(Cannon.makeValid());
		m_tileList.push_back(Gateway.makeValid());

		m_probe->move(BWAPI::Position(Cannon));
	}
}

void CheeseStrategies::CannonAwesome::start()
{   // I don't think that this method is going to be good for anything, except trying to find the geyser manually
	// that is, walking in a circle around their startLocation
	Signal::onUnitDiscover().connect(boost::bind(&CheeseStrategies::CannonAwesome::onUnitDiscover, this, _1));

	BWAPI::Position basePos = this->getEnemyBase()->getPosition();
	BWAPI::Position probePos = this->getEnemyBase()->getPosition();

	m_probe->move(BWAPI::Position(basePos.x() + (-1 * (basePos.x() - probePos.x())), basePos.y() + (-1 * (basePos.y() - probePos.y()))));

	UnitSet nearProbe = m_probe->getUnitsInRadius(270);
	for (UnitSet::iterator itr = nearProbe.begin(); itr != nearProbe.end(); ++itr) {
		if ((*itr)->getType().isResourceContainer() && !(*itr)->getType().isMineralField())  {
			Signal::onUnitDiscover()(*itr);
		}
	}
}


void CheeseStrategies::CannonAwesome::onFrame() {
	for (std::list<BWAPI::TilePosition>::iterator itr = m_tileList.begin(); itr != m_tileList.end(); ++itr) {
		Broodwar->drawCircleMap(Position(*itr).x(), Position(*itr).y(), 25, BWAPI::Colors::Cyan, true);
	}

	if (m_isRunning && m_probe->isIdle()) {

		m_probe->stop();

		switch (m_buildOrder) {
		case 0:
			if (BWAPI::Broodwar->canBuildHere(m_probe, m_tileList.front(), BWAPI::UnitTypes::Protoss_Pylon)
				&& m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Pylon)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			break;
		case 1:
			if (BWAPI::Broodwar->canBuildHere(m_probe, m_tileList.front(), BWAPI::UnitTypes::Protoss_Forge)
				&& m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Forge)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			else if (BWAPI::Broodwar->canBuildHere(m_probe, m_geyserTile, BWAPI::UnitTypes::Protoss_Assimilator)
				&& m_probe->build(m_geyserTile, BWAPI::UnitTypes::Protoss_Assimilator))
			{

			}
			break;
		case 2:
			controls->resumeEcon();
			if (BWAPI::Broodwar->canBuildHere(m_probe, m_tileList.front(), BWAPI::UnitTypes::Protoss_Photon_Cannon)
				&& m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Photon_Cannon)) {
				++m_buildOrder;
				m_tileList.pop_front();
			}
			else if (BWAPI::Broodwar->canBuildHere(m_probe, m_geyserTile, BWAPI::UnitTypes::Protoss_Assimilator)
				&& m_probe->build(m_geyserTile, BWAPI::UnitTypes::Protoss_Assimilator))
			{

			}
			break;
		case 3:
			m_probe->move(Position(m_tileList.front()));
			controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
			if (BWAPI::Broodwar->canBuildHere(m_probe, m_tileList.front(), BWAPI::UnitTypes::Protoss_Gateway)
				&& m_probe->build(m_tileList.front(), BWAPI::UnitTypes::Protoss_Gateway)) {
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
