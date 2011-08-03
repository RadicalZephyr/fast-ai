#pragma once

#include "Important/Common.h"
#include "Cheese/Helpers.h"
#include "Util/Debug.h"

namespace CheeseStrategies
{
	class BaseCheeseStrategy : public ICheeseStrategy, private Debug
	{
	public: // Intilization section

		BaseCheeseStrategy()
		{
			whichProbe = 0;
			m_firstRun = true;
			m_isRunning = false;
		}

		// For long asynchronous intilization actions
		virtual void init() {}

	public: //Usage Section

		// Will be called every time a new probe arrives at the cheese site
		virtual void newProbe(BWAPI::Unit* ) 
		{
			
		}

		bool m_firstRun;
		bool m_isRunning;
		virtual void setRunning(bool isRunning) {
			if (isRunning) {
				m_isRunning = true;

				Signal::onFrame().connect(boost::bind(&BaseCheeseStrategy::nvOnFrame, this));

				if (m_firstRun) {
					m_firstRun = false;
					start();
				}
			}
			else {
				m_isRunning = false;
			}
		}

		virtual void printDebug(void) {BWAPI::Broodwar->drawTextScreen(40, 40, "firstRun: %s\nisRunning: %s",
																(m_firstRun ? "true" : "false"),
																(m_isRunning ? "true" : "false"));}
		virtual bool isMyUnitSelected(void) {return true;}

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
