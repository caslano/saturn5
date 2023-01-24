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
# ifndef BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
# define BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_REPEAT_FROM_TO */
#
# if 0
#    define BOOST_PP_REPEAT_FROM_TO(first, last, macro, data)
# endif
#
# define BOOST_PP_REPEAT_FROM_TO BOOST_PP_CAT(BOOST_PP_REPEAT_FROM_TO_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# define BOOST_PP_REPEAT_FROM_TO_1(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_1(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_2(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_2(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_3(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_3(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_4(f, l, m, dt) BOOST_PP_ERROR(0x0003)
#
# define BOOST_PP_REPEAT_FROM_TO_1ST BOOST_PP_REPEAT_FROM_TO_1
# define BOOST_PP_REPEAT_FROM_TO_2ND BOOST_PP_REPEAT_FROM_TO_2
# define BOOST_PP_REPEAT_FROM_TO_3RD BOOST_PP_REPEAT_FROM_TO_3
#
# /* BOOST_PP_REPEAT_FROM_TO_D */
#
# if 0
#    define BOOST_PP_REPEAT_FROM_TO_D(d, first, last, macro, data)
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_D BOOST_PP_CAT(BOOST_PP_REPEAT_FROM_TO_D_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) BOOST_PP_REPEAT_1(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) BOOST_PP_REPEAT_2(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) BOOST_PP_REPEAT_3(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# else
#    define BOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt) BOOST_PP_REPEAT_1(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt) BOOST_PP_REPEAT_2(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt) BOOST_PP_REPEAT_3(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, im)
#    define BOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, im)
#    define BOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, im)
# else
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_1_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_2_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_3_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
#
# define BOOST_PP_REPEAT_FROM_TO_M_1_II(z, n, m, dt) m(z, n, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_2_II(z, n, m, dt) m(z, n, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_3_II(z, n, m, dt) m(z, n, dt)
#
# endif

/* repeat_from_to.hpp
QiqOwom638aerSUBgJdXNPmtM8zHkpnOMUty10+0IrEa29APS3uV1/yPIiD0XbjxhW/old0dxThGqMnQcIsGKzkl72SY+0S6+opQ6tR3nvwsrsXgLrQpP9Pwhp4YrrH9HiNxXV9oLi/nd/ddz/IqLryOGKyo1XIdpyLZfgaocbJoqKh7bnUi3Plnjlaz/3n1/OYxe3khJb0mhzZHxasDwwpNdpKCtvNUi+bf5ScuiUvszq+1LZW5jUktXulIQff/CvHzfzvbFBzfgtpCjupvDFP0kbKdLC9Nx98f53OsuMb/M2fSTRbBNsUooR1r5zcS9oRGF5q+V3wqIZn84797P91r9mi7e66zvkckybOjvO1Xw5Xqm9fRCVM3G04ZG1Csl1t7Y0SfMYBnwR/jn2hHtIjTgmVYUjcapyjEvMqFWUVcoofTIaXpSuQaH25HuJPY9+GKK3mXUoMr5cfr6w4pI8ylyEtj7K21gxmAni7j9nuozFnoJ+qEgBAG3Wem9tnlCsTc5UxxeXH5oDaVzsKnvRyF7aT5SNLIOyq/Pz3t7v3uXByDNtSCnuISb+iETGUzF8CHjafp81THG9/PtYJS5rJHLYtg6rQsXuRwDc07blMmLxbIuzlj5Ux1Hy76fJgpPrbXuXur+h3f0PeOXD8ZVgR5WMdUO+Nc9mTip/WTj4mcKfuXAzd0LzvwAr5enTF3XUayuFzVtACcELTy
*/