#pragma once

#include <BWAPI.h>

#include "Important/Common.h"

class BuildingRelativeBuildingPlacer
{
public:
	// Favored order of testing: Top, Bottom, Left, Right
	enum Side
	{
		Vertical = 1,
		Horizontal = 2,

		Top = 4,
		Bottom = 8,
		Left = 16,
		Right = 32,

		TopRight = Top | Right,
		TopLeft = Top | Left,
		BottomRight = Bottom | Right,
		BottomLeft = Bottom | Left,

		NotTop = Bottom | Horizontal,
		NotBottom = Top | Horizontal,
		NotRight = Right | Vertical,
		NotLeft = Left | Vertical,

		Any = 63,

		// This is what side of the relative building to favor the relative lines off of
		OrthoFavorLeft = 64,
		OrthoFavorRight = 128,
		OrthoFavorTop = 256,
		OrthoFavorBottom = 512,
		OrthoFavorCenter = 1024,
	};

	class BadSideException : public std::exception
	{

	};

	BuildingRelativeBuildingPlacer(BWAPI::Unit const& relativeBuilding) : m_relativeType(relativeBuilding.getType()), m_relativePosition(relativeBuilding.getTilePosition()) {}
	BuildingRelativeBuildingPlacer(BWAPI::UnitType relativeBuildingType, BWAPI::TilePosition relativePosition) : m_relativeType(relativeBuildingType), m_relativePosition(relativePosition) {}

	// orthoDistace is the "leeway" from the "OrthoFavor" part of the enum.
	// an orthoDistance of -1 means within the borders of the side of the building
	// an orthoDistance of 0 means "On the line"
	// any other positive orthDistance is the leeway in the orthogonal direction.

	// Will always return the posistion, even if it is potentially invalid.
	// Will throw an exception in extreme circumstances
	BWAPI::TilePosition Place(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance); //Only supports Top/Left/Right/Bottom

	// Will check a location to see if it is a good spot to place it.
	inline bool Check(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance)
	{
		return Place(type, side, distance, orthoDistance).isValid();
	}

	// Will check a location to see if it valid before setting outLocation
	inline bool CheckAndPlace(BWAPI::UnitType const& type, Side const& side, int distance, int orthoDistance, BWAPI::TilePosition& outLocation) { 
		
		BWAPI::TilePosition temp = Place(type, side, distance, orthoDistance);

		if (temp.isValid())
		{
			outLocation = temp;
			return true;
		}
		else
			return false;
	}

private:
	BWAPI::UnitType m_relativeType;
	BWAPI::TilePosition m_relativePosition;
};

typedef BuildingRelativeBuildingPlacer::Side RelativeSide;
