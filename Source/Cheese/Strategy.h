#include "Important\Common.h"

struct CheeseStrategyProbeOptions
{
	int whichProbe;
};

class ICheeseStrategy
{
public:
	virtual CheeseStrategyProbeOptions &const getProbeOptions(void) = 0;
};