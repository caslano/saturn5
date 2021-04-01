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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITAND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_I(x, y)
# else
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_OO((x, y))
#    define BOOST_PP_BITAND_OO(par) BOOST_PP_BITAND_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ ## x ## y
# else
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ID(BOOST_PP_BITAND_ ## x ## y)
#    define BOOST_PP_BITAND_ID(res) res
# endif
#
# define BOOST_PP_BITAND_00 0
# define BOOST_PP_BITAND_01 0
# define BOOST_PP_BITAND_10 0
# define BOOST_PP_BITAND_11 1
#
# endif

/* bitand.hpp
EXbrj81J/ZbSeCpjNrVYadcUw8UapKeWjzNIjAwFTKYMRUCOWrJIKohe+jLFNxYCjw6aLT38k3V7Nasyz3yy/YKUJoWFM77aPQbYaqIAVHOJOFZIOrmyb7751dxqCKkXVOZe/nvI3Sm+6AOXPCaylRjwAYrsLzX83KYWaZABqIhOl8OLZ1jYB0S2Jp/5OxOoq0k4KefdFShNOdGvy+aIjBQNrxB+C8IM9c7zBXgkuNjqzxb4mAP2JDrv4KHYj+ol66WSMw143ca8UU6wjECLKdcfvjefkI5/KyQ47BpsE3DyPkQfIr4Ol3uY+9AfZAwliacVlB1JjpGwRKUF1BBMCigYzmWAJis/haY2CAzCDOf+EXzFSrtF4y3sc2/dUfHdQcQpcIOcAxT4y+y+DOHzs9SYNJzTnczrxcsAimMCIA4a8HYpfK3+Lm9r+YidcH27UZYT5Md82XAe+tDg32xM26ErYxR1r77LPVyG0T9+/TprSkoYLMdaSspnb7F+Dz1oUQMxWX+/pL90b9xW39nj4NJqwvxoUNE5YWmXcjMMotuQESM46mtjrEdicQ==
*/