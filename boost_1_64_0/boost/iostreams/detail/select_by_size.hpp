// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Intended as an alternative to type_traits::yes_type and type_traits::no_type.
// Provides an arbitrary number of types (case_<0>, case_<1>, ...) for
// determining the results of overload resultion using 'sizeof', plus a uniform
// means of using the result. yes_type and no_type are typedefs for case_<1>
// and case_<0>. A single case with negative argument, case_<-1>, is also 
// provided, for convenience.
//
// This header may be included any number of times, with
// BOOST_SELECT_BY_SIZE_MAX_CASE defined to be the largest N such that case_<N>
// is needed for a particular application. It defaults to 20.
//
// This header depends only on Boost.Config and Boost.Preprocessor. Dependence
// on Type Traits or MPL was intentionally avoided, to leave open the 
// possibility that select_by_size could be used by these libraries.
//
// Example usage:
//
//    #define BOOST_SELECT_BY_SIZE_MAX_CASE 7   // (Needed when default was 2)
//    #include <boost/utility/select_by_size.hpp>
//
//    using namespace boost::utility;
//
//    case_<0> helper(bool);
//    case_<1> helper(int);
//    case_<2> helper(unsigned);
//    case_<3> helper(long);
//    case_<4> helper(unsigned long);
//    case_<5> helper(float);
//    case_<6> helper(double);
//    case_<7> helper(const char*);
//
//    struct test {
//        static const int value =
//            select_by_size< sizeof(helper(9876UL)) >::value;
//        BOOST_STATIC_ASSERT(value == 4);
//    };
//
// For compilers with integral constant expression problems, e.g. Borland 5.x,
// one can also write
//
//    struct test {
//        BOOST_SELECT_BY_SIZE(int, value, helper(9876UL));
//    };
//
// to define a static integral constant 'value' equal to
//
//    select_by_size< sizeof(helper(9876UL)) >::value.
//

// Include guards surround all contents of this header except for explicit
// specializations of select_by_size for case_<N> with N > 2.

#ifndef BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED

// The lowest N for which select_by_size< sizeof(case_<N>) > has not been
// specialized.
#define SELECT_BY_SIZE_MAX_SPECIALIZED 20

#include <boost/config.hpp>    // BOOST_STATIC_CONSTANT.
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>

/* Alternative implementation using max_align. 

#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

namespace boost { namespace utility {

template<int N>
struct case_ { char c[(N + 1) * alignment_of<detail::max_align>::value]; };

template<unsigned Size>
struct select_by_size {
    BOOST_STATIC_CONSTANT(int, value = 
        (Size / alignment_of<detail::max_align>::value - 1));
};

} } // End namespaces utility, boost.

*/              // End alternate implementation.

namespace boost { namespace iostreams { namespace detail {

//--------------Definition of case_-------------------------------------------//

template<int N> struct case_ { char c1; case_<N - 1> c2; };
template<> struct case_<-1> { char c; };
typedef case_<true> yes_type;
typedef case_<false> no_type;

//--------------Declaration of select_by_size---------------------------------//

template<unsigned Size> struct select_by_size;

} } } // End namespaces detail, iostreams, boost.

//--------------Definition of SELECT_BY_SIZE_SPEC-----------------------------//

// Sepecializes select_by_size for sizeof(case<n-1>). The decrement is used
// here because the preprocessor library doesn't handle negative integers.
#define SELECT_BY_SIZE_SPEC(n) \
    namespace boost { namespace iostreams { namespace detail { \
      static const int BOOST_PP_CAT(sizeof_case_, n) = sizeof(case_<n - 1>); \
      template<> \
      struct select_by_size< BOOST_PP_CAT(sizeof_case_, n) > { \
          struct type { BOOST_STATIC_CONSTANT(int, value = n - 1); }; \
          BOOST_STATIC_CONSTANT(int, value = type::value); \
      }; \
    } } } \
    /**/

//--------------Default specializations of select_by_size---------------------//

#define BOOST_PP_LOCAL_MACRO(n) SELECT_BY_SIZE_SPEC(n)
#define BOOST_PP_LOCAL_LIMITS (0, 20)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO

//--------------Definition of SELECT_BY_SIZE----------------------------------//

#define BOOST_SELECT_BY_SIZE(type_, name, expr) \
    BOOST_STATIC_CONSTANT( \
        unsigned, \
        BOOST_PP_CAT(boost_select_by_size_temp_, name) = sizeof(expr) \
    ); \
    BOOST_STATIC_CONSTANT( \
        type_, \
        name = \
            ( ::boost::iostreams::detail::select_by_size< \
                BOOST_PP_CAT(boost_select_by_size_temp_, name) \
              >::value ) \
    ) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED

//----------Specializations of SELECT_BY_SIZE (outside main inclued guards)---//

#if defined(BOOST_SELECT_BY_SIZE_MAX_CASE) && \
    BOOST_SELECT_BY_SIZE_MAX_CASE > SELECT_BY_SIZE_MAX_SPECIALIZED

