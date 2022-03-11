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

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/predef/other/endian.h>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>

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

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7f800000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0x00000000);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x007fffff);

    typedef uint32_t bits;
    static void get_bits(float x, uint32_t& a) { std::memcpy(&a, &x, 4); }
    static void set_bits(float& x, uint32_t a) { std::memcpy(&x, &a, 4); }
};

// ieee_tag version, double (64 bits) ----------------------------------------------

#if defined(BOOST_NO_INT64_T) || defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) \
   || defined(__BORLANDC__) || defined(__CODEGEAR__)

template<> struct fp_traits_non_native<double, double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7ff00000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x000fffff);

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

#if BOOST_ENDIAN_BIG_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 0);
#elif BOOST_ENDIAN_LITTLE_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 4);
#else
    BOOST_STATIC_ASSERT(false);
#endif
};

//..............................................................................

#else

template<> struct fp_traits_non_native<double, double_precision>
{
    typedef ieee_copy_all_bits_tag method;

    static const uint64_t sign     = ((uint64_t)0x80000000u) << 32;
    static const uint64_t exponent = ((uint64_t)0x7ff00000) << 32;
    static const uint64_t flag     = 0;
    static const uint64_t significand
        = (((uint64_t)0x000fffff) << 32) + ((uint64_t)0xffffffffu);

    typedef uint64_t bits;
    static void get_bits(double x, uint64_t& a) { std::memcpy(&a, &x, 8); }
    static void set_bits(double& x, uint64_t a) { std::memcpy(&x, &a, 8); }
};

#endif

#endif  // #ifndef BOOST_FPCLASSIFY_VAX_FORMAT

// long double (64 bits) -------------------------------------------------------

#if defined(BOOST_NO_INT64_T) || defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)\
   || defined(__BORLANDC__) || defined(__CODEGEAR__)

template<> struct fp_traits_non_native<long double, double_precision>
{
    typedef ieee_copy_leading_bits_tag method;

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7ff00000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x000fffff);

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

#if BOOST_ENDIAN_BIG_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 0);
#elif BOOST_ENDIAN_LITTLE_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 4);
#else
    BOOST_STATIC_ASSERT(false);
#endif
};

//..............................................................................

#else

template<> struct fp_traits_non_native<long double, double_precision>
{
    typedef ieee_copy_all_bits_tag method;

    static const uint64_t sign     = (uint64_t)0x80000000u << 32;
    static const uint64_t exponent = (uint64_t)0x7ff00000 << 32;
    static const uint64_t flag     = 0;
    static const uint64_t significand
        = ((uint64_t)0x000fffff << 32) + (uint64_t)0xffffffffu;

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

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7fff0000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0x00008000);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x00007fff);

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

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7ff00000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0x00000000);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x000fffff);

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

#if BOOST_ENDIAN_BIG_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 0);
#elif BOOST_ENDIAN_LITTLE_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 12);
#else
    BOOST_STATIC_ASSERT(false);
#endif
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

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7fff0000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0x00008000);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x00007fff);

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

    BOOST_STATIC_CONSTANT(uint32_t, sign        = 0x80000000u);
    BOOST_STATIC_CONSTANT(uint32_t, exponent    = 0x7fff0000);
    BOOST_STATIC_CONSTANT(uint32_t, flag        = 0x00000000);
    BOOST_STATIC_CONSTANT(uint32_t, significand = 0x0000ffff);

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

#if BOOST_ENDIAN_BIG_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 0);
#elif BOOST_ENDIAN_LITTLE_BYTE
    BOOST_STATIC_CONSTANT(int, offset_ = 12);
#else
    BOOST_STATIC_ASSERT(false);
#endif
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
    typedef BOOST_DEDUCED_TYPENAME size_to_precision<sizeof(T), ::boost::is_floating_point<T>::value>::type precision;
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
   && !defined(BOOST_INTEL)\
   && !defined(sun)\
   && !defined(__VXWORKS__)
#  define BOOST_MATH_USE_STD_FPCLASSIFY
#endif

template<class T> struct fp_traits
{
    typedef BOOST_DEDUCED_TYPENAME size_to_precision<sizeof(T), ::boost::is_floating_point<T>::value>::type precision;
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