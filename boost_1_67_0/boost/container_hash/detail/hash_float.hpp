
// Copyright 2005-2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HEADER)
#define BOOST_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HEADER

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/container_hash/detail/float_functions.hpp>
#include <boost/container_hash/detail/limits.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <cstring>

#if defined(BOOST_MSVC)
#pragma warning(push)
#if BOOST_MSVC >= 1400
#pragma warning(disable:6294) // Ill-defined for-loop: initial condition does
                              // not satisfy test. Loop body not executed
#endif
#endif

// Can we use fpclassify?

// STLport
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define BOOST_HASH_USE_FPCLASSIFY 0

// GNU libstdc++ 3
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#  if (defined(__USE_ISOC99) || defined(_GLIBCXX_USE_C99_MATH)) && \
      !(defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#    define BOOST_HASH_USE_FPCLASSIFY 1
#  else
#    define BOOST_HASH_USE_FPCLASSIFY 0
#  endif

// Everything else
#else
#  define BOOST_HASH_USE_FPCLASSIFY 0
#endif

namespace boost
{
    namespace hash_detail
    {
        inline void hash_float_combine(std::size_t& seed, std::size_t value)
        {
            seed ^= value + (seed<<6) + (seed>>2);
        }

        ////////////////////////////////////////////////////////////////////////
        // Binary hash function
        //
        // Only used for floats with known iec559 floats, and certain values in
        // numeric_limits

        inline std::size_t hash_binary(char* ptr, std::size_t length)
        {
            std::size_t seed = 0;

            if (length >= sizeof(std::size_t)) {
                std::memcpy(&seed, ptr, sizeof(std::size_t));
                length -= sizeof(std::size_t);
                ptr += sizeof(std::size_t);

                while(length >= sizeof(std::size_t)) {
                    std::size_t buffer = 0;
                    std::memcpy(&buffer, ptr, sizeof(std::size_t));
                    hash_float_combine(seed, buffer);
                    length -= sizeof(std::size_t);
                    ptr += sizeof(std::size_t);
                }
            }

            if (length > 0) {
                std::size_t buffer = 0;
                std::memcpy(&buffer, ptr, length);
                hash_float_combine(seed, buffer);
            }

            return seed;
        }

        template <typename Float, unsigned digits, unsigned max_exponent>
        struct enable_binary_hash
        {
            BOOST_STATIC_CONSTANT(bool, value =
                std::numeric_limits<Float>::is_iec559 &&
                std::numeric_limits<Float>::digits == digits &&
                std::numeric_limits<Float>::radix == 2 &&
                std::numeric_limits<Float>::max_exponent == max_exponent);
        };

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 24, 128>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 4);
        }


        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 53, 1024>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 8);
        }

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 64, 16384>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 10);
        }

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 113, 16384>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 16);
        }

        ////////////////////////////////////////////////////////////////////////
        // Portable hash function
        //
        // Used as a fallback when the binary hash function isn't supported.

        template <class T>
        inline std::size_t float_hash_impl2(T v)
        {
            boost::hash_detail::call_frexp<T> frexp;
            boost::hash_detail::call_ldexp<T> ldexp;

            int exp = 0;

            v = frexp(v, &exp);

            // A postive value is easier to hash, so combine the
            // sign with the exponent and use the absolute value.
            if(v < 0) {
                v = -v;
                exp += limits<T>::max_exponent -
                    limits<T>::min_exponent;
            }

            v = ldexp(v, limits<std::size_t>::digits);
            std::size_t seed = static_cast<std::size_t>(v);
            v -= static_cast<T>(seed);

            // ceiling(digits(T) * log2(radix(T))/ digits(size_t)) - 1;
            std::size_t const length
                = (limits<T>::digits *
                        boost::static_log2<limits<T>::radix>::value
                        + limits<std::size_t>::digits - 1)
                / limits<std::size_t>::digits;

            for(std::size_t i = 0; i != length; ++i)
            {
                v = ldexp(v, limits<std::size_t>::digits);
                std::size_t part = static_cast<std::size_t>(v);
                v -= static_cast<T>(part);
                hash_float_combine(seed, part);
            }

            hash_float_combine(seed, static_cast<std::size_t>(exp));

            return seed;
        }

#if !defined(BOOST_HASH_DETAIL_TEST_WITHOUT_GENERIC)
        template <class T>
        inline std::size_t float_hash_impl(T v, ...)
        {
            typedef BOOST_DEDUCED_TYPENAME select_hash_type<T>::type type;
            return float_hash_impl2(static_cast<type>(v));
        }
#endif
    }
}

#if BOOST_HASH_USE_FPCLASSIFY

#include <boost/config/no_tr1/cmath.hpp>

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        inline std::size_t float_hash_value(T v)
        {
#if defined(fpclassify)
            switch (fpclassify(v))
#elif BOOST_HASH_CONFORMANT_FLOATS
            switch (std::fpclassify(v))
#else
            using namespace std;
            switch (fpclassify(v))
#endif
            {
            case FP_ZERO:
                return 0;
            case FP_INFINITE:
                return (std::size_t)(v > 0 ? -1 : -2);
            case FP_NAN:
                return (std::size_t)(-3);
            case FP_NORMAL:
            case FP_SUBNORMAL:
                return float_hash_impl(v, 0);
            default:
                BOOST_ASSERT(0);
                return 0;
            }
        }
    }
}

#else // !BOOST_HASH_USE_FPCLASSIFY

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        inline bool is_zero(T v)
        {
#if !defined(__GNUC__) && !defined(__clang__)
            return v == 0;
#else
            // GCC's '-Wfloat-equal' will complain about comparing
            // v to 0, but because it disables warnings for system
            // headers it won't complain if you use std::equal_to to
            // compare with 0. Resulting in this silliness:
            return std::equal_to<T>()(v, 0);
#endif
        }

        template <class T>
        inline std::size_t float_hash_value(T v)
        {
            return boost::hash_detail::is_zero(v) ? 0 : float_hash_impl(v, 0);
        }
    }
}

#endif // BOOST_HASH_USE_FPCLASSIFY

#undef BOOST_HASH_USE_FPCLASSIFY

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif

/* hash_float.hpp
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
*/