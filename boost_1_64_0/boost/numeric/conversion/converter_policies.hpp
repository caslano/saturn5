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
j2DJQplewfxkETDt2TdCXJpg1trm7UwQLJHMAQs9x0sS4lLIzNriE+JSyaJgoc+USSPrxeykiv0ebaljV3mZjf7qaRX0Ndlqi2GNa2eegrbUs6t6zH5wZLci9/p23HNSmT7Ddtc2nnlLVp9Z66OHjedWkK1nFrV+VUaM7bt2Fc+s4beJxnVTzYZO/rgC5mcDuyrB7MKxhsZ7qMhqM7vfIW446iOLgIVeI0slywoLPf8LcNPO8dLIKjPbvn34I2wrDVmcfo2am/59ODftvDiJLAez20VaLsY8IzsSZtigxs2LYM43taseLC5XpZOLEEfWn1m5FRWM78qb2VVNZjf8tzqiLWQNmF1aUb0y+pOsALMl9os4v1XvsbHVjk0TyKowqzVpKXJPJmvDbENM/skYB7KGzFL/9RZAXyfa1Z/Mmn1y0Ivcm7P+1L4r93HTvtNPJavArN47fxj7hxYsTrtPwE0WDQt9D6qHzM5swJaJXZE7Ge/PArbGTdFOLS5q/uRuaCdZfph2/bqlXX3OrHPZkegXP9lci2H3wlNewVrbVW6+bbo+749xIIuAab99bEPrIEzbp5LFwrR9qmAewZLJHLDQ9dortMVPZpZDqhCXJrTF2tbcEgRLFCyJzKwtKYL5hDJTBUsTzNoudA7e+qHObOSnWWq7n7MgPzI+Rrk9G43ja7KSzKZNCxuDHMgyWgw7vGUathXVwVg/K2nXe6zctLXVxU1bkxPICjMLL1W3O+Ygj9OvPXHT7zET2pIitMVLFsMsb7R7GeYuWTQs9LvIAFl+ZivbD7qMfukYate69THODTW78vIj41iD7D1ml2cUfxf1kQ1nVj9/EZSZ3MmuxjBbdv7OVIxDZ2EcmOl95iZ7CxZ6PJ9INoTZtFf2SmgnmZu3pUvqY9T3Ph1LMYsr8O9WjDtZJEz7DkwwL1ksTDueJ0sKWkX67Dtn9z7k0MWu1jJ7+XC2cd7osatpzCp5au1HfmSxzM7dj2mAbaUrzSVY6HdELrKssNBr6QlkT5m1/rHiQ/RLN7v6kNnD/SeLYQ0hO2ExbG/ta4VQZk+76sbiUoeONd7lKljCB0IcWQSrb+iUHx4g997B/VjQztxeuxVlklVntvarHi6MLVltWOh3UgGy2cw69p18GePex67qMsvhOJaGtvSlc21mZbPkMe4vIMP46WsymQMWuo+z9qM5CNN+z0VmVmYiWYmgVaDPfXdGZ8e6pNmRy2NzoJ2avf+qzCm0pb9d3QxaefqcX7XpHrRlQKg1qdzyY7RlIK27zIr8lHQS40BWlNngie8fwnZE1jE47uXo343XLU9FXJId9zaVpc9NJUo0RRxZcWZV52z7O2hUAR2DMfv90oWvkQPZB8yKTPktBnOQLB4W+q6GAFlNZsVujh6LMofYVVVmHdtX34AcyMza4hMsQFaaWe8uXYpge/8wNPfFtZOMa9tkRZl9+uC+8Z0+WW9mJc8PKI8chprn7iFrysx9N8VYB8l4vyz8/n3jXVrDQvsl0+uByMFD9i6zr3bWmYMyyfLCtHfBCOYabm6JgiUL5hMsIJh1hLm5yXhfV6r40rgvSDCvUGaqYGqkuSUI5hEsRTC/YGmCuUaZ554oWLJgPsECo4TxGy2M32hh/ATzCpYqmBpjbgmCecicMO0dOYJ5BfMLFhBMjTU3l2BuwTxkZrmnCOYna8Jse9UN9dCWj8wt+SOhzwTzCxYQTI0T+kwwt2AewZLHCduRYAHBrB+bm/tjoZ2CJQtl+gQLCGZNFtopWJJgXrIlQStDn/0GHY1H3Hi7ssG0dwpy098pSBYB094pSBYN094pSJYXFvqOMesEygGmvb+KLBamXdMhKxq0BPo=
*/