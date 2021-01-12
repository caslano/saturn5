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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitnor.hpp>
#
# /* BOOST_PP_NOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOR(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_NOR(p, q) BOOST_PP_NOR_I(p, q)
#    define BOOST_PP_NOR_I(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* nor.hpp
TqZCjyOhOGIb2YPSHo4iERHE4aOLTLEG1Tk25A2XUiyNo5IByPX20IGeXwmi7aOzmujFiZma9MWZjoNu8Rw8aPdMtOHZWTpcvc9KFwNh6d6CislFAQcyQomgqAPgiEjDRMoQAyLMluSxlWDR1K1gEzooqcXBb2dSOr9BzUPIPFoUDAfFrLnoBC2sQNuWGQyboZS5sitimtH0Qp42zBXgCS2jLhooBT2ecEc8KNHHlLJ8C2Zn
*/