#include "NexusFunc.h"
#include "DistanceSorter.h"

using namespace BWAPI;

const int NexusFunc::s_mineralDistance = 270;

NexusFunc::NexusFunc(BWAPI::Unit &nexus): m_nexus(nexus),
										  m_gas(),
										  m_minerals(),
										  m_minGatherers(),
										  m_gasGatherers(),
										  m_shouldBuild(true) {
	findMinerals();
}

void NexusFunc::operator()(BWAPI::Unit *unit) {
	// TODO: Add functionality for calling
	addMiner(unit);
}

bool NexusFunc::operator()(BWAPI::UnitType) {
	return m_shouldBuild;
}


//////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////

bool NexusFunc::addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList) {
	if (probe == 0) {
		//Broodwar->printf("ERROR: addMiner: null pointer");
		return false;
	}
    std::pair<UnitSet::iterator, bool> isIn = gathererSet.insert(probe);

    if (isIn.second) {
        Unit *min = resourceList.front();
        resourceList.pop_front();
        probe->rightClick(min);
        resourceList.push_back(min);
    }
    return isIn.second;
}

bool NexusFunc::addMiner(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_minGatherers, m_minerals);
}

bool NexusFunc::addGasser(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_gasGatherers, m_gas);
}

void NexusFunc::findMinerals(void) {
    UnitSet& aroundNexus = Broodwar->getUnitsInRadius(m_nexus.getPosition(), s_mineralDistance);
    
    m_minerals.assign(aroundNexus.begin(), aroundNexus.end());

    // Now we filter the list for only mineral items with isMineralField()
    for (UnitList::iterator unit = m_minerals.begin(); unit != m_minerals.end(); unit++) {
        if (!(*unit)->getType().isMineralField()) {
            m_minerals.erase(unit);
        }
    }

    m_minerals.sort(DistanceSorter(m_nexus));
    // We are now ready to start adding miners
}