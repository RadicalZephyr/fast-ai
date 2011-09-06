#pragma once

#include "important/common.h"

class ObserverFollow
{
public:
	ObserverFollow(BWAPI::Unit *unit);

	~ObserverFollow(void) {
		m_connection.disconnect();
	}

	void onFrame(void);
	void followNewUnit(void);

private:
	BWAPI::Unit *cloakedEnemy(void);

	BWAPI::Unit *m_unit;
	BWAPI::Unit *m_following;
    boost::signals::connection m_connection;
};

