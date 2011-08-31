#pragma once
#include "Important/Common.h"

using BWAPI::Unit;

class DistanceSorter {
public:
    explicit DistanceSorter(Unit const * const closeTo);
    bool operator()(const Unit *rhs, const Unit *lhs);
private:
    // Not implemented to make illegal (cause link errors)
    DistanceSorter(void);
    DistanceSorter& operator=(const DistanceSorter&);

    Unit const * const refPoint;

};