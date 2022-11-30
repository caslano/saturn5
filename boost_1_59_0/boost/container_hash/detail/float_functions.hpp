
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_FUNCTIONAL_HASH_DETAIL_FLOAT_FUNCTIONS_HPP)
#define BOOST_FUNCTIONAL_HASH_DETAIL_FLOAT_FUNCTIONS_HPP

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>

// Set BOOST_HASH_CONFORMANT_FLOATS to 1 for libraries known to have
// sufficiently good floating point support to not require any
// workarounds.
//
// When set to 0, the library tries to automatically
// use the best available implementation. This normally works well, but
// breaks when ambiguities are created by odd namespacing of the functions.
//
// Note that if this is set to 0, the library should still take full
// advantage of the platform's floating point support.

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif defined(__LIBCOMO__)
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif defined(_LIBCPP_VERSION)
// libc++
#   define BOOST_HASH_CONFORMANT_FLOATS 1
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#   if defined(__GNUC__) && __GNUC__ >= 4
#       define BOOST_HASH_CONFORMANT_FLOATS 1
#   else
#       define BOOST_HASH_CONFORMANT_FLOATS 0
#   endif
#elif defined(__STL_CONFIG_H)
// generic SGI STL
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif defined(__MSL_CPP__)
// MSL standard lib:
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif defined(__IBMCPP__)
// VACPP std lib (probably conformant for much earlier version).
#   if __IBMCPP__ >= 1210
#       define BOOST_HASH_CONFORMANT_FLOATS 1
#   else
#       define BOOST_HASH_CONFORMANT_FLOATS 0
#   endif
#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (this has to appear after any possible replacement libraries):
#   if _CPPLIB_VER >= 405
#       define BOOST_HASH_CONFORMANT_FLOATS 1
#   else
#       define BOOST_HASH_CONFORMANT_FLOATS 0
#   endif
#else
#   define BOOST_HASH_CONFORMANT_FLOATS 0
#endif

#if BOOST_HASH_CONFORMANT_FLOATS

// The standard library is known to be compliant, so don't use the
// configuration mechanism.

namespace boost {
    namespace hash_detail {
        template <typename Float>
        struct call_ldexp {
            typedef Float float_type;
            inline Float operator()(Float x, int y) const {
                return std::ldexp(x, y);
            }
        };

        template <typename Float>
        struct call_frexp {
            typedef Float float_type;
            inline Float operator()(Float x, int* y) const {
                return std::frexp(x, y);
            }
        };

        template <typename Float>
        struct select_hash_type
        {
            typedef Float type;
        };
    }
}

#else // BOOST_HASH_CONFORMANT_FLOATS == 0

// The C++ standard requires that the C float functions are overloarded
// for float, double and long double in the std namespace, but some of the older
// library implementations don't support this. On some that don't, the C99
// float functions (frexpf, frexpl, etc.) are available.
//
// The following tries to automatically detect which are available.

namespace boost {
    namespace hash_detail {

        // Returned by dummy versions of the float functions.
    
        struct not_found {
            // Implicitly convertible to float and long double in order to avoid
            // a compile error when the dummy float functions are used.

            inline operator float() const { return 0; }
            inline operator long double() const { return 0; }
        };
          
        // A type for detecting the return type of functions.

        template <typename T> struct is;
        template <> struct is<float> { char x[10]; };
        template <> struct is<double> { char x[20]; };
        template <> struct is<long double> { char x[30]; };
        template <> struct is<boost::hash_detail::not_found> { char x[40]; };
            
        // Used to convert the return type of a function to a type for sizeof.

        template <typename T> is<T> float_type(T);

        // call_ldexp
        //
        // This will get specialized for float and long double
        
        template <typename Float> struct call_ldexp
        {
            typedef double float_type;
            
            inline double operator()(double a, int b) const
            {
                using namespace std;
                return ldexp(a, b);
            }
        };

