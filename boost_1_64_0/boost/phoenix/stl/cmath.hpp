/*==============================================================================
    Copyright (c) 2011 Steven Watanabe

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_CMATH_HPP_INCLUDED
#define BOOST_PHOENIX_CMATH_HPP_INCLUDED

#include <boost/phoenix/core/limits.hpp>
#include <cmath>
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost {

#if (defined (BOOST_NO_CXX11_DECLTYPE) || \
     defined (BOOST_INTEL_CXX_VERSION) || \
             (BOOST_GCC_VERSION < 40500) )
#define BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)                \
    typename proto::detail::uncvref<A0>::type
#else
#define BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)                \
    decltype(name(BOOST_PP_ENUM_BINARY_PARAMS(                          \
                      n                                                 \
                    , boost::declval<typename proto::detail::uncvref<A  \
                    ,  >::type>() BOOST_PP_INTERCEPT)))
#endif
#define BOOST_PHOENIX_MATH_FUNCTION(name, n)                            \
    namespace phoenix_impl {                                            \
    struct name ## _impl {                                              \
        template<class Sig>                                             \
        struct result;                                                  \
        template<class This, BOOST_PHOENIX_typename_A(n)>               \
        struct result<This(BOOST_PHOENIX_A(n))>                         \
        {                                                               \
            typedef                                                     \
                BOOST_PHOENIX_MATH_FUNCTION_RESULT_TYPE(name, n)        \
                type;                                                   \
        };                                                              \
        template<BOOST_PHOENIX_typename_A(n)>                           \
        typename result<name ## _impl(BOOST_PHOENIX_A(n))>::type        \
        operator()(BOOST_PHOENIX_A_const_ref_a(n)) const {              \
            using namespace std;                                        \
            return name(BOOST_PHOENIX_a(n));                            \
        }                                                               \
    };                                                                  \
    }                                                                   \
    namespace phoenix {                                                 \
    BOOST_PHOENIX_ADAPT_CALLABLE(name, phoenix_impl::name ## _impl, n)  \
    }

BOOST_PHOENIX_MATH_FUNCTION(acos, 1)
BOOST_PHOENIX_MATH_FUNCTION(asin, 1)
BOOST_PHOENIX_MATH_FUNCTION(atan, 1)
BOOST_PHOENIX_MATH_FUNCTION(atan2, 2)
BOOST_PHOENIX_MATH_FUNCTION(ceil, 1)
BOOST_PHOENIX_MATH_FUNCTION(cos, 1)
BOOST_PHOENIX_MATH_FUNCTION(cosh, 1)
BOOST_PHOENIX_MATH_FUNCTION(exp, 1)
BOOST_PHOENIX_MATH_FUNCTION(fabs, 1)
BOOST_PHOENIX_MATH_FUNCTION(floor, 1)
BOOST_PHOENIX_MATH_FUNCTION(fmod, 2)
BOOST_PHOENIX_MATH_FUNCTION(frexp, 2)
BOOST_PHOENIX_MATH_FUNCTION(ldexp, 2)
BOOST_PHOENIX_MATH_FUNCTION(log, 1)
BOOST_PHOENIX_MATH_FUNCTION(log10, 1)
BOOST_PHOENIX_MATH_FUNCTION(modf, 2)
BOOST_PHOENIX_MATH_FUNCTION(pow, 2)
BOOST_PHOENIX_MATH_FUNCTION(sin, 1)
BOOST_PHOENIX_MATH_FUNCTION(sinh, 1)
BOOST_PHOENIX_MATH_FUNCTION(sqrt, 1)
BOOST_PHOENIX_MATH_FUNCTION(tan, 1)
BOOST_PHOENIX_MATH_FUNCTION(tanh, 1)

#undef BOOST_PHOENIX_MATH_FUNCTION

}

#endif

/* cmath.hpp
A7V6UTQ5pxHmUDYADd/l76X+heSjxj5GVHJtUjIf9K2BlmGPZbYYe3ZiEUL1IRr4TMX/Nykh9Di+ZHxptnEsWmRmWtrYZGynsb5yTnNEI25B1mgclAvOQcbQmZ94UD8zXlz+UINkq8KBsmpaAazzayVSks4emUst4Oljm/DjmAqAP8siaG1/QG6RSXEvJRcOgCicZqmvd5+xBeZ0B9Pa0RPxo64lVdeW3CMVT40DuFeD8jrxmhgG1PnWmS7PH43I0gmAk9+uQ16qDVpELa7bMo1RXl8Cu3UiP1//nSZ6bxPmPOV/akq0FWIXN71u+FKNl+hCvaaz3G54a2kswwQWibjQpsLHpdaHOj1b2KY01e9THG5qgajpo305YVuMlDvJ9JXoTBnjDEgnNfdkfqx2f+aDn3vuxvcvgqJIx8CIm/St9HCqHWCVFaCAd5H+y2ZFNHFMIoyWOzrW2zJQYPtxU4x1fWSxUrAV/Fo7hz2eoNzNjQ5rxjpIUrKTXQ1tqndoqpYUxh7oCPg4pTN1W28/DjZa0F2PZrVbZHuURqlH6JIoxbVMdtgpSs+Gjg==
*/