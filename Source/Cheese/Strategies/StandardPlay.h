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
	}

	virtual void onFrame();
	virtual void init();
	
	void startBuilding();

private:
	BWAPI::Unit* m_probe;
	BaseManagerPtr m_base;

	boost::signals::connection m_frameConnection;
	
};

}