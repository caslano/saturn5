
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