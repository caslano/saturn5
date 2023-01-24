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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITXOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_I(x, y)
# else
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_OO((x, y))
#    define BOOST_PP_BITXOR_OO(par) BOOST_PP_BITXOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ ## x ## y
# else
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ID(BOOST_PP_BITXOR_ ## x ## y)
#    define BOOST_PP_BITXOR_ID(id) id
# endif
#
# define BOOST_PP_BITXOR_00 0
# define BOOST_PP_BITXOR_01 1
# define BOOST_PP_BITXOR_10 1
# define BOOST_PP_BITXOR_11 0
#
# endif

/* bitxor.hpp
XlT63BGsQAiiMijGXngHZQp4Rz9uAfHwzc0vtONXD0RG3OVyJ6OfvJ61apzLLxErFSsGLlAs3IPpwRa5GkZFDfvSEAUIM4Qkl99oNOpOJBe/YdaO/1MglSlwhRmiRh707vhTkL/GMIXiMIUw1ktntFS+Wj/cK03srfkuQUzTZcwXX5lU5VZacRiXXsP/rjFaWRi/QLhkP2VH6/YvlJ1FWBtcGkZxihUoDgWKF/9xikOR4gVa3N0tOAR3d4oGd3cPVijF3QlWHIJDsIxsZjEzzzyzuYu7vHd1PnnP6MHfb5Cyb9rA9i6R4vwXSx05ncGNkxZb7bKzbjgZfs+GmJXNVQNFqalO86risJ3kDBDYolu9rGbhfJrf+qRZWbepNUlUIXvFVDoRDRhjc8HAbk1h2tWM3KxHUcbfisle6iEdY61qvaFLKTLPcNbtIaC86AWXaxY7q4juSbNNmK2zgevBNR7h/cm/Jn5ZDfKYpbUpYsHgI8h7cPjg7oyWr3hbPjzvojkRDr4Arz4bC71wMK2+XyFxKbwuAifzDt9TQSIAJRDVK+yLOXhP7cu2FskF9YdXeMZsAP++AihGSLsU/HVi7BvuY47jgsghOGJPLONGIBRy+OIBzb5+higzXz5hxDHCPYUyuPR/2o3dlLyIU71IPKxchG1m90zJru33j+pWg0A1sfu9r0/yr3I/VQOAkNtNYBIQeN3St4BVD/9L
*/