# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# define BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/check_empty.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# define BOOST_PP_VA_OPT_IMPL(atuple) \
    BOOST_PP_TUPLE_REM() atuple       \
/**/
# define BOOST_PP_VA_OPT(rdata,rempty,...)     \
    BOOST_PP_VA_OPT_IMPL                       \
        (                                      \
        BOOST_PP_IIF                           \
            (                                  \
            BOOST_PP_CHECK_EMPTY(__VA_ARGS__), \
            rempty,                            \
            rdata                              \
            )                                  \
        )                                      \
/**/
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP */

/* va_opt.hpp
344Y5dEM+6t7uVAJanKqwLQzqRaEl9bBJv11pdRV5mShru+r01Isj+5y8lSHJ35QGjLkawjoG/s1XUBt79exStO2m670CZbO1oEwhXAwRTqKQa5lD/OHWc7wVMxslebrJHj5QX6VR/dPIPSarN1HevVdSTUywBoVViGzjFIpXaFg2hAl8bxTi23s88ycjxW6OTqFEnohCDFMI9dKXeqWWFLICPU7V902iglSzCde0IuhZKFase933KqiSuX4Db9B5ZApmckABSj7knxJ0zJnqO6tZHVfwAOfzE+8bNBfA1R9cnzb1WDG7NduVFrAG+8unZz5VvRPYYHm4emH++mr6pwcM+RzN67G7E/fXFrMegE4uDXjctpIFDk848+6Ia0biZPR116FWQlOLqMUVL6P92dmOJxrEAM/mSCakvWd0w8BZ2eEZRLGBF4aJugMFvoXR+oMeR0YG7zoMAGXRoy4cWSGLRF0EZqtL0+1wSD2HlBajz3uZ/26MQcy/1M3/+WYgDBDW/8zZv82Q8NSEJeeEV9y6nKRgcIq0RH0pBXFe9fJj2VmvjV+Aw3o8zl10ZySQq3E7NQf+vk43oRbKxp25oHRllPbTwXDDT/PgWl4ZJ/3s7XjOAq6amyEBInK7ZJiAsAhSvCwbhWEgmhP+guG0Eae0EoglbtE/uKX3irCibCSFKxtA0mGbC32Pa5tRf7DyfkPHL/dp8H5laK7
*/