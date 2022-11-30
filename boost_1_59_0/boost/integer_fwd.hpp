//  Boost integer_fwd.hpp header file  ---------------------------------------//

//  (C) Copyright Dave Abrahams and Daryle Walker 2001. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

//  See https://www.boost.org/libs/integer for documentation.

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