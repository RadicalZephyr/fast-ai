#include "CannonAwesome.h"
#include "Base.h"
#include <BWAPI.h>
#include <set>
#include "Util/RelativeSide.h"
#include "BaseManager\BaseManager.h"
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

#define TRY_CANNON_PLACE if(Cannon.isValid()) m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Photon_Cannon, Cannon, true, boost::bind(&CannonAwesome::attemptEarlyRecover, this, _1, _2)))

void CheeseStrategies::CannonAwesome::onUnitDiscover(BWAPI::Unit *unit) {
	if (unit->getType().isResourceContainer() && !unit->getType().isMineralField()) {
		Signal::onUnitDiscover().disconnect(boost::bind(&CheeseStrategies::CannonAwesome::onUnitDiscover, this, _1));
		
		//m_probe->move(g_position.unitVectorRelativeTo(Position(getEnemyStartLocation()), unit->getPosition()) * 15);
		Unit* thisOne = unit; // getGasPlacement((Position(this->getEnemyStartLocation())));

		TilePosition geyserTile = thisOne->getTilePosition();

		//BuildingRelativeBuildingPlacer gas (*thisOne);
		Position here = (Position(this->getEnemyStartLocation()));

		TilePosition Pylon, Forge, Cannon, Gateway, CannonForGateway;

		RelativeSide geyser(thisOne);

		m_buildOrder = new BuildOrder(boost::bind(&CheeseStrategies::CannonAwesome::onBuildEnd, this, _1));

		if (thisOne->getPosition().y() - here.y() > 0)
		{ //Geyser Below
			Pylon = geyser.Place(UnitTypes::Protoss_Pylon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0);
			Forge = geyser.Place(UnitTypes::Protoss_Forge, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0);
			Cannon = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);
			Gateway = geyser.Place(UnitTypes::Protoss_Gateway, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
			if (!Gateway.isValid())
				CannonForGateway = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
		}
		else
		{ //Geyser Above
			Pylon = geyser.Place(UnitTypes::Protoss_Pylon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0);
			Forge = geyser.Place(UnitTypes::Protoss_Forge, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0);
			Cannon = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);
			Gateway = geyser.Place(UnitTypes::Protoss_Gateway, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
			if (!Gateway.isValid())
				CannonForGateway = geyser.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 2, 0);
		}
		/**/

			m_printer.printf("enemy gas: (%d, %d)\nEnemyStartLocation: (%d, %d)\nPylon (%d, %d)\nForge (%d, %d)\nCannon (%d, %d)\nGateway (%d, %d)",
			thisOne->getPosition().x(), thisOne->getPosition().y(),
			here.x(), here.y(), Pylon.x(), Pylon.y(), Forge.x(), Forge.y(), Cannon.x(), Cannon.y(), Gateway.x(), Gateway.y());

		RelativeSide pylon(UnitTypes::Protoss_Pylon, Pylon);

		if (!Cannon.isValid())
		{
			this->recoverEcon();
			BaseManagerSet::iterator Grr = g_baseManagers . begin();
			(*Grr)->getControllee()->addProbe(m_probe);

			return;
		}

		m_probe->move(BWAPI::Position(Cannon));
		m_buildOrder->idlePosition = BWAPI::Position(Cannon);

		m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Pylon, Pylon, false, boost::bind(&CannonAwesome::attemptEarlyRecover, this, _1, _2)));
		m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Forge, Forge, false, boost::bind(&CannonAwesome::attemptEarlyRecover, this, _1, _2)));
		m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Photon_Cannon, Cannon, false, boost::bind(&CannonAwesome::attemptEarlyRecover, this, _1, _2)));
		m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Assimilator, geyserTile, true, boost::bind(&CannonAwesome::recoverEcon, this)));
		if (Gateway.isValid())
			m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Gateway, Gateway, false, boost::bind(&CannonAwesome::recoverEcon, this)));
		else if (CannonForGateway.isValid())
			m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Photon_Cannon, CannonForGateway, false, boost::bind(&CannonAwesome::recoverEcon, this)));
		
		Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0); TRY_CANNON_PLACE;
		Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Left | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
		Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0); TRY_CANNON_PLACE;

		RelativeSide forge(UnitTypes::Protoss_Forge, Forge);

		Pylon = forge.Place(UnitTypes::Protoss_Pylon, RelativeSide::Right | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineLeft, 0, 0);

		if (Pylon.isValid())
		{
			m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Pylon, Pylon, false, boost::bind(&CannonAwesome::recoverEcon, this)));

			pylon = RelativeSide(UnitTypes::Protoss_Pylon, Pylon);

			Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0); TRY_CANNON_PLACE;
			Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Right | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
			Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineRight, 0, 0); TRY_CANNON_PLACE;
		}

		m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Nexus, getEnemyBase()->getTilePosition(), false, boost::bind(&CannonAwesome::recoverEcon, this)));

		RelativeSide nexus(UnitTypes::Protoss_Nexus, getEnemyBase()->getTilePosition());

		UnitSet set = Broodwar->getUnitsInRadius(Position(getEnemyBase()->getTilePosition()), 270);

		Unit* mineral = NULL;

		for (UnitSet::iterator unit = set.begin(); unit != set.end(); unit++) {
			if ((*unit)->getType().isMineralField()) {
				mineral = (*unit);
				break;
			}
		}

		if (mineral != NULL)
		{
			if (mineral->getTilePosition().x() < getEnemyBase()->getTilePosition().x())
			{ // RIGHT
				Pylon = nexus.Place(UnitTypes::Protoss_Pylon, RelativeSide::Right | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);

				if (Pylon.isValid())
				{
					m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Pylon, Pylon, false, boost::bind(&CannonAwesome::recoverEcon, this)));

					pylon = RelativeSide(UnitTypes::Protoss_Pylon, Pylon);

					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Right | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
				}
			}
			else
			{
				Pylon = nexus.Place(UnitTypes::Protoss_Pylon, RelativeSide::Left | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0);

				if (Pylon.isValid())
				{
					m_buildOrder->addOrderElement(BuildOrderElement(UnitTypes::Protoss_Pylon, Pylon, false, boost::bind(&CannonAwesome::recoverEcon, this)));

					pylon = RelativeSide(UnitTypes::Protoss_Pylon, Pylon);

					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Top | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Left | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
					Cannon = pylon.Place(UnitTypes::Protoss_Photon_Cannon, RelativeSide::Bottom | RelativeSide::CenterOnOrthoLine | RelativeSide::OrthoLineCenter, 0, 0); TRY_CANNON_PLACE;
				}
			}
		}

		m_buildOrder->start(m_probe);
	}
}

void CheeseStrategies::CannonAwesome::start()
{   
	if (getEnemyBase() == 0)
		recoverEcon();
	// I don't think that this method is going to be good for anything, except trying to find the geyser manually
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

}

void CheeseStrategies::CannonAwesome::printDebug(void) {

	BaseCheeseStrategy::printDebug();
}

void CheeseStrategies::CannonAwesome::onBuildEnd(BWAPI::Unit* probe)
{
	recoverEcon();
	m_probe = probe;
}

void CheeseStrategies::CannonAwesome::attemptEarlyRecover(BuildOrderElement* orderElement, BWAPI::Unit* builderProbe)
{
	if (BWAPI::Broodwar->self()->minerals() >= 500)
		recoverEcon();
}

void CheeseStrategies::CannonAwesome::recoverEcon()
{
	controls->resumeEcon();
	static bool added;
	if (!added)
	{
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Forge);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Gateway);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Photon_Cannon);
		controls->buildInBase(BWAPI::UnitTypes::Protoss_Pylon);
		added = true;
	}
}