#include "Cheese/Helpers.h"
#include "Base.h"

namespace CheeseStrategies {

class StandardPlay : public BaseCheeseStrategy
{
public:
	StandardPlay() : BaseCheeseStrategy() {
		m_frameConnection = Signal::onFrame().connect(boost::bind(&StandardPlay::onFrame, this));
		whichProbe = 6;
		buildProbesTo = -1;

		dragoonRange = false;
		zealotLegs = false;
		psiStorm = false;
		kAmulet = false;
	}

	virtual void onFrame();
	virtual void init();
	
	void startBuilding();
	bool startUpgrade(BWAPI::UpgradeType upgrade);
	bool startTech(BWAPI::TechType tech);
	void upgradeChecker();
	void techBuildingChecker();

private:
	boost::signals::connection m_frameConnection;

	BWAPI::Unit* m_probe;
	BaseManagerPtr m_base;

	bool dragoonRange;
	bool zealotLegs;
	bool psiStorm;
	bool kAmulet;

	bool citadel;
	bool templarArchives;
	bool robotics;
	bool roboticsBay;
	bool observatory;
	bool stargate;
};

}