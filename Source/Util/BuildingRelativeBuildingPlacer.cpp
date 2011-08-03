#include "BuildingRelativeBuildingPlacer.h"

BWAPI::TilePosition BuildingRelativeBuildingPlacer::Place(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance) {
	return this->DirectionalPlace(type, side, distance, orthoDistance);
}

BWAPI::TilePosition BuildingRelativeBuildingPlacer::DirectionalPlace(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance) {
	int iSide = (int)side;
	BWAPI::TilePosition newPos(this->m_relativePosition);

	if (iSide & (int)Top)
	{
		this->m_relativePosition.y() += distance + type.tileHeight();
	}
	else if (iSide & (int)Bottom)
	{
		this->m_relativePosition.y() += distance + this->m_relativeType.tileHeight();
	}
	else if (iSide & (int)Left)
	{
		this->m_relativePosition.x() += distance + type.tileWidth();
	}
	else if (iSide & (int)Right)
	{
		this->m_relativePosition.x() += distance + this->m_relativeType.tileWidth();
	}
	else
	{
		::MessageBoxA(0, "Why the fuck would you try to use that side of a building?\nBuildingRelativeBuildingPlacer::DirectionalPlace throwing BadSideException", "EXCEPTION", 0);
		throw new BadSideException();
	}

	OrthoAdjust(type, iSide, newPos, orthoDistance);
	return newPos;
}

int BuildingRelativeBuildingPlacer::findCenter(int in)
{
	switch (in)
		{
		case 1:
		default:
			return 0;
		case 2:
		case 3:
			return 1;
		case 4:
		case 5:
			return 2;
		}
}

BWAPI::TilePosition BuildingRelativeBuildingPlacer::OrthoAdjust(BWAPI::UnitType const& type, int const& iSide, BWAPI::TilePosition& curPos, int orthoDistance) {

	int& orthoLine = (iSide & (int)Top) || (iSide & (int)Bottom) ? curPos.x() : curPos.y();

	if ((iSide & (int)OrthoLineRight) || (iSide & (int)OrthoLineBottom))
		orthoLine += ((iSide & (int)Top) || (iSide & (int)Bottom) ? this->m_relativeType.tileWidth() : this->m_relativeType.tileHeight()) + orthoDistance;
	else if ((iSide & (int)OrthoLineCenter))
		orthoLine += findCenter((iSide & (int)Top) || (iSide & (int)Bottom) ? this->m_relativeType.tileWidth() : this->m_relativeType.tileHeight());
	else
		orthoLine += orthoDistance;

	if ((iSide & (int)CenterOnOrthoLine))
		orthoLine -= findCenter((iSide & (int)Top) || (iSide & (int)Bottom) ? type.tileWidth() : type.tileHeight());

}

