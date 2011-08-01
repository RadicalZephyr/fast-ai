#include "Cheese/Helpers.h"

namespace CheeseStrategies
{
	class BaseCheeseStrategy abstract
	{
	public: // Intilization section

		BaseCheeseStrategy()
		{
			whichProbe = 0;
		}

		// For long asynchronous intilization actions
		virtual void init() {}

	public: //Usage Section

		// Will be called every time a new probe arrives at the cheese site
		virtual void newProbe(BWAPI::Unit* probe) 
		{
			
		}

		bool m_firstRun = true;
		bool m_isRunning = false;
		virtual void setRunning(bool isRunning) {
			if (isRunning) {
				m_isRunning = true;

				Signal::onFrame().connect(boost::bind(&BaseCheeseStrategy::nvOnFrame, this))

				if (m_firstRun) {
					m_firstRun = false;
					start();
				}
			}
			else {
				m_isRunning = false;
			}
		}

	protected:
		virtual void start()
		{

		}

		virtual void onFrame()
		{

		}
	private:
		void nvOnFrame(){ this->onFrame(); }
	};
}
