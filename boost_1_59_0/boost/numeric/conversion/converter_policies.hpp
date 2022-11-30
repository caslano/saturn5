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

#include <functional>
#include <typeinfo> // for std::bad_cast

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp> // for std::floor and std::ceil
#include <boost/throw_exception.hpp>

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

    const char * what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
      {  return "bad numeric conversion: overflow"; }
};

class negative_overflow : public bad_numeric_cast
{
  public:

    const char * what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
      {  return "bad numeric conversion: negative overflow"; }
};
class positive_overflow : public bad_numeric_cast
{
  public:

    const char * what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
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
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
*/