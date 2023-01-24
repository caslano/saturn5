# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
# define BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE tuple,)
#    else
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
# endif

/* size.hpp
g3IA0gk3/OHxPE/DVS+7mZBMt0h3yBqwITcNKjzCZPARkQDJK385sEnRYmDVT8hvOZBC6S9MHn0tbhoO1qsoIYjZ6s+TWaNO7dJl6ovJUxx6QjK/ILPwnfcBa9GmyjlgjZswrJhfiP4y3eNsCZPJ6gZGzGlveEpnHXZInMhX6ZXUtfuAJy70vmdt2n86WbvAAE88NaK4dz7wgw/gWOAJRHK8E/nL8B+HQSJYJ2gdZ3I4I503A7OUwiKD1fsecVWjEE4r7V3UHdOZsg/SWS9XLRu0Sl/P7nVWvhv77WqT+OQsbk5KieLfRZhYn55N+67LZk+ixpgAgEsHGCf43hSJiSoufgfNE8FVYbkg3yGThw/PrydqvSWHV0hBDlVkbh+GL5UImlXUIuxenK7M72FjemToWTkqK5+h3JjiNo+iBaH/XrQwUbOm611B8Muhmt8pYTfs8mGIhOg5a/62W3XTd+fsioqODc2A72nmqgotG7h9DN5FUI09LKmp9LBe//v0Ia/GP6TGv9iogCStP4GhGYDN8Jn+8+VQ7fPQn6HMhCj6Ggm7hDbkE2SPIB/ki5555GOGBP0E73jGaDUJ2m2BEOCXFumNm71KGjODpP2eEvLOWbURsIB4TDVKZjrjQbhtn59e2b6iX1YNys0/VU1raQEebcqJuddCVPneyw1NbPTGblljZh+mjeAj+/pjgCGCGpC77ZwMYOufeZbt
*/