//  Boost integer_fwd.hpp header file  ---------------------------------------//

//  (C) Copyright Dave Abrahams and Daryle Walker 2001. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

#ifndef BOOST_INTEGER_FWD_HPP
#define BOOST_INTEGER_FWD_HPP

#include <climits>  // for UCHAR_MAX, etc.
#include <cstddef>  // for std::size_t

#include <boost/config.hpp>  // for BOOST_NO_INTRINSIC_WCHAR_T
#include <boost/limits.hpp>  // for std::numeric_limits
#include <boost/cstdint.hpp>  // For intmax_t


namespace boost
{

#ifdef BOOST_NO_INTEGRAL_INT64_T
     typedef unsigned long static_log2_argument_type;
     typedef          int  static_log2_result_type;
     typedef long          static_min_max_signed_type;
     typedef unsigned long static_min_max_unsigned_type;
#else
     typedef boost::uintmax_t static_min_max_unsigned_type;
     typedef boost::intmax_t  static_min_max_signed_type;
     typedef boost::uintmax_t static_log2_argument_type;
     typedef int              static_log2_result_type;
#endif

//  From <boost/cstdint.hpp>  ------------------------------------------------//

// Only has typedefs or using statements, with #conditionals


//  From <boost/integer_traits.hpp>  -----------------------------------------//

template < class T >
    class integer_traits;

template <  >
    class integer_traits< bool >;

template <  >
    class integer_traits< char >;

template <  >
    class integer_traits< signed char >;

template <  >
    class integer_traits< unsigned char >;

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template <  >
    class integer_traits< wchar_t >;
#endif

template <  >
    class integer_traits< short >;

template <  >
    class integer_traits< unsigned short >;

template <  >
    class integer_traits< int >;

template <  >
    class integer_traits< unsigned int >;

template <  >
    class integer_traits< long >;

template <  >
    class integer_traits< unsigned long >;

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_LONG_LONG)
template <  >
class integer_traits<  ::boost::long_long_type>;

template <  >
class integer_traits<  ::boost::ulong_long_type >;
#elif !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_MS_INT64)
template <  >
class integer_traits<__int64>;

template <  >
class integer_traits<unsigned __int64>;
#endif


//  From <boost/integer.hpp>  ------------------------------------------------//

template < typename LeastInt >
    struct int_fast_t;

template< int Bits >
    struct int_t;

template< int Bits >
    struct uint_t;

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && defined(BOOST_HAS_LONG_LONG)
    template< boost::long_long_type MaxValue >   // maximum value to require support
#else
  template< long MaxValue >   // maximum value to require support
#endif
    struct int_max_value_t;

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && defined(BOOST_HAS_LONG_LONG)
  template< boost::long_long_type MinValue >   // minimum value to require support
#else
  template< long MinValue >   // minimum value to require support
#endif
    struct int_min_value_t;

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && defined(BOOST_HAS_LONG_LONG)
  template< boost::ulong_long_type MaxValue >   // maximum value to require support
#else
  template< unsigned long MaxValue >   // maximum value to require support
#endif
    struct uint_value_t;


//  From <boost/integer/integer_mask.hpp>  -----------------------------------//

template < std::size_t Bit >
    struct high_bit_mask_t;

template < std::size_t Bits >
    struct low_bits_mask_t;

template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned char>::digits >;

//  From <boost/integer/static_log2.hpp>  ------------------------------------//

template <static_log2_argument_type Value >
    struct static_log2;

template <> struct static_log2<0u>;


//  From <boost/integer/static_min_max.hpp>  ---------------------------------//

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
    struct static_signed_min;

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
    struct static_signed_max;

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
    struct static_unsigned_min;

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
    struct static_unsigned_max;


namespace integer
{
//  From <boost/integer/common_factor_ct.hpp>

#ifdef BOOST_NO_INTEGRAL_INT64_T
     typedef unsigned long static_gcd_type;
#else
     typedef boost::uintmax_t static_gcd_type;
#endif

template < static_gcd_type Value1, static_gcd_type Value2 >
    struct static_gcd;
template < static_gcd_type Value1, static_gcd_type Value2 >
    struct static_lcm;


//  From <boost/integer/common_factor_rt.hpp>

template < typename IntegerType >
    class gcd_evaluator;
template < typename IntegerType >
    class lcm_evaluator;

} // namespace integer

}  // namespace boost


#endif  // BOOST_INTEGER_FWD_HPP

/* integer_fwd.hpp
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
*/