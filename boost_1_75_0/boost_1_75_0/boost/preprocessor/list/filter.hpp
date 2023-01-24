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
# ifndef BOOST_PREPROCESSOR_LIST_FILTER_HPP
# define BOOST_PREPROCESSOR_LIST_FILTER_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FILTER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER(pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_FILTER(pred, data, list) BOOST_PP_LIST_FILTER_I(pred, data, list)
#    define BOOST_PP_LIST_FILTER_I(pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER_O(d, pdr, elem) BOOST_PP_LIST_FILTER_O_D(d, BOOST_PP_TUPLE_ELEM(3, 0, pdr), BOOST_PP_TUPLE_ELEM(3, 1, pdr), BOOST_PP_TUPLE_ELEM(3, 2, pdr), elem)
# else
#    define BOOST_PP_LIST_FILTER_O(d, pdr, elem) BOOST_PP_LIST_FILTER_O_I(d, BOOST_PP_TUPLE_REM_3 pdr, elem)
#    define BOOST_PP_LIST_FILTER_O_I(d, im, elem) BOOST_PP_LIST_FILTER_O_D(d, im, elem)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_LIST_FILTER_O_D(d, pred, data, res, elem) (pred, data, BOOST_PP_IF(pred(d, data, elem), (elem, res), res))
# else
#    define BOOST_PP_LIST_FILTER_O_D(d, pred, data, res, elem) (pred, data, BOOST_PP_IF(pred##(d, data, elem), (elem, res), res))
# endif
#
# /* BOOST_PP_LIST_FILTER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FILTER_D(d, pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_FILTER_D(d, pred, data, list) BOOST_PP_LIST_FILTER_D_I(d, pred, data, list)
#    define BOOST_PP_LIST_FILTER_D_I(d, pred, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_FILTER_O, (pred, data, BOOST_PP_NIL), list))
# endif
#
# endif

/* filter.hpp
VuI0lSV5mE1+drFMpMpOOgvlyHLNJwbcvTWWJ8tf+RuQjjzkC+3iz7eYBVob0Vj2/WknTTTbx6mdXn5gFiQjFRtRdYmjMQlNi1ke22ttkD1EIJAUrUvueg5XaUGpwgDYlJMv081HyqAxtkXYVj6q4Tr8zde1nS9060BZ9fpzd3nBYhOdsyIhEvUOp3rW7ea+5mWbE67daNrdUUNSnNKy6eHSbDOawPmcsgyYTeWkJGo1bRaYz3cP1nBCc3RmIAbXFgI3igqg7z+3DjG9ijPMtuHu8+JSO/29XTfK0bygEYAkEThAuEiRvgcpzxNPl8oKBA27jaoxbnSLXW1V8/sDEAeC36XUgyRyGmkUgxBHhp+h5TuTfSZ3Ue3cYsI7YJThPObOdoEUwmNI7aeVU67qa2a0UHrofRQ5uszCC3z8KS4iM4kllC3aLXK3xqYczQXbm/Krtz4hfyPdSXN8KPMX7J7xVygT7Hr80T7QwbJouFsqvoXyrlEm2BdTdIXwVnSFKFF0Bc/519wXekt8rP/Xwjk+EUZZ/jK4UXSFK0obWHuq6u081aLNC3xWASpfQQr10jhvLZi5c3ggSqFD3pYGI48hiLcey4pf5hR58FUIKe2ZE37tVlJLvNGYSIZLV6mq394FFrIeZ4ZFWa1zHDbJRSrc3mYf1T/FZ8uXslpGm4yTKZQTfzSceY6LzWSfKB6x73p/WCp6aJbhYrGE
*/