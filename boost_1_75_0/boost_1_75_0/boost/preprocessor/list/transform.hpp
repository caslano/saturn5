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
# ifndef BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_TRANSFORM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM(op, data, list) BOOST_PP_LIST_TRANSFORM_I(op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_I(op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, BOOST_PP_TUPLE_ELEM(3, 0, odr), BOOST_PP_TUPLE_ELEM(3, 1, odr), BOOST_PP_TUPLE_ELEM(3, 2, odr), elem)
# else
#    define BOOST_PP_LIST_TRANSFORM_O(d, odr, elem) BOOST_PP_LIST_TRANSFORM_O_I(d, BOOST_PP_TUPLE_REM_3 odr, elem)
#    define BOOST_PP_LIST_TRANSFORM_O_I(d, im, elem) BOOST_PP_LIST_TRANSFORM_O_D(d, im, elem)
# endif
#
# define BOOST_PP_LIST_TRANSFORM_O_D(d, op, data, res, elem) (op, data, (op(d, data, elem), res))
#
# /* BOOST_PP_LIST_TRANSFORM_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# else
#    define BOOST_PP_LIST_TRANSFORM_D(d, op, data, list) BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list)
#    define BOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list) BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_TRANSFORM_O, (op, data, BOOST_PP_NIL), list))
# endif
#
# endif

/* transform.hpp
MMCPBnt+TKhVXQYW/Zmz+mObpPgGqVZaTNiXO+IQ2fcFVZxN4qnRtqp1l/6II4wpfuJVpBGX3iWrf2Ki4S3L9CRzrtbnn5IKMyRcagT/8mVE0eol7y1OxFSlSo8sM+3TjtfHZiAkGWUz28RoxLjO9LrwEFZQDzxMMYMtzq7uL+7/iGrdxum6XjGeeq9jCeFJTmDqI6952NaoAywZxmqwras5VB2unnFI9zJiezMg0ssb8v341rke1NXFjvi0EqOxTzfgUSy3yaApmRZnWqdN+YfmtKCtFBgQ1k7A9WQQfYFr99t214fjTjKLcFKf/h4nK2OiV/H4SDClMkA8EjpPyO86bJTKnNemxsZWyhuvenb3AeJHrTwvq6R0cWkomhPw4NeBuRQI0hdwsIaAMnRXZT7gP90HDPh920IXlj/D2uVQ80IvoPEouPmu5vX+QXKLthXDw+sjwRlsN1jFS8ILwwPo/KPyNSwirDhIovI1MkZyS06YcrHvt53k8FVbAmsl9HAlH//qjml60sDT/U+enFcbuHEH3yiaSNWesPwbnMfi6acjG/iSSBvN+gt5cKLiXP84U0czNnKCJ/LYM/n3N8wukZKRcR2kK8vYfGUJG/Uif70IpCdIIFN+RuKwoikvZtuauRNw4TIdnua3gX4Aee3BwvSFt7X+6MwW2LU9Dq7JQq639BrwkDktOn8h1OT23xcYPLjx8cb//qY0
*/