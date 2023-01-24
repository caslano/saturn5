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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_DIV_BASE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_BASE(x, y) BOOST_PP_WHILE(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# else
#    define BOOST_PP_DIV_BASE(x, y) BOOST_PP_DIV_BASE_I(x, y)
#    define BOOST_PP_DIV_BASE_I(x, y) BOOST_PP_WHILE(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_P_IM(d, im) BOOST_PP_DIV_BASE_P_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_P_I(d, r, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_O_IM(d, im) BOOST_PP_DIV_BASE_O_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_O_I(d, r, x, y) (BOOST_PP_INC(r), BOOST_PP_SUB_D(d, x, y), y)
#
# /* BOOST_PP_DIV_BASE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_BASE_D(d, x, y) BOOST_PP_WHILE_ ## d(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# else
#    define BOOST_PP_DIV_BASE_D(d, x, y) BOOST_PP_DIV_BASE_D_I(d, x, y)
#    define BOOST_PP_DIV_BASE_D_I(d, x, y) BOOST_PP_WHILE_ ## d(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# endif
#
# endif

/* div_base.hpp
p7VfzmnXeMXdd7p0nJ24ddTuA2/f694kbV50SWbMhH830bR0cx/X0jbj7c+G9tg2+sv3s5p0Pbn8xOQ+b3t3mHL/p10DJzQpHnrdcs/xeg/bpq+ws22WbfNa/WHrEiz/eLdJ4w1DMvFu1vcYOHMMt0N2pGnTemEuHVTfuO9RdljPDdrbf9S7qcMW7LyWPfKZZ/CP8baDfd744dAU5a2PBu3a+GuJf9nyelaFLjPOfdA7PSJph/ufC4c9micZs7B03fI1XOy3rn/8ZT8sYGLHJopFHbttvfy6xf10Lr+7m/mzU5od6x5w71iele3z++H6+aDfP/3wyht5tza9uStre+qAXZab38uM6XReLfnkrXmKD3z/ZXZruuOLZuEW1o2KxrVy72PZ8BNLv7FdlG8UX/jKaspWy0aHHeURdo5ZHec5uSwcd7H3vx/3OH7iR89Ldz9sUP/ZhfZNWn3Yf8jMN7nfNjnNluWs4R55fnYz9w9rM271kQ8+upS1x6P3be697M1nzvcyD2ux/ZfG+ZOL27W6U+/I+oHOIYOGecTEOB4f2K7F88+blx2r16j73JONxs1qxZlPzryzTHbrrUZlY1vXWzuw5xivMZtubP7h/7R3LeBRFVm68iCPTudBCJAghCvPBkJIAiISkCQgyNMAYQRFJ510B1q6k7Y7IYAwH+mIAyyCioOIrxBQEZVBB3dwPgcJ6MAGVnFQRxzk
*/