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
Rbwy8taHF0oiMbRN9eI3xFZYxeTpH/iGx/UnMmkLQgip7X9glYukJL75E6NGc8nRbCX5ttQffUixJWu524azDt/t6MTqLZEak8QNEzgY5Y+CFBiy2ihxxtM1+Q8/7wtVHYF+K7ZppXIwrq1pm9OHxMczr5I2Tf7Zwf6nFLfVM5SeoCpILq8MHc1aRpKnxkqyJX1qSmAhll7S/JnspNy8u1DqqRSBR0At4ji9h413cYmKI1O3gFL9pVcDYx2w6gqBBznBTPyc3uN/NevHCjolu01QQXEmrLORPbAVn6QneQXE6KTXTQWNSgQaLEtVoia1DSZS0UJC9CmzsM6As3QRSBZiLykbwfpIrntGbspxK/OvLxCvr4LBhzxXbOi7rRZZpjUuptaHIvICqHepor5hUUnKzUAZ12J+9QhKotX7p1w+ViP3mw419U590L1k03gdzsv1N4qMS2SqLplIKpRzS5I7PkwvQlL6nzv5ASOaf+b2JyWu6fYth5UPd/jnD2ArgnTuVBQ0wgAkfZjfbg8Y2aA4D7xOBQSaUxPtVBd5EQxxZzZyq7+EwxqbIg==
*/