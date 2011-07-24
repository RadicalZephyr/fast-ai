#pragma once
#include "CommonHeaders.h"

using BWAPI::Unit;

class DistanceSorter {
public:
    explicit DistanceSorter(const Unit &closeTo);
    bool operator()(const Unit *rhs, const Unit *lhs);
private:
    // Not implemented to make illegal (cause link errors)
    DistanceSorter(void);
    DistanceSorter& operator=(const DistanceSorter&);

    const Unit &refPoint;

};