#include "Cheese/Helpers.h"
#include "Base.h"
#include "Util/PersistentPrinter.h"

namespace CheeseStrategies
{
	class CannonAwesome : public BaseCheeseStrategy
	{
	public: // Intilization section

		CannonAwesome() : BaseCheeseStrategy(), 
						  m_buildOrder(0), 
						  m_tileList(),
						  m_printer(400, 20)
		{
			whichProbe = 0;
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
	private:
		BWAPI::Unit* m_probe;
		int m_buildOrder;
		std::list<BWAPI::TilePosition> m_tileList;
		PersistentPrinter m_printer;
	};
}
