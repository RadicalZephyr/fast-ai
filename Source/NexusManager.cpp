#include "NexusManager.h"

using namespace BWAPI;



NexusManager::NexusManager(Unit &theNexus): remainingBuildFrames(0),
                                                   minGatherers(),
                                                   gasGatherers(),
                                                   minerals(),
                                                   builder(0),
                                                   nexus(theNexus) {
    if (nexus.getType().isResourceDepot()) {
        buildProbe();
    } else {
        // Should invalidate the manager somehow if passed a non-ResourceDepot
        std::invalid_argument badArg("Non-ResourceDepot object passed to constructor");
        throw badArg;
    }
}

bool NexusManager::findBuiltProbe() {
    Broodwar->printf("Attempting to find probe");
    Position nexPos = nexus.getPosition();

    UnitSet probes = Broodwar->getUnitsInRectangle(nexPos.x()-70, nexus.getPosition().y()+35, 
        nexus.getPosition().x()+60, nexPos.y()+85);
    bool addedProbe = false;

    for (UnitSet::const_iterator probe = probes.begin();
        probe != probes.end(); ++probe) {
            if ((*probe)->getType().isWorker()) {
                if (addMiner(*probe)) {
                    addedProbe = true;
                }
            }
    }
    return addedProbe;
}

void NexusManager::adjustRemainingFrames() {
    if (lookingForProbe) {
        lookingForProbe = !findBuiltProbe();

    } else if (0 == remainingBuildFrames  && building) {
        remainingBuildFrames = nexus.getRemainingTrainTime();

    } else if (1 == remainingBuildFrames) {
        building = false;
        Broodwar->printf("Training done, setting look flag");
        lookingForProbe = true;
        --remainingBuildFrames;

    } else if (remainingBuildFrames > 1) {
        --remainingBuildFrames;
    }
}

void NexusManager::buildProbe() {
    if (!building && (0 == remainingBuildFrames) && 
        (Broodwar->self()->minerals() >= 50) && 
        (Broodwar->self()->supplyUsed() < Broodwar->self()->supplyTotal())) {
        building = true;
        Broodwar->printf("building A Probe");
        Broodwar->printf("Buildframes: %d", remainingBuildFrames);
        Race myRace = nexus.getType().getRace();
        if (Races::Zerg != myRace) {
            nexus.train(myRace.getWorker());
        } else {
            // Zerg handling code goes here
        }
    }
}

bool NexusManager::addMiner(BWAPI::Unit *probe) {
    std::pair<UnitSet::iterator, bool> isIn = minGatherers.insert(probe);

    if (isIn.second) {
        Unit *min = minerals.front();
        minerals.pop_front();
        probe->rightClick(min);
        minerals.push_back(min);
        Broodwar->printf("added a miner.");
    }
    return isIn.second;
}

bool NexusManager::addGasser(BWAPI::Unit *probe) {
    gasGatherers.insert(probe);

    Broodwar->printf("added a gasser.");
	return false;
}

void NexusManager::onFrame(void) {
    //Broodwar->drawBoxMap(nexus.getPosition().x()-70, nexus.getPosition().y()+35, 
    //                      nexus.getPosition().x()+60, nexus.getPosition().y()+85, Colors::Red);
    //Broodwar->printf("Time till done building: %d", nexus.getRemainingTrainTime());
    Broodwar->drawTextScreen(40, 40, "building: %s\nlookingForProbe: %s\nremainingBuildFrames: %d",
        (building ? "yes" : "no"), (lookingForProbe ? "yes" : "no"), remainingBuildFrames);
    adjustRemainingFrames();
    buildProbe();
}


void NexusManager::findMinerals(void) {
    // 260 is the magic number at which we get the local min patch for starting positions on AIIDE maps
    UnitSet& aroundNexus = Broodwar->getUnitsInRadius(nexus.getPosition(), 260);
    
    minerals.assign(aroundNexus.begin(), aroundNexus.end());

    // Now we filter the list for only mineral items with isMineralField()
    for (UnitList::iterator unit = minerals.begin(); unit != minerals.end(); unit++) {
        if (!(*unit)->getType().isMineralField()) {
            minerals.erase(unit);
        }
    }

    minerals.sort(DistanceSorter(nexus));
    // We are now ready to start adding miners
}
