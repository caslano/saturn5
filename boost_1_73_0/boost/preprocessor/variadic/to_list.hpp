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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_VARIADIC_TO_LIST */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_LIST(...) BOOST_PP_TUPLE_TO_LIST((__VA_ARGS__))
# endif
#
# endif

/* to_list.hpp
aBl+t78/Wa9m6MH+NJiE+xM9BNWnaB7rzWfgMXdfnGAZOVHgrEOv4lDZijMPpv4D/cWw4OFyPZ754VPFIoTGFtP9YOWE3mxGwKii74VAnbs+UGNUoXLOElj7Ef0Jg0VIbT0/BXMpaAeTwTysVws05U2p1DTAYFecNdbTCqWl+6oNM7I8zMVTZHEGzGABfJyt+sBpD7acsRv6YcX51B7e9O6Hzqd6v1/vDj87vSun3v3M0D60
*/