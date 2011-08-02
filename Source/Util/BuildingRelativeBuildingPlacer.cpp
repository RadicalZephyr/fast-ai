#include "BuildingRelativeBuildingPlacer.h"



BWAPI::TilePosition BuildingRelativeBuildingPlacer::Place(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance) {
	int iSide = (int)side;
	
	if (iSide & (int)Top)
	{
		BWAPI::TilePosition newPos(this->m_relativePosition);
		this->m_relativePosition.y() += distance + type.tileHeight();

		return newPos;
	}
	else if (iSide & (int)Bottom)
	{
		BWAPI::TilePosition newPos(this->m_relativePosition);
		this->m_relativePosition.y() += distance + this->m_relativeType.tileHeight();

		return newPos;
	}
	else if (iSide & (int)Left)
	{
		BWAPI::TilePosition newPos(this->m_relativePosition);
		this->m_relativePosition.x() += distance + type.tileWidth();

		return newPos;
	}
	else if (iSide & (int)Right)
	{
		BWAPI::TilePosition newPos(this->m_relativePosition);
		this->m_relativePosition.x() += distance + this->m_relativeType.tileWidth();

		return newPos;
	}
	else
		throw new BadSideException();
}
