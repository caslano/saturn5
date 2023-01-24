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
# ifndef BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
# define BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH_I */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_FOR_EACH_I_P_D x
#    define BOOST_PP_LIST_FOR_EACH_I_P_D(m, d, l, i) BOOST_PP_LIST_IS_CONS(l)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(4, 2, x))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) BOOST_PP_LIST_FOR_EACH_I_O_D x
#    define BOOST_PP_LIST_FOR_EACH_I_O_D(m, d, l, i) (m, d, BOOST_PP_LIST_REST(l), BOOST_PP_INC(i))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) (BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(4, 2, x)), BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(4, 3, x)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_D(r, BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_I(r, BOOST_PP_TUPLE_REM_4 x)
#    define BOOST_PP_LIST_FOR_EACH_I_M_I(r, x_e) BOOST_PP_LIST_FOR_EACH_I_M_D(r, x_e)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_I_M_D(r, m, d, l, i) m(r, d, i, BOOST_PP_LIST_FIRST(l))
#
# /* BOOST_PP_LIST_FOR_EACH_I_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# endif

/* for_each_i.hpp
8ol4bu7Y/QqiGxp/Drgf9zyKyQRcD/voGuWP2uvVmCS5xiacEWWzmVa2zDk7uQdKGuwlRMxM65Fpcm7b0X0AxjLDz8PtuwCEyWNEZZ/QF+YaSNId5aDO7noUe0Pe7aKTBedyUhSfJsxB9QKZzbmQaHx8Zt8Po5mnOX8uUJt+PG3684P7xCFbjS6ji0efaI/I2UXqyWH37zqJSa5z8YNqk61G1Swx+YTm6zNfGxT/jVyd/cSsgfz8z1N1jfcSzMR7bl2Oo/012DlXjYV0KuQrGmRiSvxHxJml5EOaBXexnZekmKu3TbWkz3i74dikISSizr935k9K/5SajkW9l10XFz3k9mfPJo/AN//o4ur36GoQlKHT6LOfaILejR+VvUliC2M+EZC6Sow2zxKZl3XL9epNAcmIZ/76CUWT6F1QTTA88pbEAAZZ/MMsrKnR6jOKxoXA3/7RXzw/zYj6K5VVs+KqWDuK3k0zNTDMtv9YelnM1prRVcgC6RU70/K7pBmLHjG4kWsUa1Xt6qC7Pi14/8HTK4ZmaISojan9gNDPxlebNfSKM8jsMH6QOrW3I4uZJukbUzBKvOTZxo8J34lIa903I7U7fWPHm/hTnlpRkFrFBEGRwvmPHA/tFV0T1fnAzno3A0cVQcN4VS0EPUp3z4rZH4Za6Nox3by1YecBEfIrezoxgqLbqiZN2ZkpyqAuVOLszwXn/viFSg8H
*/