#define BOOST_PP_LOCAL_MACRO(n) SELECT_BY_SIZE_SPEC(n)
#define BOOST_PP_LOCAL_LIMITS \
    (SELECT_BY_SIZE_MAX_SPECIALIZED, BOOST_SELECT_BY_SIZE_MAX_CASE) \
    /**/
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO
#undef SELECT_BY_SIZE_MAX_SPECIALIZED
#define SELECT_BY_SIZE_MAX_SPECIALIZED BOOST_SELECT_BY_SIZE_MAX_CASE

#endif

/* select_by_size.hpp
GP5WOdPXJ/7W417uV97udXfmgxjhG+9M3xh6uQ69mhjxGOPMBzoesd3bKXo9DHovOP0VvS71uGf5RS9m+YdovdjlVa7Wi12+FGi92OVBhdaL/fxWab3Yz1u11ov9fNRovdj52QqIXsz8h4heej3pkav1YqdHgdaLnR4VWi92elRpvdjpUa31YqdHTQy9sU77BUUvZrohWi92uuVqvXrKNa3nnW5Lwm1iWC56rZB5opeFns1+sDscAI+Dg+EYOASOg0PhRHgSnASPh+fDUXCRnJc1gqVNJ8+3a43gq8W/Cv5vDtfCDLhO/L9Wu6PaLJ7u5Is7Z4s754o7c8Sd82BFMLQm6YhlrPeH5PJ3MVyHVCF7kYNIyvIkzzVLc7m2GRbCDchO5AASXMF6gMhZSPmKpITmv8sapob1Sz3XLtXrlZ6BGNYolfVJ45sjvwfmDwq41x9l7dHINUfda41uRNxrjLrXF3WvLToaKaibV0+m0nPrWTdUz63Xa4bWIqZ59qO7BWSuPeexd3jN0I3QNO9+q32ee3bAIxzvg4Z1Qc1rgsrc/M3Qa37+YT1Hn2vYUubpqzVAS56Jfx1Q7zVAvdb/dM/hN631mdg6n2/AFrP12p4x5/mPh865/s61O6sQaw7hhf2hc51O5xqdu0i/A8hRpBsbRo1G5iEVSBVSjRxEki9mHU8kHylHtiB7kVqkWynPM1KIbEC2I/uQg0hKGetxIrORCmQ7sh85iFjl3IuMQM5CipF1yDZkL3IQSV7J84zMQ65AqpB9SA1irWJNT2Q8sgTZjOxCDiBHkG6XcA2Zh5RcEt+6Bk2/pl/Tr+nX9Gv6Nf2afk2/pl/Tr+nX9Gv6Nf2+5fX/Fi5dMZ+RUmr5v0au/2evy/azDEuPJ6zy6f3w9Hi0t+3xhKFxJWMnqxULwuPt45s/nKnHgMj4UdYZ9JybqHXPa+/n+B17jYA4xoaa5vqmRsz1xU/HOsSZPq9v8N5jOyrVWIpPHu73t2mXNf+ks2/EU8FxfVO9x2qYv+V7j7EwjznwGnuR+JgD8xgC77EUav9cnSbkCTkOIH0c692q/ALTYQacjbKhn1nvlVWCjDKsq2paS7UGOvuGZe1U7/VSXeuk9p+JO4jdXzseMa+FKn2qrr7UA0hofdP41jR19IOa+j+lfzNyvdLiGOuUWtI/Ge6XXNfUV9f0a/o1/Zp+Tb+mX9Ov6df0a/r9T/2+hfb/sOFg2PCi0mOx/18P5hO9R/t++yjadWr99mHD55eVl85fvHL5ovIytVb8+1xffZLreimhW7G8DO9VH8LDGVbdeqnShzBcbDIM2ZbGWLWjqg9hwsyZ84tXLGBCm3aNIJVZej5US1xZk4LEMc+mbl+hxPfZ8ZqjsFe18w/tuXXduPc+zzlQcWWPHZ9W3evdzje3z73nOpjb217t/2M3VyDR/oJ/KzvMv2XVtsL9y58e0f0363e/+spI7zkQH6t9XSSd4XA5boaMlkQ7R/oL5sBU1347g+EFcBicD/sQv7S1jINBzGPXOMe10Pi1b3/vlivWJjVo/5Yq7nPv4VI489jv3RLPvi3/7/u17F3b1CfS9PsPe2cCH0V1BvCZXASygSSEEGLkkluK4YaqyKGIVmmqqIhYEkKAQICYhFNog6CCKEalLVJsUVFpS1sP1FgvatXiUcWzVFGCRUHBGqkIWq39z9tvX2Zn34bdAFbbnR8f/+yb771598y845vYETtiR+yIHbEjdsSO/97xNb3/89o8u7L0KLz/O+/um1zz/6/G+dNxOdIEWYB85nzL46B6d8fmzOjzzz+Hrw8W9Zk9s8Q//5+u5v9xku9iZ8PLlf505ovjjWsCCM9jKxz/yvQ=
*/