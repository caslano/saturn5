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
# ifndef BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REPLACE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REPLACE */
#
# define BOOST_PP_ARRAY_REPLACE(array, i, elem) BOOST_PP_ARRAY_REPLACE_I(BOOST_PP_DEDUCE_D(), array, i, elem)
# define BOOST_PP_ARRAY_REPLACE_I(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem)
#
# /* BOOST_PP_ARRAY_REPLACE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REPLACE_D(d, array, i, elem) BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem)
#    define BOOST_PP_ARRAY_REPLACE_D_I(d, array, i, elem) BOOST_PP_TUPLE_ELEM(5, 3, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REPLACE_P, BOOST_PP_ARRAY_REPLACE_O, (0, i, elem, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_P(d, state) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(5, 4, state)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I state
# else
#    define BOOST_PP_ARRAY_REPLACE_O(d, state) BOOST_PP_ARRAY_REPLACE_O_I(BOOST_PP_TUPLE_ELEM(5, 0, state), BOOST_PP_TUPLE_ELEM(5, 1, state), BOOST_PP_TUPLE_ELEM(5, 2, state), BOOST_PP_TUPLE_ELEM(5, 3, state), BOOST_PP_TUPLE_ELEM(5, 4, state))
# endif
#
# define BOOST_PP_ARRAY_REPLACE_O_I(n, i, elem, res, arr) (BOOST_PP_INC(n), i, elem, BOOST_PP_ARRAY_PUSH_BACK(res, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_ELEM(n, arr), elem)), arr)
#
# endif

/* replace.hpp
716/nM1pMJpOeTfzTLcvPM/gWjgIe1P8INxOGaN6/KGt74de07cBVs1ycxDW6xrbujV6HZhfIzWJM/5P8F6aONm01l+A+CLO9gMfA81hokwD4h7Wv57LkmX7Erhowr0jO8N+6u4JEtWg4UE66ErL+XXM6lZZ1bAUyhn1QqO8rSkvmu10hXAspFNqg/iNyk0qpStxImdNvlw7JboJ/CP1sfHOe+bwwLEkl7F6tYp515IoUj9VovR0QWiBHuSYbsrR7+3RLupPutekm2AckncZp+Q/PM1lYKxABuzv8xGQqMqpIoG5Gm7zBLGnuFpip1DqgISoiQYaz5nrFI6LBlrYPZSRafUleuCOj1EtsqeQBjyrxOqxkM24ZZl7T8FxHfxFywEIAx8FqmAGc24Dm4wS0ZcNx3YgWWnPaNZme1k7yngyuWxflTcskmtXeIbzoewVL3Fb/l6UFhaGduTkdoJN0k0zm0PWNwWB/GKmSdwoCCKZAVBqzffUWAB2p2ioUYNbeggXAUUe6SGzNzMPAgpp1jYVS+MzaXZlB6T4v8cLxywSs4bYYVvtSvdWXm8ZSn1+LPfHGYlklZ+HSmdUXmZ2ZfDKCHOUSUDSv9r+gbZSTavOvg5qAHZIdfl7rPCPsipDF8kGuEd5oknvfr8lf+uQHG9eYoSz2pxK61Y2nNr4N8W/vmwb/6zunX6j9GPbWAj/YVf2xhC733T7sN1j
*/