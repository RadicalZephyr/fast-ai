#include "DistanceSorter.h"

DistanceSorter::DistanceSorter(const Unit &closeTo): refPoint(closeTo) {}

bool DistanceSorter::operator()(const Unit *rhs, const Unit *lhs) {
    return refPoint.getPosition().getApproxDistance(rhs->getPosition()) <
            refPoint.getPosition().getApproxDistance(lhs->getPosition());
}