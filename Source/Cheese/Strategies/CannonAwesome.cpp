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
	::MessageBoxA(0, "BLARGH", "BLARGH", 0);
	Unit* thisOne = getGasPlacement((Position(this->enemyStartLocation)));
	//BuildingRelativeBuildingPlacer gas (*thisOne);
	Position here = (Position(this->enemyStartLocation));
	TilePosition Pylon, Forge, Cannon, Gateway;
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
	m_probe->build(Pylon,UnitTypes::Protoss_Pylon);
	bool built;
	built = false;
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