        // call_frexp
        //
        // This will get specialized for float and long double

        template <typename Float> struct call_frexp
        {
            typedef double float_type;
            
            inline double operator()(double a, int* b) const
            {
                using namespace std;
                return frexp(a, b);
            }
        };
    }
}
            
// A namespace for dummy functions to detect when the actual function we want
// isn't available. ldexpl, ldexpf etc. might be added tby the macros below.
//
// AFAICT these have to be outside of the boost namespace, as if they're in
// the boost namespace they'll always be preferable to any other function
// (since the arguments are built in types, ADL can't be used).

namespace boost_hash_detect_float_functions {
    template <class Float> boost::hash_detail::not_found ldexp(Float, int);
    template <class Float> boost::hash_detail::not_found frexp(Float, int*);    
}

// Macros for generating specializations of call_ldexp and call_frexp.
//
// check_cpp and check_c99 check if the C++ or C99 functions are available.
//
// Then the call_* functions select an appropriate implementation.
//
// I used c99_func in a few places just to get a unique name.
//
// Important: when using 'using namespace' at namespace level, include as
// little as possible in that namespace, as Visual C++ has an odd bug which
// can cause the namespace to be imported at the global level. This seems to
// happen mainly when there's a template in the same namesapce.

#define BOOST_HASH_CALL_FLOAT_FUNC(cpp_func, c99_func, type1, type2)    \
namespace boost_hash_detect_float_functions {                           \
    template <class Float>                                              \
    boost::hash_detail::not_found c99_func(Float, type2);               \
}                                                                       \
                                                                        \
namespace boost {                                                       \
    namespace hash_detail {                                             \
        namespace c99_func##_detect {                                   \
            using namespace std;                                        \
            using namespace boost_hash_detect_float_functions;          \
                                                                        \
            struct check {                                              \
                static type1 x;                                         \
                static type2 y;                                         \
                BOOST_STATIC_CONSTANT(bool, cpp =                       \
                    sizeof(float_type(cpp_func(x,y)))                   \
                        == sizeof(is<type1>));                          \
                BOOST_STATIC_CONSTANT(bool, c99 =                       \
                    sizeof(float_type(c99_func(x,y)))                   \
                        == sizeof(is<type1>));                          \
            };                                                          \
        }                                                               \
                                                                        \
        template <bool x>                                               \
        struct call_c99_##c99_func :                                    \
            boost::hash_detail::call_##cpp_func<double> {};             \
                                                                        \
        template <>                                                     \
        struct call_c99_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return c99_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <bool x>                                               \
        struct call_cpp_##c99_func :                                    \
            call_c99_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::c99     \
            > {};                                                       \
                                                                        \
        template <>                                                     \
        struct call_cpp_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   \
namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
#endif

#if defined(frexpf)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpf, float, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpf, float, int*)
#endif

#if defined(frexpl)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpl, long double, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpl, long double, int*)
#endif

#undef BOOST_HASH_CALL_FLOAT_MACRO
#undef BOOST_HASH_CALL_FLOAT_FUNC


namespace boost
{
    namespace hash_detail
    {
        template <typename Float1, typename Float2>
        struct select_hash_type_impl {
            typedef double type;
        };

        template <>
        struct select_hash_type_impl<float, float> {
            typedef float type;
        };

        template <>
        struct select_hash_type_impl<long double, long double> {
            typedef long double type;
        };


        // select_hash_type
        //
        // If there is support for a particular floating point type, use that
        // otherwise use double (there's always support for double).
             
        template <typename Float>
        struct select_hash_type : select_hash_type_impl<
                BOOST_DEDUCED_TYPENAME call_ldexp<Float>::float_type,
                BOOST_DEDUCED_TYPENAME call_frexp<Float>::float_type
            > {};            
    }
}

#endif // BOOST_HASH_CONFORMANT_FLOATS

#endif

/* float_functions.hpp
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
*/