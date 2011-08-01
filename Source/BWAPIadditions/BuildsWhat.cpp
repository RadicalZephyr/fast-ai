#include "BuildsWhat.h"

namespace BWAPI {

	BuildsWhat::BuildsWhat(void): m_BuildsWhatMap() {
		UnitTypeSet allTypes = UnitTypes::allUnitTypes();

		for (UnitTypeSet::const_iterator type = allTypes.begin();
				type != allTypes.end(); ++type) {

			std::string whatBuildsName = type->whatBuilds().first.getName();
			BuildsWhatMap::iterator itr = m_BuildsWhatMap.find(whatBuildsName);

			if (m_BuildsWhatMap.end() != itr) {
				// If in map, insert a new value
				Broodwar->printf("Inserting a new value\n%s builds %s", 
					type->whatBuilds().first.getName().c_str(),
					type->getName().c_str());
				UnitTypeSet buildSet = m_BuildsWhatMap[whatBuildsName];
				buildSet.insert(*type);
				m_BuildsWhatMap[whatBuildsName] = buildSet;
			} else {
				// Not in map already, assign a new set
				Broodwar->printf("Assigning a new set for\n%s builds %s", 
					type->whatBuilds().first.getName().c_str(),
					type->getName().c_str());
				UnitTypeSet newSet;
				newSet.insert(*type);
				m_BuildsWhatMap[whatBuildsName] = newSet;
			}
		}
	}
}