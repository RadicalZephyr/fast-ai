#include "StandardPlay.h"
#include "BaseManager\BaseManager.h"

void CheeseStrategies::StandardPlay::onFrame() {
    upgradeChecker();
    techBuildingChecker();
}

void CheeseStrategies::StandardPlay::init() {
   BaseManagerSet::iterator first = g_baseManagers.begin();
    m_base = *first;

    startBuilding();
}

void CheeseStrategies::StandardPlay::startBuilding() {
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Assimilator);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Cybernetics_Core);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Pylon);
   m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Gateway);
}

bool CheeseStrategies::StandardPlay::startUpgrade(BWAPI::UpgradeType upgrade) {
   UnitType upBuildingType = upgrade.whatUpgrades();

    if (Broodwar->self()->completedUnitCount(upBuildingType) == 0) {
        return false;
    }

    UnitSet myUnits = BWAPI::Broodwar->self()->getUnits();
    UnitSet::iterator it;

    BWAPI::Unit* upBuilding;

    for (it=myUnits.begin(); it!=myUnits.end(); it++) {
        if ((*it)->getType() == upBuildingType) {
            upBuilding = (*it);
        }
    }

    return upBuilding->upgrade(upgrade);
}

bool CheeseStrategies::StandardPlay::startTech(BWAPI::TechType tech) {
   UnitType techBuildingType = tech.whatResearches();

    if (Broodwar->self()->completedUnitCount(techBuildingType) == 0) {
        return false;
    }

    UnitSet myUnits = BWAPI::Broodwar->self()->getUnits();
    UnitSet::iterator it;

    BWAPI::Unit* techBuilding;

    for (it=myUnits.begin(); it!=myUnits.end(); it++) {
        if ((*it)->getType() == techBuildingType) {
            techBuilding = (*it);
        }
    }

    return techBuilding->research(tech);
}

void CheeseStrategies::StandardPlay::upgradeChecker() {
    if (!dragoonRange) {
        dragoonRange = startUpgrade(BWAPI::UpgradeTypes::Singularity_Charge);
    }
    if (!zealotLegs) {
        zealotLegs = startUpgrade(BWAPI::UpgradeTypes::Leg_Enhancements);
    }
    if (!psiStorm) {
        psiStorm = startTech(BWAPI::TechTypes::Psionic_Storm);
    }
    if (!kAmulet && psiStorm) {
        kAmulet = startUpgrade(BWAPI::UpgradeTypes::Khaydarin_Amulet);
    }
}

void CheeseStrategies::StandardPlay::techBuildingChecker() {
    if (!citadel &&
      Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core) >= 1 &&
      Broodwar->self()->supplyUsed() >= 140) {

        citadel = m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Citadel_of_Adun);
    }
    if (!robotics &&
      Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core) >= 1 &&
      Broodwar->self()->supplyUsed() >= 100) {

        robotics = m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Robotics_Facility);
    }
    if (!observatory &&
      Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Robotics_Facility) >= 1) {

        observatory = m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Observatory);
    }
    if (!templarArchives &&
      Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) >= 1) {

        templarArchives = m_base->constructBuilding(BWAPI::UnitTypes::Protoss_Templar_Archives);
    }
}