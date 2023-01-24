# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
# define BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_ERROR */
#
# if BOOST_PP_CONFIG_ERRORS
#    define BOOST_PP_ERROR(code) BOOST_PP_CAT(BOOST_PP_ERROR_, code)
# endif
#
# define BOOST_PP_ERROR_0x0000 BOOST_PP_ERROR(0x0000, BOOST_PP_INDEX_OUT_OF_BOUNDS)
# define BOOST_PP_ERROR_0x0001 BOOST_PP_ERROR(0x0001, BOOST_PP_WHILE_OVERFLOW)
# define BOOST_PP_ERROR_0x0002 BOOST_PP_ERROR(0x0002, BOOST_PP_FOR_OVERFLOW)
# define BOOST_PP_ERROR_0x0003 BOOST_PP_ERROR(0x0003, BOOST_PP_REPEAT_OVERFLOW)
# define BOOST_PP_ERROR_0x0004 BOOST_PP_ERROR(0x0004, BOOST_PP_LIST_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0005 BOOST_PP_ERROR(0x0005, BOOST_PP_SEQ_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0006 BOOST_PP_ERROR(0x0006, BOOST_PP_ARITHMETIC_OVERFLOW)
# define BOOST_PP_ERROR_0x0007 BOOST_PP_ERROR(0x0007, BOOST_PP_DIVISION_BY_ZERO)
#
# endif

/* error.hpp
mqy7vE6Z+cX/sk/kwiIpMXP9c2l9fEgBEN/dGaHS9CjlR7sGPgh488oKhg/LbGr/OZfV3YQ0hpA+ShoDbkLco9dfyUy8XkKooO7rvjddyFVpV8JKIENfaoQl7S32netvG6QIZJJua9W5jKEpu1M3pIY7bW3+td4HkW10rh9kp9wPBHhdGOhwv8iNvstxhskYZ8eZwC05DsHisQA0b/9Hrtt6dGHG3L9MeZB5X76nJuPs6e9wZE6KuhWcGuYN6dMbfvClzN5X9l7nejzOUzYaIfIFvTEc2ucldQOJFE41iPpdC5+u+W81e+H7kPmj/DzCO2v3yFbwVhZrHzesg4xdcReLWQsqeJPVenwjer+2AHZrUwoSVgr6vTaD2OZpp6MO/u2B0uXQ6RUbzwtrAyF+NKhPHzYZuP3ykv0GRgwaN0AwKwT90ro+MPrLh65xohoC/2rrzW4FhA3qe4IqsaUSNJ4e23DgvA2XD5zQeI7mcP3hK23stJVhj4QNVAVgVp6f1DS2YFw+YnzwubTJsMuPllFXbUP8go+WYi9K1x99va0AxMRqW/I2+ZQRdoDJ04vvScJF5t/mlqZXpppzMmEwdbsTJWn4Vo0NP2bcuYI17mXiffp5DDQry6SH2bCbDIq0oT9jnoCXB/TNiKjqtA01TYhw/YYGnrspqeBNXCJUS8OT8KPFQmbMHXa3HZ6n4FXLAzzvH/NL5lxdRx/n
*/