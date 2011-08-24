#pragma once
#include "Important/Common.h"
#include "UnitTrainingManager/IUnitTrainingManagerBehaviour.h"
#include "Util/Debug.h"
#include "Util/Timed.h"

using BWAPI::Unit;

class NexusBehaviour : public IUnitTrainingManagerBehaviour, private Debug {
public:
	NexusBehaviour(Unit *nexus);

	virtual void postBuild(BWAPI::Unit *unit);
	virtual BWAPI::UnitType shouldBuild(BWAPI::UnitType type);

	void setShouldBuild(bool newFlag) {m_shouldBuild = newFlag;}

	void onFrame(void);
	void onFriendlyUnitDestroy(BWAPI::Unit *unit) {removeProbeFromGatherers(unit);}
	void onNeutralUnitDestroy(BWAPI::Unit *unit) {m_gas.remove(unit);
												m_minerals.remove(unit);}

	void addProbe(Unit *unit);
	Unit *removeProbe(void);
	BWAPI::TilePosition startGas(void);
	
	Unit *getNexus(void) {return m_nexus;}

private:
    virtual void printDebug(void);
    virtual bool isMyUnitSelected(void);

	void findMinerals(void);

    bool addMiner(Unit *probe);
    bool addGasser(Unit *probe);

	bool addProbeToGatherers(BWAPI::Unit *probe, UnitSet &gathererSet, UnitList &resourceList, bool shiftClick = false);
	bool removeProbeFromGatherers(BWAPI::Unit *probe);

	const static int s_mineralDistance;

	Unit *m_nexus;

	UnitList m_gas;
	UnitList m_minerals;

	UnitSet m_minGatherers;
	UnitSet m_gasGatherers;

	bool m_shouldBuild;

	// Not implemented to disallow assignment
	// and default construction
	NexusBehaviour(void);
	NexusBehaviour(NexusBehaviour &rhs);
	NexusBehaviour &operator=(NexusBehaviour &rhs);
};


// Current problems: queues like a bitch
// also, possibly related to queueing is it doesn't always successfully execute the postBuild
