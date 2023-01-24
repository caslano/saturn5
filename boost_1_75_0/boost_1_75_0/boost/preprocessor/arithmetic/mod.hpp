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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_MOD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_MOD(x, y) BOOST_PP_MOD_I(x, y)
#    define BOOST_PP_MOD_I(x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_MOD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_MOD_D(d, x, y) BOOST_PP_MOD_D_I(d, x, y)
#    define BOOST_PP_MOD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* mod.hpp
mcT+oLfLCGPZzNmSzUrz8LpJAm/0/+t4XRtBbvwsS2NnFptdJ7EZZ56ON5IRHTsj1mGUw/Zm+lIyY2UbuHe54Vi2qBlJqB+bsUjq5Xzx44uOy7EmfowZjzC+/IRQ/lqlo8tYHg+433T9peq7F+9fglquPV69rxnd/0BsmYlIg65yRJyxjPdJ2EIzmFzmGchBwr3D7UH+gkzIYT+WEe/BzfjZku8rFXuKKIsFOJqqksV+obxSWdT7hiMfgYHcaPz/F5ydB6K8+2MLjMZjP+xF/dllp+u9KOMX8Ky4yV9NdRKP3cRqOKaKDNIYc8IYiH2C5DcLbaNewniiGZekw3E/sGvacd8gfMeO4/B/2s+zKZ4Xez1x7Yjc8COQ0h9Y03gmGzuESawP09Xz8Gr6v1zPczjbd8K6RNo9mV4ez3iao3eVqTo/R3l8gTUPYbp0AbMhWrI7WsBGzmymZyZiPTPwtyPjbhbjZQCrZxrrFfNZP6J+TFfPYLJfh320nKchrI/Y6fFijeVtURJtmd62xl8d8be17q8lymkBw57PfjviaGuJd9CDtdrnKL/B2Bd+4YYiDOQG4Vjtx3JtKpR8wei1w75sxtplPuNlFrvXcon3xDsagNL4jd0H9eW2eH1fLJvMriTZz0EuSKqTca6dj9cEM45q2k5tsaQHk05LvVrsWG4i6//zmGafwMZAd7QtzbBv8ldOFfgV5TmrEr7b
*/