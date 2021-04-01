# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/not.hpp>
#
# /* BOOST_PP_LESS_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# else
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_LESS_EQUAL_I(x, y)
#    define BOOST_PP_LESS_EQUAL_I(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# endif
#
# /* BOOST_PP_LESS_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# else
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D_I(d, x, y)
#    define BOOST_PP_LESS_EQUAL_D_I(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# endif
#
# endif

/* less_equal.hpp
o1D+IhsSnak6LTwo5urTpXY5gjBgrATbTLHtpWpAIzRkc5KgN+Vfs+gh4R5DNNElyLKYHUiIBXcQVzfAn1jAOrh4QdrdfXmHeR486p4G2dyiKTZ7wU+yjQJMKaOK+T8fosAOQ5hnE9DNxtlQc9vRjCJpAIxgWGDVNROAnQuHNjWoj1o3A1suAFKUfsKnU0LJr6P4TK5UZ/sd68a9YIGGPt+EXiE9wvgPQy8tMtq8Icq3oI02qkxjldzb0GAxqB5tewjq+KHwIFKxB8JY8HPv5p7ts0M5QZkLME75RbkCbZhmFBZIDsMjIxnpSXykh6tXcxlcMODNn5WtqfqeT9JqV3562FLAmEXvgrDWgs0tPNDACMlgXfbbgB1/aFgjHu3BFmwDlsS+Vc/r83lZTftj+lA/9rxwBiMh0q8y3wGbZU0i31P5zw9lQzvWuW0MTM682oGS0EIWzydHaXJ6Deal2SaVUVnUMFNIJwi4pJ+isrhM3OJAdZRw8p9awlkPca3Wx3J/mwOblK1HeHGl/A5A0bLY/1relEOB46X1CT7XdCrVKNoXNf+HLRyLgA==
*/