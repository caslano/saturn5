// fp_traits.hpp

#ifndef BOOST_MATH_FP_TRAITS_HPP
#define BOOST_MATH_FP_TRAITS_HPP

// Copyright (c) 2006 Johan Rade

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
To support old compilers, care has been taken to avoid partial template
specialization and meta function forwarding.
With these techniques, the code could be simplified.
*/

#if defined(__vms) && defined(__DECCXX) && !__IEEE_FLOAT
// The VAX floating point formats are used (for float and double)
#   define BOOST_FPCLASSIFY_VAX_FORMAT
#endif

#include <cstring>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_standalone.hpp>
#include <boost/math/tools/assert.hpp>

// Determine endianness
#ifndef BOOST_MATH_STANDALONE

#include <boost/predef/other/endian.h>
#define BOOST_MATH_ENDIAN_BIG_BYTE BOOST_ENDIAN_BIG_BYTE
#define BOOST_MATH_ENDIAN_LITTLE_BYTE BOOST_ENDIAN_LITTLE_BYTE

#elif (__cplusplus >= 202002L || _MSVC_LANG >= 202002L)

#if __has_include(<bit>)
#include <bit>
#define BOOST_MATH_ENDIAN_BIG_BYTE (std::endian::native == std::endian::big)
#define BOOST_MATH_ENDIAN_LITTLE_BYTE (std::endian::native == std::endian::little)
#else
#error Missing <bit> header. Please disable standalone mode, and file an issue at https://github.com/boostorg/math
#endif

#elif defined(_WIN32)

#define BOOST_MATH_ENDIAN_BIG_BYTE 0
#define BOOST_MATH_ENDIAN_LITTLE_BYTE 1

#elif defined(__BYTE_ORDER__)

#define BOOST_MATH_ENDIAN_BIG_BYTE (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BOOST_MATH_ENDIAN_LITTLE_BYTE (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#else
#error Could not determine endian type. Please disable standalone mode, and file an issue at https://github.com/boostorg/math
#endif // Determine endianness

static_assert((BOOST_MATH_ENDIAN_BIG_BYTE || BOOST_MATH_ENDIAN_LITTLE_BYTE)
    && !(BOOST_MATH_ENDIAN_BIG_BYTE && BOOST_MATH_ENDIAN_LITTLE_BYTE),
    "Inconsistent endianness detected. Please disable standalone mode, and file an issue at https://github.com/boostorg/math");

#ifdef BOOST_NO_STDC_NAMESPACE
  namespace std{ using ::memcpy; }
#endif

#ifndef FP_NORMAL

#define FP_ZERO        0
#define FP_NORMAL      1
#define FP_INFINITE    2
#define FP_NAN         3
#define FP_SUBNORMAL   4

#else

#define BOOST_HAS_FPCLASSIFY

#ifndef fpclassify
#  if (defined(__GLIBCPP__) || defined(__GLIBCXX__)) \
         && defined(_GLIBCXX_USE_C99_MATH) \
         && !(defined(_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC) \
         && (_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC != 0))
#     ifdef _STLP_VENDOR_CSTD
#        if _STLPORT_VERSION >= 0x520
#           define BOOST_FPCLASSIFY_PREFIX ::__std_alias::
#        else
#           define BOOST_FPCLASSIFY_PREFIX ::_STLP_VENDOR_CSTD::
#        endif
#     else
#        define BOOST_FPCLASSIFY_PREFIX ::std::
#     endif
#  else
#     undef BOOST_HAS_FPCLASSIFY
#     define BOOST_FPCLASSIFY_PREFIX
#  endif
#elif (defined(__HP_aCC) && !defined(__hppa))
// aCC 6 appears to do "#define fpclassify fpclassify" which messes us up a bit!
#  define BOOST_FPCLASSIFY_PREFIX ::
#else
#  define BOOST_FPCLASSIFY_PREFIX
#endif

#ifdef __MINGW32__
#  undef BOOST_HAS_FPCLASSIFY
#endif

#endif


//------------------------------------------------------------------------------

