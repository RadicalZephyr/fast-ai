#include "Cheese/Helpers.h"
#include "Base.h"

namespace CheeseStrategies
{
	class CannonAwesome : public BaseCheeseStrategy
	{
	public: // Intilization section

		CannonAwesome() : BaseCheeseStrategy()
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


	protected:
		virtual void start();

		virtual void onFrame();
	private:
		BWAPI::Unit* m_probe;
	};
}
