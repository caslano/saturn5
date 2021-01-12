# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
# define BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/insert.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_INSERT */
#
# define BOOST_PP_TUPLE_INSERT(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_INSERT_D */
#
# define BOOST_PP_TUPLE_INSERT_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_INSERT_HPP

/* insert.hpp
D9Apexijp9hdyAQH3/pVfO/dVrqN8WWYfGLz0hV8aw7bs57xdTP5xN6oK/gm3LPhXcZ3iMkntl62+fIp353Feev6s4Yj81G6g24thWMp26qfHv2BdfRDZbaIZrsuC8dQtidu7b3vFGQ7zGAzt6U2S6b6bm3nDPuTfbfDJa5mZ9plMeUb9+bdu3NYrzP4yJ7abhlHUc6lnX/+fCpyHmFwyjt226VUML665t12xpgpGIUgYH98
*/