namespace boost {
namespace math {
namespace detail {

//------------------------------------------------------------------------------

/*
The following classes are used to tag the different methods that are used
for floating point classification
*/

struct native_tag {};
template <bool has_limits>
struct generic_tag {};
struct ieee_tag {};
struct ieee_copy_all_bits_tag : public ieee_tag {};
struct ieee_copy_leading_bits_tag : public ieee_tag {};

#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
//
// These helper functions are used only when numeric_limits<>
// members are not compile time constants:
//
inline bool is_generic_tag_false(const generic_tag<false>*)
{
   return true;
}
inline bool is_generic_tag_false(const void*)
{
   return false;
}
#endif

//------------------------------------------------------------------------------

/*
Most processors support three different floating point precisions:
single precision (32 bits), double precision (64 bits)
and extended double precision (80 - 128 bits, depending on the processor)

Note that the C++ type long double can be implemented
both as double precision and extended double precision.
*/

struct unknown_precision{};
struct single_precision {};
struct double_precision {};
struct extended_double_precision {};

// native_tag version --------------------------------------------------------------

template<class T> struct fp_traits_native
{
    typedef native_tag method;
};

// generic_tag version -------------------------------------------------------------

template<class T, class U> struct fp_traits_non_native
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   typedef generic_tag<std::numeric_limits<T>::is_specialized> method;
#else
   typedef generic_tag<false> method;
#endif
};

// ieee_tag versions ---------------------------------------------------------------

/*
These specializations of fp_traits_non_native contain information needed
to "parse" the binary representation of a floating point number.

Typedef members:

  bits -- the target type when copying the leading bytes of a floating
      point number. It is a typedef for uint32_t or uint64_t.

  method -- tells us whether all bytes are copied or not.
      It is a typedef for ieee_copy_all_bits_tag or ieee_copy_leading_bits_tag.

Static data members:

  sign, exponent, flag, significand -- bit masks that give the meaning of the
  bits in the leading bytes.

Static function members:

  get_bits(), set_bits() -- provide access to the leading bytes.

*/

// ieee_tag version, float (32 bits) -----------------------------------------------

#ifndef BOOST_FPCLASSIFY_VAX_FORMAT

template<> struct fp_traits_non_native<float, single_precision>
{
    typedef ieee_copy_all_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7f800000;
    static constexpr uint32_t flag        = 0x00000000;
    static constexpr uint32_t significand = 0x007fffff;

    typedef uint32_t bits;
    static void get_bits(float x, uint32_t& a) { std::memcpy(&a, &x, 4); }
    static void set_bits(float& x, uint32_t a) { std::memcpy(&x, &a, 4); }
};

// ieee_tag version, double (64 bits) ----------------------------------------------

#if defined(BOOST_NO_INT64_T) || defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) \
   || defined(BOOST_BORLANDC) || defined(__CODEGEAR__)

template<> struct fp_traits_non_native<double, double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7ff00000;
    static constexpr uint32_t flag        = 0;
    static constexpr uint32_t significand = 0x000fffff;

    typedef uint32_t bits;

    static void get_bits(double x, uint32_t& a)
    {
        std::memcpy(&a, reinterpret_cast<const unsigned char*>(&x) + offset_, 4);
    }

    static void set_bits(double& x, uint32_t a)
    {
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + offset_, &a, 4);
    }

private:
    static constexpr int offset_ = BOOST_MATH_ENDIAN_BIG_BYTE ? 0 : 4;
};

//..............................................................................

#else

template<> struct fp_traits_non_native<double, double_precision>
{
    typedef ieee_copy_all_bits_tag method;

    static constexpr uint64_t sign     = static_cast<uint64_t>(0x80000000u) << 32;
    static constexpr uint64_t exponent = static_cast<uint64_t>(0x7ff00000) << 32;
    static constexpr uint64_t flag     = 0;
    static constexpr uint64_t significand
        = (static_cast<uint64_t>(0x000fffff) << 32) + static_cast<uint64_t>(0xffffffffu);

    typedef uint64_t bits;
    static void get_bits(double x, uint64_t& a) { std::memcpy(&a, &x, 8); }
    static void set_bits(double& x, uint64_t a) { std::memcpy(&x, &a, 8); }
};

#endif

#endif  // #ifndef BOOST_FPCLASSIFY_VAX_FORMAT

// long double (64 bits) -------------------------------------------------------

#if defined(BOOST_NO_INT64_T) || defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)\
   || defined(BOOST_BORLANDC) || defined(__CODEGEAR__)

