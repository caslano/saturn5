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
n/0l8fnVi82Iz3W/lsTnw4vjiM+8iuOYDIP+fatV9O+G5vSv1oSTFh8v/fvW0cfrV++3XC/vLT96+kGLj7leHl7+Y9ZL8fpjrpdRpS3XS+56fb1YH/zp1guk5pwS4kOjckOjMiHtW9Vcfgudg2KVDDTsny07+vg9eWccfIbOiPePrLlGLuNtp+rVy0rK72jo15OVqzyX9ZTg2iYtQQkNK+Y5lT3Cs8gBDL5YRi7lO48QBzKZ8WJz7VavB8+TNvAh5lZaIYJtnirPYp9loweKvuGh0XNLeZy+4ybE0N7eTfpxY9x9PG4smJ+Nf5+l0hnd7lNsqNqHqmEsZQR8UaipKLx+KHMqbRDmUkZmQ7ZLvBdY/d01KytJfZBFyOkKVsWWp5GpExMxiHa3ES1iljGm0fRDxXVqVtxCZqoyNRXXWS/uRsY8jRg2nOFNDR/NqLtlTYiyIsoFul/xWA0zOrlIErlRxpuOEG9n/IUuYbazMQcmNwfJ50SkjfSXz3Y+nyafu/K5i3zO5nOKW9mA5wGyWWrFUwLi7UQGucJ+Wz4oCmiOfK+TUiuiVfMGCc2Rb7qLBNiG1XOeRTNOFvLE0fTH2lA6b6MAgWj6nXjD9ROtBRRoVibLaqXEHO0A0dok/nTXs8MWWUzX4vsqvpZ7LaZu+J6H71X43oDv7fhOx/dufB/G12Qmk7rdv+8DozNt/wetzBwv/SzxT/pSgTOU9s/f1A2mvJ+WW3pX7Ly/QwAk4rNgmwpv3W4Rb13wRoTxg9aRBX7S7C9qxrOfKZNV7dW2+vZ5FYb0+lXAvWaeqko8wZkek98v7ls9CihE3IZl03CSWTMFV4QFpZmGkyJK0S3YkvOkqVTForxPedMiD/N148pukYfSQUyzRbshNZpQHtTF/OQV131n8orr97jialAPgjcjkgrDBkz/zyod7dvcY1RmTBkeZVS+MiQzuN3W1pmpDMkKObNiYlveX2ujOoasBxrQhHCe6jIGNxHslBu1MZ2NMc01+QPNxvRUfUzd4MUq1RR0aBrNM2n7W/JMtPHMZZ4MjmdT+riRbHnXnOvEoF6nDWqRHNRz+3NQl2JQO6lPPg5o4nhG/smxXGvAs/t1jX+3Klz0Cbh4al41N6YW4GrAf0z6z5necsT0LflxGhHz3muabhd2UmWXYCNR9h33d7Th8+tndHaBsPaCsKFWVMLLHRAoeLODLsGbXRma4QwXpYKwVYZ2DRV2VYZmgsJVhmaHCrPVqSvFzeFoX3johKWp4nA2eoL62XwReq4HfOok+MmKtMNRk1eSJWtZ6VyYUYhQYbF0muBxVWtUz5Rmrq54+fPm24J5pY7ZIJhwW9aemA+Ecbkl9dSAMF2xu6En2NZZutHflr5wnI6N/n2keyJ1Lfz2xMrbT3u1xfmAAvM+ZfgkLG12pJKawWo7UD8A3Y+FXc65AQ94Z6z3dEytDuoYeg0LEGxxK2uObqRtbWQbBohncghYFRWQ0E8iYG/2hQsnYFjFqKtPPoaWoFp1PVh28n4JmHFKjrxDWwWu7D+joSFg51Pk17i8JX+V/Q6JVbUfkEcjb4S9cVJebYbHEx6JqI/FMHDGMQw+ts/0phiKGQNhrnruzfpI9Gw+ElzB8aPgbsUo/PFRbRRqwzGjMLGvHIUqEAqwaDe3rQC9cQL00HBDAnrcj5AMPMp40fdY83d73Htu07th//8VTX+pcoKgsYse0GlsxZnRrFkNzkwr4NR/siZPgmf9zJXMuMAuMUCKJyuUcqT+KMDfzd+7HgWfa5j8zpeb+FdfEdwJEGWiZrPAIM8J4JqZjUusP/IxFp33gPFrY5dUVhibXZKO0nOCJRmmwKDySRo67ibR8Qs=
*/