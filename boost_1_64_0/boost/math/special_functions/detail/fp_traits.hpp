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
tTq0PaPdGvaX1dLIYMwc0Lks3lbKjmU4YmCGQYYiR4zYYQGGIok9nlZ36ld0TaunnYz2o2SYLLqx2GJW56jAjbJl0mDeRvpKo1MwSZc+x83HVGtJubqd1s6mgUP+30A0GhHTBthmE2PhR4mGQ2zr55y71WOH4XGOx8zcx2Hih9FMBN3z1NHrf/3rC9Oo1dfSMMJG8zROvI6sHXo6JRz22XhamjBXnoSrKdpOjdqCye8D/fttUQeHLf17Zv6hPsRKy5NR/KlobWMaa0E3ld/bG9PV25TzRqsjZdfVb3cb1qVNcPVUXJc24WZak/KGvVeOnpc1KROOlpczicvNlXYblLFV53eKS4Syu39Ya7k9TAmIvhDlIz2STAVELvZAH1bE0OzeLrWhUhcfCq4R13dqh29X1m8DTt1W9PT5EqeclV2N+z18O+PpupxVPE23IYP7QvPKf0PStQNGl6tV5/fp6duoOZAYGg8voPUc7dZ30N/tORrZn6RJe/hw0R623Wg341arGen3f156uUy/38rcwrG5Y9kN9aeWZ0/wHb1iI4wKuQbFG1zpZUUczbYSJ2H+0CVT7vh8ZTmdjHHWkfueRqmc+nFC7LH83uUTcwtzS7Mns4e/J8/a1cU+CDFqPa8X0imIzt0zlnHfTnuF1fVeuYHROVX1eU7L8LtmHWqcF5z3gKZeWcCeWWt26+o97pdZjqJexnyZ1fU8eaVsdX5/D/urAm4kEm73HaNxkEW4xS58m8MtnzqysjTHSSZpGmK8t+GjtwcYLoCXn9TDH2T14u73mj2K8ekP5Td1UiXalfbkR47OeQl94OmUN9Quor0Zero++z/1Y2g4OYC7aEo/cXS9yRhtlmJ4krQq9sRPofFRLtF6WuPTIqTxvBQ0PiUi2gw0c15gP9fmj83Npm2yLJWJrfd30fPOTAi4Ef8LDLXNQkh6/k504/7qv6G1tPs6vTQTpxs0E9i0/xVNLx86a0Wr0SU1Qz4IA1vh+AUyZmHl1tNUSuX3Vfmdgqbbpb+Wst8rs7UalYHk6HarsVF360D86xDj1oF+2J20yMGdv7nM8bWdRvOc61fv1yHG9Wsv6I57h0f5ny6z2F5a293iiKm9nau/DnPkId5WD7vl7ouNLucw2jdxx/NLfNLrR5478Em1b8/OGbpLJL3X49j88op+yWRN5hueVcSlfoIr7RVx5C9x8j7xfFaGTi4SRC4cm7Rt+7fNyuW9jt1G2bo3mfw2aRpgH5dvJpqz7tLD7yt0E0PCT8gtiI0vujQNO5efaMdYu210Smyf201+kzDsiI1+e9GcMJTuIL8Hw1AW3YahMsfa0Wmp89Fx+W0SiB1pB6FxGwltoDT2aEf65ay/yfs1urtseWVpljJrmd91VXvJ33EAVz26EOk3B98VZrm+LEg7+rYwp+vLuMAtKk1oyy9+kYzJ7l677/zCraejeekXlYarX9X+qqtovbsT0wJyS+nRVX19M9b9T1/pHMFY3PY0vvkJ5wu1vpVfl7GePrug28KreQwtdPN2fJSzq3sMj1gkjFpP70FSNvbI1/L4o2+/hqfn8Uc/pnRuWmLZJ/H5Q5k2t7J8dLYyl18atDx371N0ypVNI+zjOZBNyzPYmQNZCoROv3tewGGXK/ekHj/z+6j0AUEm9RPMIMiQX8TIvpinlnxmvpp237XslDn2LjwtzPE+AMw1Wj/nOdk2pP4+PeAWlQG+1RXzcietW7rvLgV0Tsp1sU1/fMgwbFyvSxqEwpMgPJLmzwhxtEKu/BsEGP/9x8qZvH1YXJmnYjDHdVCtzXc9XbXPsfctxxfj1s9l7SZtAc3bn7WaWlP9vNbkwJXoe19wdDl1KmNSq+M=
*/