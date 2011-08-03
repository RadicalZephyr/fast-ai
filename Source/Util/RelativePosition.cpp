#include "RelativePosition.h"
#include "Rounding.h"

using rounding::roundhalfeven;

// Convenience interface methods to the real workhorse method mirrorPosition
Position RelativePosition::mirrorX(Position origin, Position point) {
	return mirrorPosition(origin, point, LowerRight);
}

Position RelativePosition::mirrorY(Position origin, Position point) {
	return mirrorPosition(origin, point, UpperLeft);
}

Position RelativePosition::mirrorOrigin(Position origin, Position point) {
	return mirrorPosition(origin, point, UpperRight);
}

RelativePosition::Quadrant RelativePosition::identifyQuadrant(Position origin, Position point) {
	int quad = 0;

	// If origin x is less than point x set the 1 bit
	quad |= ((origin.x() >= point.x()) ? 0 : 1);
	// if origin y is greater than point y set the 2 bit
	quad |= ((origin.y() >= point.y()) ? 2 : 0);
	return static_cast<Quadrant>(quad);

	// The reason for the mismatch is that we are defining a relative coordinate system
	// that has origin in bottom left, whereas starcraft's origin is top left
}


Position RelativePosition::mirrorPosition(Position origin, Position point, RelativePosition::Quadrant direction) {
	int x = origin.x() - point.x();
	int y = origin.y() - point.y();

	// multiplying x by one and then adding them back to origin will yield point
	// so LowerLeft as Quadrant means no mirror, so it should cause them to be mult by 1

	return Position(origin.x() + (x * (direction & 1 ? -1 : 1)), 
					origin.y() + (y * (direction & 2 ? 1 : -1)));
}

Position RelativePosition::unitVectorRelativeTo(Position origin, Position point) {
	double length = origin.getDistance(point);

	return Position(static_cast<int>(roundhalfeven(origin.x() - point.x()/length)), 
					static_cast<int>(roundhalfeven(origin.y() - point.y()/length)));
}

Position operator*(const Position &lhs, const Position &rhs) {
	return Position(lhs.x() * rhs.x(), lhs.y() * rhs.y());
}

Position operator*(const Position &lhs, int rhs) {
	return Position(lhs.x() * rhs, lhs.y() * rhs);
}

Position operator*(int lhs, const Position &rhs) {
	return operator*(rhs, lhs);
}
