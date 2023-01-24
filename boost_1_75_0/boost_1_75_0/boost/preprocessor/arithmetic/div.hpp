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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_DIV */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_DIV(x, y) BOOST_PP_DIV_I(x, y)
#    define BOOST_PP_DIV_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_DIV_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_DIV_D_I(d, x, y)
#    define BOOST_PP_DIV_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* div.hpp
V717//LLL++3bdNcl8cT77//3rt8nvuK+OnY8euva30nr3aebclwutdg+eb/lZRw+iAQqE4fApyzIfrUYcD5GHAOhmux0YBze6XKFOd1YU+oTLQb0+GusCck6h84PasboD6Ca1djK62D8HHe1qsjjdWBOgtQnwDqMkAdwPBRpwDqGkC9pqsLdQE0eX8doE4D1H+AepDVgbqOAeo9QP3B8FGvsPeRR3euY0fUjUD4qAdh7OTbgPoOUD+iDZwp7G95G22oVLT7kxg+6hlA/QSo33T0UQ9Bg0/2A+o0GDvpDrz1vifey2NAPQqS6esA9SpIEFDPmbx/wkddC6hzAfUw1hXK5IG6FlC3AupYQL2M+LEm8VGfCvs2FQHqPMjPpxhROYD6GVC/AupZQP2Nj/6V41NCPQnFRcWsDnV+PsNHPQ+o7wF1f6X4Yh0ECWcPg/LsEYg9cwxQlwPqb7iGeFXh/t+U/uk8U9FOHmFgJ480sJNH4S/RiDXjetbjuvM28VtmcQI9ZhGaDeLGclO42dxMPOqn1wa8zllyf+BV/NODjOvPLeDmc3PY/y25SdxUbgY3EX+14mYh7kz8/b1BDS6c64BhiL+Da8hlN6F7cDWSiNkALZZbYfncZlTuwrVlf4ZJQh+vc+9xVmavC7y4GF1BvH6CvNbX8ToAORrPTcf/W3GTGZciv3ZGXNKyx0fI58fcQa47N4/xscJE/R2x
*/