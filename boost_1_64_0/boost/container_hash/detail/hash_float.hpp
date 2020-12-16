
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
kJuFmQ4z253vd1oYhtoc866w4Snv3RaiNz6x0gEPxV4awu0HFWijAarapuvh5P7YgumtRGbd4NYbNL2VnchEA3JV/U9LMWrWIPRqfM1gR23WRdlLXxMFaACULpOLoZxUd7c56XF8qX0Ux+IvKhHU0bIv1DtGq5l7vRHQGeu83/57l9Jk49+yNDZDXd2eCEo5zIo8EoqtKqzVBhlNcqk1Dwwj5XbZiwy/zA/HVmvz9p3T32wPpAJU5HEGqHzmSn13yOIj/V6IEpVcdV4doJYTW2r65phQ2ceV57Dwrf6Cdn0TalL+/PH7H78/L98vysfNe12N6NAw9oih85O/XXiujtW+iMvP105+8cab7w3/9+zdt18L65jXulJaky9TCpnBw1L1y09eb4vVcy9KTbz33Pjn+fj9m1y1XC/I9efw56XJ7xNoWre//Prcc5y/mLyUnjHvhGsSGXPszdqw73HDe93nfJi54x3n3ursXPDwX28T2tnyyS9kjLvbvar2bnerDnZyTEYaNde4LFR2N/O53vH+x+PdoZTvIsW07P8mamMylPmPVS5tqq4OYdt4M3b3Ze2pRINlTG/2Zqn/Lp7Oeyyk9mIsU57QUJ0XbyTUBuG16pLXrBH8714CDQVTOpaS5RMaFeG/SMchaf9V9a3gMMuzj0nmHMfMOVriT+LYc8iL2gsNYk7rs/vdrPi/a35mm0m8sDmH0/IRNCH++ygp6TZFBT/wleYKGluX1cm5Gl/3zdO64mdCvPsM+n93qlZG0Wm2Ch6r5jdDi3KWquYMfdBCK/s+a5Aw9RdwrJsZ+rhT5WKoQRs41/CF1xln9dgRg46LvqW1/TrZHYGQ4RdIMnqis3K5vznsWxX8Bxs/2mZxrrUtMdUOxsZINhcTJrUWOjMhn9txp9tJ/5NX4c69NoLMCMDa5/fyw3T7ef4IADcPl62+KNEA3skPDEGoCxym1DOd7DAmvcErFBWCf55DMLvutOjq99ty376Frg7mOHyb41hOmNIxo0b8Z6Fex0oy02sf04TmeivknPbN8UqJ+Ui9qNvgk5UWYZjRKPhO/oNvatAJ7tXTubf5fCwB7I7vv7ljpp0/837Ned/ps/yzzwhAQ7mZD0Hg9JNZ1sxx4k9HKCCt5efGWvhPoR3YQBJ0pAokFsZl9xSGXm13Dp3N5gUN4YOS4NFPLsuiCFl8X5bweDsvnAsfMgYL4XNdeHhspuIdXedzu8VcMhbw6WY9X1JP227fNs3NsemSC5qm6OK4ZKNqUcHm/kMIvBxa0hnDxS/8p6MbYhlBRlecEfFxEouSqIY5oU1nB1Dlg8FS8XPZEL0zIx3/H7GYyYjWMXg2JBgx5j+GD8dXg3IOKG90KRGOiWdLC47hl7kymHFjCh6YxgfoZCPdgXvvq6Hc31xiTHNBt+uX2fTPRCltBebke7EVkk/cYkhqs2fWvSF951vMWOKyNEf0oOZYyc+dhBWSzjXoMU+aa5dPrQitceN9PTmzD6IyjVmJclV10+zgaq4q8tt76rNHk8Hw9uHtOdEeV/hxZzi5XrbuJ2L6jNDpLVXYRGfEERJT4rsMGXrjm48cdtbetlhtBRslmGYQoEpYPpNjLVhl+yk0hP3ljaNWovx3TIDoSl5rDDO2EMwzbwpcqz9p398ogGnvLWv58VKh4kdcblru31pImyhFfC6vrHjZvfrqy3nfd9Xq2Gv70MOFSor5cupOr9x8PRdWDY/Tuk1KbhGGq+uuSv9/kz4cSaJmAsHEAWn21wrM+/ywkXuOY57GTDjl1T5fmTKqANl332Qff/jFFx99+PHn2adfff/Zt19/lX3/1s3chr/R1XtlnXLzscutbo+w7ndTmX4=
*/