template<> struct fp_traits_non_native<long double, double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7ff00000;
    static constexpr uint32_t flag        = 0;
    static constexpr uint32_t significand = 0x000fffff;

    typedef uint32_t bits;

    static void get_bits(long double x, uint32_t& a)
    {
        std::memcpy(&a, reinterpret_cast<const unsigned char*>(&x) + offset_, 4);
    }

    static void set_bits(long double& x, uint32_t a)
    {
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + offset_, &a, 4);
    }

private:
    static constexpr int offset_ = BOOST_MATH_ENDIAN_BIG_BYTE ? 0 : 4;
};

//..............................................................................

#else

template<> struct fp_traits_non_native<long double, double_precision>
{
    typedef ieee_copy_all_bits_tag method;

    static const uint64_t sign     = static_cast<uint64_t>(0x80000000u) << 32;
    static const uint64_t exponent = static_cast<uint64_t>(0x7ff00000) << 32;
    static const uint64_t flag     = 0;
    static const uint64_t significand
        = (static_cast<uint64_t>(0x000fffff) << 32) + static_cast<uint64_t>(0xffffffffu);

    typedef uint64_t bits;
    static void get_bits(long double x, uint64_t& a) { std::memcpy(&a, &x, 8); }
    static void set_bits(long double& x, uint64_t a) { std::memcpy(&x, &a, 8); }
};

#endif


// long double (>64 bits), x86 and x64 -----------------------------------------

#if defined(__i386) || defined(__i386__) || defined(_M_IX86) \
    || defined(__amd64) || defined(__amd64__)  || defined(_M_AMD64) \
    || defined(__x86_64) || defined(__x86_64__) || defined(_M_X64)

// Intel extended double precision format (80 bits)

template<>
struct fp_traits_non_native<long double, extended_double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7fff0000;
    static constexpr uint32_t flag        = 0x00008000;
    static constexpr uint32_t significand = 0x00007fff;

    typedef uint32_t bits;

    static void get_bits(long double x, uint32_t& a)
    {
        std::memcpy(&a, reinterpret_cast<const unsigned char*>(&x) + 6, 4);
    }

    static void set_bits(long double& x, uint32_t a)
    {
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + 6, &a, 4);
    }
};


// long double (>64 bits), Itanium ---------------------------------------------

#elif defined(__ia64) || defined(__ia64__) || defined(_M_IA64)

// The floating point format is unknown at compile time
// No template specialization is provided.
// The generic_tag definition is used.

// The Itanium supports both
// the Intel extended double precision format (80 bits) and
// the IEEE extended double precision format with 15 exponent bits (128 bits).

#elif defined(__GNUC__) && (LDBL_MANT_DIG == 106)

//
// Define nothing here and fall though to generic_tag:
// We have GCC's "double double" in effect, and any attempt
// to handle it via bit-fiddling is pretty much doomed to fail...
//

// long double (>64 bits), PowerPC ---------------------------------------------

#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) \
    || defined(__ppc) || defined(__ppc__) || defined(__PPC__)

// PowerPC extended double precision format (128 bits)

template<>
struct fp_traits_non_native<long double, extended_double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7ff00000;
    static constexpr uint32_t flag        = 0x00000000;
    static constexpr uint32_t significand = 0x000fffff;

    typedef uint32_t bits;

    static void get_bits(long double x, uint32_t& a)
    {
        std::memcpy(&a, reinterpret_cast<const unsigned char*>(&x) + offset_, 4);
    }

    static void set_bits(long double& x, uint32_t a)
    {
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + offset_, &a, 4);
    }

private:
    static constexpr int offset_ = BOOST_MATH_ENDIAN_BIG_BYTE ? 0 : 12;
};


// long double (>64 bits), Motorola 68K ----------------------------------------

#elif defined(__m68k) || defined(__m68k__) \
    || defined(__mc68000) || defined(__mc68000__) \

// Motorola extended double precision format (96 bits)

// It is the same format as the Intel extended double precision format,
// except that 1) it is big-endian, 2) the 3rd and 4th byte are padding, and
// 3) the flag bit is not set for infinity

