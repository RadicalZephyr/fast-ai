#include "NexusBehaviour.h"
#include "FunctionObjects/DistanceSorter.h"
#include "BaseManager/BaseManager.h"

using namespace BWAPI;

const int NexusBehaviour::s_mineralDistance = 270;

NexusBehaviour::NexusBehaviour(BWAPI::Unit &nexus): m_nexus(nexus),
										  m_gas(),
										  m_minerals(),
										  m_minGatherers(),
										  m_gasGatherers(),
										  m_shouldBuild(true) {
	findMinerals();
	Signal::onFrame().connect(boost::bind(&NexusBehaviour::onFrame, this));
	Signal::onFriendlyUnitDestroy().connect(boost::bind(&NexusBehaviour::onFriendlyUnitDestroy, this, _1));
	Signal::onNeutralUnitDestroy().connect(boost::bind(&NexusBehaviour::onNeutralUnitDestroy, this, _1));

	g_baseManagers.insert(BaseManagerPtr(new BaseManager(this)));
}

void NexusBehaviour::onFrame(void) {
	// This is meant to... what?  Call it's delegate/behaviour's methods?
	// Could have it do two things, try and build a pylon, try and build an extractor
}


void NexusBehaviour::postBuild(BWAPI::Unit *unit) {
	// TODO: Add functionality for calling addGasser
	//Broodwar->printf("NB postBuild");
	addMiner(unit);
}

BWAPI::UnitType NexusBehaviour::shouldBuild(BWAPI::UnitType ) {
	if (m_shouldBuild && ((m_minerals.size() * 2.5f) > m_minGatherers.size())) {// &&  // TODO: Uncomment these lines when gas production is implemented
		return UnitTypes::Protoss_Probe;									 //((m_gas.size() * 3) > m_gasGatherers.size());
	} else {
		return UnitTypes::None;
	}
}

void NexusBehaviour::addProbe(Unit *unit) {
	addMiner(unit);
}

Unit *NexusBehaviour::removeProbe(void) {
	UnitSet::iterator first = m_minGatherers.begin();
	m_minGatherers.erase(first);
	return *first;
}


//////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////

void drawCircleOnUnit(BWAPI::Unit *unit) {
	BWAPI::Position pos(unit->getPosition());
	Broodwar->drawCircleMap(pos.x(), pos.y(), 15, Colors::Orange);
}

void NexusBehaviour::printDebug(void) {
	std::for_each(m_minerals.begin(), m_minerals.end(), drawCircleOnUnit);
	std::for_each(m_minGatherers.begin(), m_minGatherers.end(), drawCircleOnUnit);
}

bool NexusBehaviour::isMyUnitSelected(void) {
	return m_nexus.isSelected();
}

bool NexusBehaviour::removeProbeFromGatherers(BWAPI::Unit *probe) {
	if (probe == 0) {
		return false;
	}

	if (m_minGatherers.erase(probe)) {
		return true;
	} else {
		return m_gasGatherers.erase(probe) != 0;
	}
}

bool NexusBehaviour::addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList) {
	if (probe == 0) {
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
	//Broodwar->printf("NB addMiner");
	return addProbeToGatherers(probe, m_minGatherers, m_minerals);
}

bool NexusBehaviour::addGasser(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_gasGatherers, m_gas);
}

void NexusBehaviour::findMinerals(void) {
    UnitSet& aroundNexus = Broodwar->getUnitsInRadius(m_nexus.getPosition(), s_mineralDistance);
    
    m_minerals.assign(aroundNexus.begin(), aroundNexus.end());

	UnitList startProbes;

    // Now we filter the list for only mineral items with isMineralField()
    for (UnitList::iterator unit = m_minerals.begin(); unit != m_minerals.end(); unit++) {
		if ((*unit)->getType().isWorker()) {
			startProbes.push_front(*unit);
			m_minerals.erase(unit);
		} else if (!(*unit)->getType().isMineralField()) {
            m_minerals.erase(unit);
        }
    }

    m_minerals.sort(DistanceSorter(m_nexus));
    // We are now ready to start adding miners
	
	if (!startProbes.empty()) {
		//std::for_each(startProbes.begin(), startProbes.end(), std::bind1st(std::mem_fun(&NexusBehaviour::addMiner), this));
		for (UnitList::iterator probe = startProbes.begin(); probe != startProbes.end(); probe++) {
			addMiner(*probe);
		}
	}
}
