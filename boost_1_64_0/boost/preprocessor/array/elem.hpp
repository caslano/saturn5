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
# ifndef BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_ELEM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# else
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_ARRAY_ELEM_I(i, array)
#    define BOOST_PP_ARRAY_ELEM_I(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# endif
#
# endif

/* elem.hpp
lUFy2ck9F9+onGU8/ZO2Z5XRTlRq9p8Jip3ejdLFAZhDFnzUiI5mfI60pRtyRJxS7KFkMZyDICLEuRWRZbhbTse3WUSCFO+bzEaY2ZD/S2Mfgvj99wk2YUteSEZLxXxL8lKPz7r5a3WCUngw2GCImQP0THig2wUcE+lMPYmxrpGkpk2aeg1HzHlXt5BSXDVDVw/cDb6gjs+pSnhMKDGoEkJFB4a3jH+s7e/FpyPzZrSO9b4f2P505sjU28I0/mbA/ONqx+NWA85GDTaTT1Q7cm+B0MGcOrri5/l5DPLMJ5z6eacj7JGgv9GwHl2C76nohiB0hbLC3ZzdXROLGfl2eTkA/8XI1CHqliuOEjaIdWd780XX1zuQxbpTj8kU1aVnw5VTqP8KMchEAeTw3yKj6x4cGvtBucYvbTk6fhMeWe5RGEu3pkOksUktPjsEPLYSh++sr+YI0BT7BpuivGoBwFLNjpJ4gSgRT8EgI4w6y0zZrUNxm1ZeAt7hJoGvTWG7sqYFxgQatHNdrQU1n5SpEAx6w79YkfbGMFh0UuKr58TiOvlfPV3C69JO3A==
*/