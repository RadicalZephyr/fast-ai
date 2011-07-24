#include "NexusManager.h"

using namespace BWAPI;


const int NexusManager::s_mineralDistance = 270;

NexusManager::NexusManager(Unit &theNexus): c_unitTrainTime(theNexus.getType().getRace().getWorker().buildTime()),
											m_trainingUnit(0),
											m_trainingTime(),
                                            m_minGatherers(),
                                            m_gasGatherers(),
                                            m_minerals(),
                                            m_builder(0),
                                            m_nexus(theNexus) {
												Broodwar->printf("constant time value: %d", c_unitTrainTime);
    if (m_nexus.getType().isResourceDepot()) {
        buildProbe();
    } else {
        // Should invalidate the manager somehow if passed a non-ResourceDepot
        std::invalid_argument badArg("ERROR: NexusManager: Non-ResourceDepot object passed to constructor");
        throw badArg;
    }
}

void NexusManager::checkTraining() {
	if (m_trainingTime.isDone()) {
		addMiner(m_trainingUnit);
		buildProbe();
	}
}

void NexusManager::buildProbe() {
    if (!m_nexus.isTraining() && 
		(Broodwar->self()->minerals() >= 50) && 
        (Broodwar->self()->supplyUsed() < Broodwar->self()->supplyTotal())) {

        Race myRace = m_nexus.getType().getRace();
        m_nexus.train(myRace.getWorker());
		m_trainingUnit = 0;
    }
}

bool NexusManager::addMiner(BWAPI::Unit *probe) {
	if (probe == 0) {
		//Broodwar->printf("ERROR: addMiner: null pointer");
		return false;
	}
    std::pair<UnitSet::iterator, bool> isIn = m_minGatherers.insert(probe);

    if (isIn.second) {
        Unit *min = m_minerals.front();
        m_minerals.pop_front();
        probe->rightClick(min);
        m_minerals.push_back(min);
    }
    return isIn.second;
}

bool NexusManager::addGasser(BWAPI::Unit *probe) {
    m_gasGatherers.insert(probe);

    Broodwar->printf("UNIMP: addGasser");
	return false;
}

void NexusManager::onUnitCreate(Unit* unit) {

	if (m_nexus.isTraining() && !unit->isCompleted() &&
		m_nexus.getPosition().getApproxDistance(unit->getPosition()) < s_mineralDistance) {
		Broodwar->printf("Inside unitcreate if");
		m_trainingUnit = unit;
		m_trainingTime.reset(c_unitTrainTime);
	}
}

void NexusManager::onFrame(void) {
    //Broodwar->drawBoxMap(m_nexus.getPosition().x()-70, m_nexus.getPosition().y()+35, 
    //                      m_nexus.getPosition().x()+60, m_nexus.getPosition().y()+85, Colors::Red);
    //Broodwar->printf("Time till done building: %d", m_nexus.getRemainingTrainTime());
    Broodwar->drawTextScreen(40, 40, "unitTraining isDone: %s\namountDone: %d", 
			(m_trainingTime ? "yes" : "no"), m_trainingTime.amountDone() );

	checkTraining();
}

void NexusManager::findMinerals(void) {
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
