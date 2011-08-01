#include "BuildsWhat.h"

namespace BWAPI {

	BuildsWhat::BuildsWhat(void): m_BuildsWhatMap() {
		UnitTypeSet allTypes = UnitTypes::allUnitTypes();

		for (UnitTypeSet::const_iterator type = allTypes.begin();
				type != allTypes.end(); ++type) {

			int whatBuildsID = type->whatBuilds().first.getID();
			BuildsWhatMap::iterator itr = m_BuildsWhatMap.find(whatBuildsID);

			if (m_BuildsWhatMap.end() != itr) {
				// If in map, insert a new value
				UnitTypeSet buildSet = m_BuildsWhatMap[whatBuildsID];
				buildSet.insert(*type);
			} else {
				UnitTypeSet newSet;
				newSet.insert(*type);
				m_BuildsWhatMap[whatBuildsID] = newSet;
			}
		}
	}
}