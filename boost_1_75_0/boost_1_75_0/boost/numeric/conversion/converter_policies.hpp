//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
//
#ifndef BOOST_NUMERIC_CONVERSION_CONVERTER_POLICIES_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERTER_POLICIES_FLC_12NOV2002_HPP

#include <typeinfo> // for std::bad_cast

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp> // for std::floor and std::ceil
#include <boost/throw_exception.hpp>

#include <functional>

#include "boost/type_traits/is_arithmetic.hpp"

#include "boost/mpl/if.hpp"
#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric
{

template<class S>
struct Trunc
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    return s < static_cast<S>(0) ? ceil(s) : floor(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_zero> round_style ;
} ;



template<class S>
struct Floor
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
#endif

    return floor(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_neg_infinity> round_style ;
} ;

template<class S>
struct Ceil
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::ceil ;
#endif

    return ceil(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_infinity> round_style ;
} ;

template<class S>
struct RoundEven
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
    // Algorithm contributed by Guillaume Melquiond

#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    // only works inside the range not at the boundaries
    S prev = floor(s);
    S next = ceil(s);

    S rt = (s - prev) - (next - s); // remainder type

    S const zero(0.0);
    S const two(2.0);

    if ( rt < zero )
      return prev;
    else if ( rt > zero )
      return next;
    else
    {
      bool is_prev_even = two * floor(prev / two) == prev ;
      return ( is_prev_even ? prev : next ) ;
    }
  }

  typedef mpl::integral_c< std::float_round_style, std::round_to_nearest> round_style ;
} ;


enum range_check_result
{
  cInRange     = 0 ,
  cNegOverflow = 1 ,
  cPosOverflow = 2
} ;

class bad_numeric_cast : public std::bad_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      {  return "bad numeric conversion: overflow"; }
};

class negative_overflow : public bad_numeric_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      {  return "bad numeric conversion: negative overflow"; }
};
class positive_overflow : public bad_numeric_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      { return "bad numeric conversion: positive overflow"; }
};

struct def_overflow_handler
{
  void operator() ( range_check_result r ) // throw(negative_overflow,positive_overflow)
  {
#ifndef BOOST_NO_EXCEPTIONS
    if ( r == cNegOverflow )
      throw negative_overflow() ;
    else if ( r == cPosOverflow )
           throw positive_overflow() ;
#else
    if ( r == cNegOverflow )
      ::boost::throw_exception(negative_overflow()) ;
    else if ( r == cPosOverflow )
           ::boost::throw_exception(positive_overflow()) ;
#endif
  }
} ;

struct silent_overflow_handler
{
  void operator() ( range_check_result ) {} // throw()
} ;

template<class Traits>
struct raw_converter
{
  typedef typename Traits::result_type   result_type   ;
  typedef typename Traits::argument_type argument_type ;

  static result_type low_level_convert ( argument_type s ) { return static_cast<result_type>(s) ; }
} ;

struct UseInternalRangeChecker {} ;

} } // namespace boost::numeric

#endif

/* converter_policies.hpp
CLvWyQE2Vv8l/B2xMk/TtMAr9GM9fkKzyvBJvaFvX8swaIBmcjRxA0inPxzlXFrxCQLo5tpIrP5NbPC6azNmcGN+zHoGt+qoJ9VRT5R8u3oBeevmW6IlDf/gSLra2PykofbwooDAMb+AsgVrYuXD1GmwWu+7gFLVa9a7B6Ie8qECwVccaNRC3Xn54zVwoADMWKHyNgyxogfoAzFlKMVY7XXKjfhYEgT2eGqBIhk063X02Bdvq/ddFPoQjq4CzdpjMH6kuEAI54xIr+iYY1S9rDePoWX2Y0x9eVJNg+fMyM6QrlG9uqKjkT0693Dc62RuVtdMZcemLrKVn1Pc206gbPnrdWGapfuqG1hRCnL7egqB51HygDtJ+S0XxBTrruGUNHwUPGtgz0CESSm9Cp/9iz3rHWW5hr20OonVyFqVxP1nI3Kum/iNAdAJyld/pQ/8PowAV4Q9jdbFV2yCqTkF+s4e1qRMIIaXOXY0qHb+nZwkfe960hOn8jACKvdCeQ+3aZr1zv7kc8bgMoimjCJ0DrMekUytFZTCrzF4SJA30XnCFeR5Gsw+Rk6aktlYUJSVtBE9YeCd49w61RId0MYRuuppkgeByExf4pG/luSPBK4fK/fIbyVS6yqLgTGURfVIMKB5k6R47aqV0ipVHSIv626kgL9uEJrPanmDQRk6ewM4nYG4hrhtJNxGyoGewjDxWXZ6908wJnRdppL3
*/