#include "BaseManager.h"
#include "Util/BuildingRelativeBuildingPlacer.h"

using namespace BWAPI;

bool BaseManager::constructBuilding(BWAPI::UnitType type) {
	if (m_lastBuilding = 0) {
		// Create a first building in the area
		m_probe = m_controllee->removeProbe();
		BuildingRelativeBuildingPlacer placer(m_controllee->getNexus());
		TilePosition tile = placer.Place(type, BuildingRelativeBuildingPlacer::Left, 2, 0).makeValid();

		if (Broodwar->canBuildHere(m_probe, tile, type, true)) {
			m_probe->build(tile, type);
		}

	} else {
		m_probe;
	}

}

void BaseManager::onFrame(void) {
	if (m_probe && !m_probe->isConstructing()) {
		m_controllee->addProbe(m_probe);
		m_probe = 0;
	}
}
