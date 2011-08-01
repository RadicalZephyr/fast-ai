#pragma once

#include "Important\Common.h"
#include "boost\unordered_map.hpp"

typedef boost::unordered_map<int, UnitTypeSet> BuildsWhatMap;

namespace BWAPI {

	class BuildsWhat
	{
	public:
		BuildsWhat(void);

		UnitTypeSet const &lookupBuildsWhat(UnitType const &unitType) const {return m_BuildsWhatMap.at(unitType.getID());}

	private:

		BuildsWhatMap m_BuildsWhatMap;

		// Unimplemented to disallow assignment/copying
		BuildsWhat(BuildsWhat const &);
		BuildsWhat &operator=(BuildsWhat const &);
	};
}