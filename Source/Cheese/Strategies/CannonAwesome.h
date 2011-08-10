#include "Cheese/Helpers.h"
#include "Base.h"
#include "Util/PersistentPrinter.h"
#include "Util/BuildOrder.h"

namespace CheeseStrategies
{
	class CannonAwesome : public BaseCheeseStrategy
	{
	public: // Intilization section

		CannonAwesome() : BaseCheeseStrategy(), 
						  m_buildOrder(0),
						  m_printer(400, 20)
		{
			whichProbe = 0;
			if (BWAPI::Broodwar->getStartLocations().size() == 4)
				buildProbesTo = 7;
			else
				buildProbesTo = 6;
		}

		// For long asynchronous intilization actions
		virtual void init() {}

	public: //Usage Section

		// Will be called every time a new probe arrives at the cheese site
		virtual void newProbe(BWAPI::Unit* probe) 
		{
			m_probe = probe;
		}

		virtual void printDebug(void);
		virtual bool isMyUnitSelected(void) {return (m_probe ? m_probe->isSelected() : false);}
	protected:
		virtual void start();

		virtual void onFrame();

		void onUnitDiscover(BWAPI::Unit *unit);

	private:
		BWAPI::Unit* m_probe;
		BuildOrder* m_buildOrder;
		PersistentPrinter m_printer;

		void onBuildEnd( BWAPI::Unit* probe );
		void attemptEarlyRecover(BuildOrderElement* orderElement, BWAPI::Unit* builderProbe);
	};
}
