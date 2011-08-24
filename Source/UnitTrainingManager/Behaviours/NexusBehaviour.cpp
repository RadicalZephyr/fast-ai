#include "NexusBehaviour.h"
#include "FunctionObjects/DistanceSorter.h"
#include "BaseManager/BaseManager.h"

using namespace BWAPI;

const int NexusBehaviour::s_mineralDistance = 270;

NexusBehaviour::NexusBehaviour(BWAPI::Unit *nexus): m_nexus(nexus),
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
}


void NexusBehaviour::postBuild(BWAPI::Unit *unit) {
	// TODO: Add functionality for calling addGasser
	//Broodwar->printf("NB postBuild");

	IUnitTrainingManagerBehaviour::postBuild(unit);

	addProbe(unit); // !!!!!!
}

BWAPI::UnitType NexusBehaviour::shouldBuild(BWAPI::UnitType ) {
	if (m_shouldBuild && ((m_minerals.size() * 2.5f) > m_minGatherers.size()) && (Broodwar->self()->supplyUsed() > 17 || Broodwar->self()->supplyUsed() < 14 || g_resourceManager.minerals() >= 200)) {// &&  // TODO: Uncomment these lines when gas production is implemented
		return UnitTypes::Protoss_Probe;									 //((m_gas.size() * 3) > m_gasGatherers.size());
	} else {
		return UnitTypes::None;
	}
}

void NexusBehaviour::addProbe(Unit *unit) {
	// Broodwar->printf("Gas Begin type is %s", (*m_gas.begin())->getType().getName().c_str());
	if ((*m_gas.begin())->getType() == BWAPI::UnitTypes::Protoss_Assimilator && m_gasGatherers.size() < 3) {
		addGasser(unit);
	} else {
		addMiner(unit);
	}
}

Unit *NexusBehaviour::removeProbe(void) {
	UnitSet::iterator first = m_minGatherers.begin();
	m_minGatherers.erase(first);
	return *first;
}


BWAPI::TilePosition NexusBehaviour::startGas(void) {
	if (m_minGatherers.size() > 3 && m_gasGatherers.size() < 3) {
		BWAPI::Unit *gasProbe1 = removeProbe();

		addGasser(gasProbe1);

		return (*m_gas.begin())->getTilePosition();
	}
	else {
		Broodwar->printf("Couldn't start gas");
		return BWAPI::TilePosition(0,0);
	}
}


//////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////

void NexusBehaviour::printDebug(void) {
	std::for_each(m_minerals.begin(), m_minerals.end(), boost::bind(&drawCircleOnUnit, _1, BWAPI::Colors::Red));
	std::for_each(m_minGatherers.begin(), m_minGatherers.end(), boost::bind(&drawCircleOnUnit, _1, BWAPI::Colors::Orange));
  std::for_each(m_gas.begin(), m_gas.end(), boost::bind(&drawCircleOnUnit, _1, BWAPI::Colors::Blue));
  std::for_each(m_gasGatherers.begin(), m_gasGatherers.end(), boost::bind(&drawCircleOnUnit, _1, BWAPI::Colors::Teal));
}

bool NexusBehaviour::isMyUnitSelected(void) {
	return m_nexus->isSelected();
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

bool NexusBehaviour::addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList, bool shiftClick) {
	if (probe == 0) {
		return false;
	}
    std::pair<UnitSet::iterator, bool> isIn = gathererSet.insert(probe);

    if (isIn.second) {
        Unit *min = resourceList.front();
        resourceList.pop_front();
        probe->rightClick(min, shiftClick);
        resourceList.push_back(min);
    }
    return isIn.second;
}

bool NexusBehaviour::addMiner(BWAPI::Unit *probe) {
	return addProbeToGatherers(probe, m_minGatherers, m_minerals);
}

bool NexusBehaviour::addGasser(BWAPI::Unit *probe) {

	if (m_gas.front()->getType() == UnitTypes::Resource_Vespene_Geyser) {
		probe->build(m_gas.front()->getTilePosition(), UnitTypes::Protoss_Assimilator);
		return addProbeToGatherers(probe, m_minGatherers, m_minerals, true);
	} else if (m_gas.front()->isBeingConstructed()) {
		return addProbeToGatherers(probe, m_minGatherers, m_minerals, true);
	} else {
		return addProbeToGatherers(probe, m_gasGatherers, m_gas);
	}
}

void NexusBehaviour::findMinerals(void) {
    UnitSet& aroundNexus = Broodwar->getUnitsInRadius(m_nexus->getPosition(), s_mineralDistance);
    
    m_minerals.assign(aroundNexus.begin(), aroundNexus.end());

	UnitList startProbes;

    // Now we filter the list for only mineral items with isMineralField()
    for (UnitList::iterator unit = m_minerals.begin(); unit != m_minerals.end(); unit++) {
		if ((*unit)->getType().isWorker()) {
			startProbes.push_front(*unit);
			m_minerals.erase(unit);
		} else if ((*unit)->getType() == UnitTypes::Resource_Vespene_Geyser) {
			m_minerals.erase(unit);
			m_gas.push_front(*unit);
		} else if (!(*unit)->getType().isMineralField()) {
            m_minerals.erase(unit);
        }
		else if ((*unit)->getType() == UnitTypes::Resource_Vespene_Geyser) {
			m_gas.push_front(*unit);
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