template<>
struct fp_traits_non_native<long double, extended_double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7fff0000;
    static constexpr uint32_t flag        = 0x00008000;
    static constexpr uint32_t significand = 0x00007fff;

    // copy 1st, 2nd, 5th and 6th byte. 3rd and 4th byte are padding.

    typedef uint32_t bits;

    static void get_bits(long double x, uint32_t& a)
    {
        std::memcpy(&a, &x, 2);
        std::memcpy(reinterpret_cast<unsigned char*>(&a) + 2,
               reinterpret_cast<const unsigned char*>(&x) + 4, 2);
    }

    static void set_bits(long double& x, uint32_t a)
    {
        std::memcpy(&x, &a, 2);
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + 4,
               reinterpret_cast<const unsigned char*>(&a) + 2, 2);
    }
};


// long double (>64 bits), All other processors --------------------------------

#else

// IEEE extended double precision format with 15 exponent bits (128 bits)

template<>
struct fp_traits_non_native<long double, extended_double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    static constexpr uint32_t sign        = 0x80000000u;
    static constexpr uint32_t exponent    = 0x7fff0000;
    static constexpr uint32_t flag        = 0x00000000;
    static constexpr uint32_t significand = 0x0000ffff;

    typedef uint32_t bits;

    static void get_bits(long double x, uint32_t& a)
    {
        std::memcpy(&a, reinterpret_cast<const unsigned char*>(&x) + offset_, 4);
    }

    static void set_bits(long double& x, uint32_t a)
    {
        std::memcpy(reinterpret_cast<unsigned char*>(&x) + offset_, &a, 4);
    }

private:
    static constexpr int offset_ = BOOST_MATH_ENDIAN_BIG_BYTE ? 0 : 12;
};

#endif

//------------------------------------------------------------------------------

// size_to_precision is a type switch for converting a C++ floating point type
// to the corresponding precision type.

template<int n, bool fp> struct size_to_precision
{
   typedef unknown_precision type;
};

template<> struct size_to_precision<4, true>
{
    typedef single_precision type;
};

template<> struct size_to_precision<8, true>
{
    typedef double_precision type;
};

template<> struct size_to_precision<10, true>
{
    typedef extended_double_precision type;
};

template<> struct size_to_precision<12, true>
{
    typedef extended_double_precision type;
};

template<> struct size_to_precision<16, true>
{
    typedef extended_double_precision type;
};

//------------------------------------------------------------------------------
//
// Figure out whether to use native classification functions based on
// whether T is a built in floating point type or not:
//
template <class T>
struct select_native
{
    typedef typename size_to_precision<sizeof(T), ::std::is_floating_point<T>::value>::type precision;
    typedef fp_traits_non_native<T, precision> type;
};
template<>
struct select_native<float>
{
    typedef fp_traits_native<float> type;
};
template<>
struct select_native<double>
{
    typedef fp_traits_native<double> type;
};
template<>
struct select_native<long double>
{
    typedef fp_traits_native<long double> type;
};

//------------------------------------------------------------------------------

// fp_traits is a type switch that selects the right fp_traits_non_native

#if (defined(BOOST_MATH_USE_C99) && !(defined(__GNUC__) && (__GNUC__ < 4))) \
   && !defined(__hpux) \
   && !defined(__DECCXX)\
   && !defined(__osf__) \
   && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)\
   && !defined(__FAST_MATH__)\
   && !defined(BOOST_MATH_DISABLE_STD_FPCLASSIFY)\
   && !defined(__INTEL_COMPILER)\
   && !defined(sun)\
   && !defined(__VXWORKS__)
#  define BOOST_MATH_USE_STD_FPCLASSIFY
#endif

template<class T> struct fp_traits
{
    typedef typename size_to_precision<sizeof(T), ::std::is_floating_point<T>::value>::type precision;
#if defined(BOOST_MATH_USE_STD_FPCLASSIFY) && !defined(BOOST_MATH_DISABLE_STD_FPCLASSIFY)
    typedef typename select_native<T>::type type;
#else
    typedef fp_traits_non_native<T, precision> type;
#endif
    typedef fp_traits_non_native<T, precision> sign_change_type;
};

//------------------------------------------------------------------------------

}   // namespace detail
}   // namespace math
}   // namespace boost

#endif

/* fp_traits.hpp
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
*/