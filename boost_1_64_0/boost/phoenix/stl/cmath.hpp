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
NcN4cqH/axhbLsd4cn8L+72LSbyb5Xkva/M+HsX72YdLeCIfYOb1NDvsf1yc6+m5sP/nmcRVLM/VrM0Xw/7X8Hi+xOFcyzFcxzA+s/6rMedrjvGZ00I8ZzCJE1ieE9mQk5hZHw8K+zkwTn1cL+ynPvdnA4b49R0N+YwT/7xQb1zNGryOvXg9R/EGhvj9sR9UiDN+88n7iZ+nMJmnMiv/4X0d4oxP3T2kuzdbsg8PZz+24/EhH8uEaWE/5cO4fJHyuifs57QwLt8QNuNQHs4U9mcqB3AEx3AkJ3EUp3I0b+AYzud4LmUa/84zuIET+D4n8itO5recwn2l6yyW4dlM4jmMXnehDyZbxRlv8fQwrvRAVmEq63I4m3AUm3E0t3OWkNGXkkVDeZT076mCl3Fq7Y9FWI7F2Jb7sQcP4OlM4Bgm8myW5aVM4o0sx7+xIpfyYH7A2vyQdSg96v3Qh5ErQ/5Kc15IT+OQniYsx2ZszRZsx9bsxCPYh0exPztwILtwFLtzHHvxLPbmNPbhxTyeV/AkXs3TeS0HMnocQt9AtotzHOaFdF7NcryWtXg923ABj+DCsL9twrqwv/nhOFTy701hf/eG6+s+luNiVuUD7MSHOIAPcziXcgof5Uw+zr/w77yBT3Ehl/N2ruDTfJ7ruIqfcDX3kZ41rMSXWIVreThf4VF8jb34AQfwQw7k10zjVp7JHziVPzI6Tmbos8dHhJzjZJ4X8n0+y3E6m/FCHskZ7MmLeDov5ijO4jheyjRewem8kn/hPM7jjbyRN/Ne3sYHeHtI32who+8ea4fjUioSb0hfajjOw1iOI9iWo9iHYzmMaTyH6byck3kLz+ISTuUKns83eAE/40z+xMu4g5dzO5fvE/q8hT5w0mWINucBvbRlSxfPYjlOZVuex6N5Prtzmv9O5IUczhkcy5k8kxdxOi/hRbyMV/Jy3sgruJBX8m7O5sOcw6Wcy+W8iqs5j6/zGr7Na7mN1/FnXs+iMnUD9+dNPIKLeCxvYy/eztN5Byfwb5zCu3gB7+ZlvJdzeB8XcAlX8EG+wIf4Gh/me1zKD7iM3/FR/s7HeKCyfZyl+QQr8UnW4NOsy1VsyxfYiavZm2s5kK/wAr4WMz/GXL7B+XyLC7mBd/A9LuX7fJof8EV+yHX8lG/yM27kZn7BL7iFX/FHfs3fuJXFnS/bWIbfMInbeTD/wVr8lg35PRvzJ7bhz+zIHezKX9k9zKPRtwh4GvfhUJZgOhM4hyV5FUuF68sxC30GrQvj0NaPjv8a7e4Zrv9klmMFHs6DeQwPYU/WYH/W5hDW4RjW5zlswIvZiHPYmDeyGW9jc97PDvw7j+YqduRqHsPX2Ykf8jh+yS78jt35O3swct72Yx0ezxY8ke3Yn514GntzAE/iYA7iEI7iUE5hCs9nKqdzGGdxFOdwNG/kGP6VY7mI43gfx/MJpnEFJ/FZnknlr+k/9BtkNSFR+Rdl5u921cN91aFM5GGswhrczqrCtvD+g4TZQmEhKbzf4+phu9BHj6V3sV3jDvnbX+8/2F+XmO3SMve3i+1mx+zvzhzbdYvJ7+LM/e1iu3X53G5b2O6AONsN3rmdkzLs7w+3E/K5Xft8bNfZykG2g35EuceX//IA1ye/YRK3sxK/ZQN+x3b8kb34E0/mbxzN33kGCx3ofMY+vJ9F+BCL8hEW43Luy2e4H1ezODfzAH7FBBaXtpKsxdI8nGXYn0kcwIM4kMmcwPKczYqcy0N4G6tyBavzWdbkBtbix6zN31iHhZRNA+7HRqzAxqzEJox+Xwx9kPigkHP88fOVR1FOYxNOZwteyDM5g+fwEt7BS3k3L+NiXs7tXCdsC/E=
*/