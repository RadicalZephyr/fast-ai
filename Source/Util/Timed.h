#include "../Important/Common.h"

//Provides a way to see when timed points of time have passed
class Timed
{
public:
	Timed(int const& delta) : m_frameStart(g_frame), m_frameEnd(delta + m_frameStart) {}
	Timed(Timed const& copy) : m_frameStart(copy.m_frameStart), m_frameEnd(copy.m_frameEnd) {}

	inline void reset(int const& delta) {m_frameEnd = delta + (m_frameStart = g_frame);}

	inline bool isDone() const {return m_frameEnd >= g_frame;}
	inline operator bool() const {return isDone();}

	inline int doneOn() const {return m_frameEnd;}
	inline operator int() const {return doneOn();}

	inline int tillDone() const {return m_frameEnd - g_frame;}
	inline int amountDone() const {return g_frame - m_frameStart;}

	inline int delta() const {return m_frameEnd - m_frameStart;}

	inline float ratioDone() const {return ((float)amountDone()) / ((float)(m_frameEnd - m_frameStart));}
	inline float ratioUndone() const {return ((float)tillDone()) / ((float)(m_frameEnd - m_frameStart));}

	inline void addDelta(int const& delta) {m_frameEnd += delta;}
private:
	int m_frameStart;
	int m_frameEnd;
};