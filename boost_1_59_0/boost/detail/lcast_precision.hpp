// Copyright Alexander Nasonov & Paul A. Bristow 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED
#define BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED

#include <climits>
#include <ios>
#include <limits>

#include <boost/config.hpp>
#include <boost/integer_traits.hpp>

#ifndef BOOST_NO_IS_ABSTRACT
// Fix for SF:1358600 - lexical_cast & pure virtual functions & VC 8 STL
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_abstract.hpp>
#endif

#if defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS) || \
  (defined(BOOST_MSVC) && (BOOST_MSVC<1310))

#define BOOST_LCAST_NO_COMPILE_TIME_PRECISION
#endif

#ifdef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
#include <boost/assert.hpp>
#else
#include <boost/static_assert.hpp>
#endif

namespace boost { namespace detail {

class lcast_abstract_stub {};

#ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
// Calculate an argument to pass to std::ios_base::precision from
// lexical_cast. See alternative implementation for broken standard
// libraries in lcast_get_precision below. Keep them in sync, please.
template<class T>
struct lcast_precision
{
#ifdef BOOST_NO_IS_ABSTRACT
    typedef std::numeric_limits<T> limits; // No fix for SF:1358600.
#else
    typedef BOOST_DEDUCED_TYPENAME boost::conditional<
        boost::is_abstract<T>::value
      , std::numeric_limits<lcast_abstract_stub>
      , std::numeric_limits<T>
      >::type limits;
#endif

    BOOST_STATIC_CONSTANT(bool, use_default_precision =
            !limits::is_specialized || limits::is_exact
        );

    BOOST_STATIC_CONSTANT(bool, is_specialized_bin =
            !use_default_precision &&
            limits::radix == 2 && limits::digits > 0
        );

    BOOST_STATIC_CONSTANT(bool, is_specialized_dec =
            !use_default_precision &&
            limits::radix == 10 && limits::digits10 > 0
        );

    BOOST_STATIC_CONSTANT(std::streamsize, streamsize_max =
            boost::integer_traits<std::streamsize>::const_max
        );

    BOOST_STATIC_CONSTANT(unsigned int, precision_dec = limits::digits10 + 1U);

    BOOST_STATIC_ASSERT(!is_specialized_dec ||
            precision_dec <= streamsize_max + 0UL
        );

    BOOST_STATIC_CONSTANT(unsigned long, precision_bin =
            2UL + limits::digits * 30103UL / 100000UL
        );

    BOOST_STATIC_ASSERT(!is_specialized_bin ||
            (limits::digits + 0UL < ULONG_MAX / 30103UL &&
            precision_bin > limits::digits10 + 0UL &&
            precision_bin <= streamsize_max + 0UL)
        );

    BOOST_STATIC_CONSTANT(std::streamsize, value =
            is_specialized_bin ? precision_bin
                               : is_specialized_dec ? precision_dec : 6
        );
};
#endif

template<class T>
inline std::streamsize lcast_get_precision(T* = 0)
{
#ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
    return lcast_precision<T>::value;
#else // Follow lcast_precision algorithm at run-time:

#ifdef BOOST_NO_IS_ABSTRACT
    typedef std::numeric_limits<T> limits; // No fix for SF:1358600.
#else
    typedef BOOST_DEDUCED_TYPENAME boost::conditional<
        boost::is_abstract<T>::value
      , std::numeric_limits<lcast_abstract_stub>
      , std::numeric_limits<T>
      >::type limits;
#endif

    bool const use_default_precision =
        !limits::is_specialized || limits::is_exact;

    if(!use_default_precision)
    { // Includes all built-in floating-point types, float, double ...
      // and UDT types for which digits (significand bits) is defined (not zero)

        bool const is_specialized_bin =
            limits::radix == 2 && limits::digits > 0;
        bool const is_specialized_dec =
            limits::radix == 10 && limits::digits10 > 0;
        std::streamsize const streamsize_max =
            (boost::integer_traits<std::streamsize>::max)();
        (void)streamsize_max;

        if(is_specialized_bin)
        { // Floating-point types with
          // limits::digits defined by the specialization.

            unsigned long const digits = limits::digits;
            unsigned long const precision = 2UL + digits * 30103UL / 100000UL;
            // unsigned long is selected because it is at least 32-bits
            // and thus ULONG_MAX / 30103UL is big enough for all types.
            BOOST_ASSERT(
                    digits < ULONG_MAX / 30103UL &&
                    precision > limits::digits10 + 0UL &&
                    precision <= streamsize_max + 0UL
                );
            return precision;
        }
        else if(is_specialized_dec)
        {   // Decimal Floating-point type, most likely a User Defined Type
            // rather than a real floating-point hardware type.
            unsigned int const precision = limits::digits10 + 1U;
            BOOST_ASSERT(precision <= streamsize_max + 0UL);
            return precision;
        }
    }

    // Integral type (for which precision has no effect)
    // or type T for which limits is NOT specialized,
    // so assume stream precision remains the default 6 decimal digits.
    // Warning: if your User-defined Floating-point type T is NOT specialized,
    // then you may lose accuracy by only using 6 decimal digits.
    // To avoid this, you need to specialize T with either
    // radix == 2 and digits == the number of significand bits,
    // OR
    // radix = 10 and digits10 == the number of decimal digits.

    return 6;
#endif
}

template<class T>
inline void lcast_set_precision(std::ios_base& stream, T*)
{
    stream.precision(lcast_get_precision<T>());
}

template<class Source, class Target>
inline void lcast_set_precision(std::ios_base& stream, Source*, Target*)
{
    std::streamsize const s = lcast_get_precision(static_cast<Source*>(0));
    std::streamsize const t = lcast_get_precision(static_cast<Target*>(0));
    stream.precision(s > t ? s : t);
}

}}

#endif //  BOOST_DETAIL_LCAST_PRECISION_HPP_INCLUDED


/* lcast_precision.hpp
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
*/