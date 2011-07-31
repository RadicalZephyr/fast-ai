#include "NexusBehaviour.h"
#include "FunctionObjects/DistanceSorter.h"

using namespace BWAPI;

const int NexusBehaviour::s_mineralDistance = 270;

NexusBehaviour::NexusBehaviour(BWAPI::Unit &nexus): m_nexus(nexus),
										  m_gas(),
										  m_minerals(),
										  m_minGatherers(),
										  m_gasGatherers(),
										  m_shouldBuild(true) {
	findMinerals();
}

void NexusBehaviour::postBuild(BWAPI::Unit *unit) {
	// TODO: Add functionality for calling addGasser
	addMiner(unit);
}

bool NexusBehaviour::shouldBuild(BWAPI::UnitType *) {
	return m_shouldBuild;
}

//BWAPI::UnitType *setBuildType(void) {
//	return &(UnitTypes::getUnitType("Protoss Probe"));
//}

//////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////

bool NexusBehaviour::addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList) {
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

bool NexusBehaviour::addMiner(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_minGatherers, m_minerals);
}

bool NexusBehaviour::addGasser(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_gasGatherers, m_gas);
}

void NexusBehaviour::findMinerals(void) {
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