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