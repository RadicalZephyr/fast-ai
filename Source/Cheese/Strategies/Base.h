#pragma once

#include "Cheese/Helpers.h"

namespace CheeseStrategies
{
	class BaseCheeseStrategy : public ICheeseStrategy
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
		virtual void newProbe(BWAPI::Unit* probe) 
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
