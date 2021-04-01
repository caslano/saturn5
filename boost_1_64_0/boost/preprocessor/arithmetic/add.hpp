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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ADD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD(x, y) BOOST_PP_ADD_I(x, y)
#    define BOOST_PP_ADD_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# define BOOST_PP_ADD_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I xy
# else
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_ADD_O_I(x, y) (BOOST_PP_INC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_ADD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_ADD_D_I(d, x, y)
#    define BOOST_PP_ADD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# endif

/* add.hpp
9mki6aerw8gTD1naWDDQJ1iwEGnXjCRceXIda25tr/thzYQlTYhChRTSB9SFwe76brVKr5qpOYt7puZy5dZNRJCJx65mYz81TfL1GqQVb7HwKajRkV8V8WSgQN6FJyJTWId5G9SrrstwQ/onbeOMQgLq0BYK4+ID4NbIHs4qsYmrjIiifJIBVJPMssWRygzP7b3J6bkUwLBvOB3VsjwrWwx3ydMJG3XkRH8FsQHoK0L5Wbdv/LUZ4ZXd9AswsaG5T7kPjCh9htS7c85ej5S4bSpY9PxBN1npZYzQSNtiB56tRDBBSuRtbGoAJX4Dypg4HN4RN/F4SAYWBIE9wXPV3DkqFILdw4SitHajN7/NGcxrS5eHDVfGB/v4B4sSoRBxSEBTPdl27ooM4kkUshT6W+QBrygtcp7JVh/i1BJvZEs/fCsds3t+QZOjZnJatOhlwgdoHITWJeY1AoPWOyQ9JaZj/DHrtNm27fOFmx4nhjpFlr97xMKlH4hpZSjnt9zOZVcYLt6R9zD6oeAS5shqMX8SpLt+2ycwD4cmREyHSQPqbNfuTa5iMOcUzg==
*/