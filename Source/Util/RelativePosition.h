#pragma once

#include <BWAPI.h>

using BWAPI::Position;

class RelativePosition
{
public:

    Position relativeTo(Position origin, Position relCoord);

    Position mirrorX(Position origin, Position point);

    Position mirrorY(Position origin, Position point);

    Position mirrorOrigin(Position origin, Position point);

    Position unitVectorRelativeTo(Position origin, Position point);

private:
    enum Quadrant {
        // Vertical is the 1 bit
        // Horizontal is the 2 bit
        LowerLeft = 0,
        UpperLeft = 1,
        LowerRight = 2,
        UpperRight = 3
    };

    Position mirrorPosition(Position origin, Position point, Quadrant direction);
    Quadrant identifyQuadrant(Position origin, Position point);

};

Position operator*(const Position &lhs, const Position &rhs);
Position operator*(const Position &lhs, int rhs);
Position operator*(int lhs, const Position &rhs);