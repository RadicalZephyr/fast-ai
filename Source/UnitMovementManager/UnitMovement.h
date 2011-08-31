#pragma once

#include <BWAPI.h>
#include <boost/numeric/ublas/vector.hpp>
#include "Important/Signals.h"

typedef boost::numeric::ublas::vector<double> MovementVector;

using BWAPI::Unit;

// Briefly, the idea behind this class is that we will keep track of a unit vector (i.e. a heading) for the unit
//  onFrame we will give the opportunity for all of our subscribers to calculate adjustments to our vector
//  These adjustments will then be added together by the signal combiner (might need to write our own)
//  and then normalized, and then an order given to the unit to move to that location.

// Obviously, doing this every frame is silly at best, and wasteful of processing time/orders
//  thus, a delay of some kind would probably be good.  Maybe a simple g_frame mod random number between 15 and 30?

// TODO: Figure out how to call the damn signal!  Probably the issue is in the combiner
class UnitMovement {
public:
    typedef boost::signal<MovementVector (Unit *, MovementVector), std::plus<MovementVector> > signal_t;
    typedef boost::signals::connection connection_t;

    explicit UnitMovement(Unit &unit) : m_unit(unit) {
   Signal::onFrame().connect(boost::bind(&UnitMovement::onFrame, this));
    }

    ~UnitMovement(void) {
   Signal::onFrame().disconnect(boost::bind(&UnitMovement::onFrame, this));
    }

    connection_t connect(signal_t::slot_function_type subscriber) {
        return m_sig.connect(subscriber);
    }

    void onFrame(void);
private:
    const Unit &m_unit;
    signal_t m_sig;
    MovementVector m_vector;
};
