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
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_LESS_EQUAL(y, x)
# else
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_GREATER_EQUAL_I(x, y)
#    define BOOST_PP_GREATER_EQUAL_I(x, y) BOOST_PP_LESS_EQUAL(y, x)
# endif
#
# /* BOOST_PP_GREATER_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# else
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_GREATER_EQUAL_D_I(d, x, y)
#    define BOOST_PP_GREATER_EQUAL_D_I(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# endif
#
# endif

/* greater_equal.hpp
WkA5p5RI/xLQsRid/vVGTPReE2WYtk+CwfHyuMXsfSTEldHycuvuvwtgeXOPwGbVbgAC4KYBFRSSl/n/5NFsoxY5u6WafYW/5pdKc6B3eGW9DDo1+6ePMrXReEiuT0/YaVOhquULUNPjVUnRTgcPDLn0E9ZnMMycLmLhmB1M3ygX4mqhEWqu2QHhvj7s1ajfIMqzHKgGRuTPwKRyGnlzCI12Nbe1jQel79NjulzpCF0OOQVIcrFslbbbFbhucJP48vxLDWiWC/ePGgU81r7Utej0pEgGodY9+l4bxir9Iezhi+gF0rI+QejcuylywaG7sS+X1Kd5f+o5ZyJCzcBFrj2b9yCotXa2rtunYcy8e5KD5112ZSdcgtC1jY633oGDIPt/XSjBzQPkOcFKlnV2kM7NOCgHoD9u60ELDLggPXC4Evc2I18Ht9BZ9N2LgtYMQg1Qs9MEmlLdqDslOcahpgM12SjUEyMpZYseGq4578j1ZSp9z4cSEeiBEtinFbrRcQeznD+8go+RwJ47cTihnpw6WtibR9zAQGyOQ6YSaB9CVAGjVROgS6AZ7A==
*/