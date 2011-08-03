// rounding-algorithms.hpp
//
// General Rounding Algorithms
// Copyright (c) 2008 Michael Thomas Greer
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//----------------------------------------------------------------------------
// Reference
// <http://www.pldesignline.com/howto/showArticle.jhtml;?articleID=175801189>
//
//----------------------------------------------------------------------------
// In this library, symmetric functions are indicated by a zero at the end
// of the function name.
//
// If you want a different default epsilon make sure to change
//
//   #define ROUNDING_EPSILON 0.001
//
// to whatever you want it to be. (I wanted to make it so that you could 
// define a different default epsilon each time you #included the file, but
// I haven't figured out how to get around the template restrictions yet.)
//

#ifndef ROUNDING_ALGORITHMS_HPP
#define ROUNDING_ALGORITHMS_HPP

#ifndef ROUNDING_EPSILON
#define ROUNDING_EPSILON 0.0000001
#endif

#include <cmath>
#include <cstdlib>
#include <ciso646>

namespace rounding
  {

  //--------------------------------------------------------------------------
  // round down
  // Bias: -Infinity
  using std::floor;

  //--------------------------------------------------------------------------
  // round up
  // Bias: +Infinity
  using std::ceil;

  //--------------------------------------------------------------------------
  // symmetric round down
  // Bias: towards zero
  template <typename FloatType>
  FloatType floor0( const FloatType& value )
    {
    FloatType result = std::floor( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
    }

  //--------------------------------------------------------------------------
  // A common alias for floor0()
  // (notwithstanding hardware quirks)
  template <typename FloatType>
  inline
  FloatType trunc( const FloatType& value )
    {
    return floor0( value );
    }

  //--------------------------------------------------------------------------
  // symmetric round up
  // Bias: away from zero
  template <typename FloatType>
  FloatType ceil0( const FloatType& value )
    {
    FloatType result = std::ceil( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
    }

  //--------------------------------------------------------------------------
  // Common rounding: round half up
  // Bias: +Infinity
  template <typename FloatType>
  FloatType roundhalfup( const FloatType& value )
    {
    return std::floor( value +0.5 );
    }

  //--------------------------------------------------------------------------
  // Round half down
  // Bias: -Infinity
  template <typename FloatType>
  FloatType roundhalfdown( const FloatType& value )
    {
    return std::ceil( value -0.5 );
    }

  //--------------------------------------------------------------------------
  // symmetric round half down
  // Bias: towards zero
  template <typename FloatType>
  FloatType roundhalfdown0( const FloatType& value )
    {
    FloatType result = roundhalfdown( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
    }

  //--------------------------------------------------------------------------
  // symmetric round half up
  // Bias: away from zero
  template <typename FloatType>
  FloatType roundhalfup0( const FloatType& value )
    {
    FloatType result = roundhalfup( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
    }

  //--------------------------------------------------------------------------
  // round half even (banker's rounding)
  // Bias: none
  template <typename FloatType>
  FloatType roundhalfeven(
    const FloatType& value,
    const FloatType& epsilon = ROUNDING_EPSILON
    ) {
    if (value < 0.0) return -roundhalfeven <FloatType> ( -value, epsilon );

    FloatType ipart;
    std::modf( value, &ipart );

    // If 'value' is exctly halfway between two integers
    if ((value -(ipart +0.5)) < epsilon)
      {
      // If 'ipart' is even then return 'ipart'
      if (std::fmod( ipart, 2.0 ) < epsilon)
        return ipart;

      // Else return the nearest even integer
      return ceil0( ipart +0.5 );
      }

    // Otherwise use the usual round to closest
    // (Either symmetric half-up or half-down will do0
    return roundhalfup0( value );
    }

  //--------------------------------------------------------------------------
  // round alternate
  // Bias: none for sequential calls
  bool _is_up = false;
  template <typename FloatType>
  FloatType roundalternate( const FloatType& value, int& is_up = _is_up )
    {
    if ((is_up != is_up))
      return roundhalfup( value );
    return roundhalfdown( value );
    }

  //--------------------------------------------------------------------------
  // symmetric round alternate
  // Bias: none for sequential calls
  template <typename FloatType>
  FloatType roundalternate0( const FloatType& value, int& is_up = _is_up )
    {
    if ((is_up != is_up))
      return roundhalfup0( value );
    return roundhalfdown0( value );
    }

  //--------------------------------------------------------------------------
  // round random
  // Bias: generator's bias
  template <typename FloatType, typename RandValue, typename RandomGenerator>
  FloatType roundrandom(
    const FloatType& value,
    const RandValue& mid,
    RandomGenerator& g
    ) {
    if (g() < mid)
      return roundhalfup0( value );
    return roundhalfdown0( value );
    }

  //--------------------------------------------------------------------------
  // default round random
  // Bias: rand()
  template <typename FloatType>
  FloatType roundrandom( const FloatType& value )
    {
    return roundrandom <FloatType, int, int(*)()> ( value, RAND_MAX /2, &rand );
    }
  }

#endif 