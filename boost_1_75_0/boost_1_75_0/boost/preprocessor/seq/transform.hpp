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
# ifndef BOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_TRANSFORM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TRANSFORM(op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_TRANSFORM(op, data, seq) BOOST_PP_SEQ_TRANSFORM_I(op, data, seq)
#    define BOOST_PP_SEQ_TRANSFORM_I(op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_TRANSFORM_O(s, state, elem) BOOST_PP_SEQ_TRANSFORM_O_IM(s, BOOST_PP_TUPLE_REM_3 state, elem)
#    define BOOST_PP_SEQ_TRANSFORM_O_IM(s, im, elem) BOOST_PP_SEQ_TRANSFORM_O_I(s, im, elem)
# else
#    define BOOST_PP_SEQ_TRANSFORM_O(s, state, elem) BOOST_PP_SEQ_TRANSFORM_O_I(s, BOOST_PP_TUPLE_ELEM(3, 0, state), BOOST_PP_TUPLE_ELEM(3, 1, state), BOOST_PP_TUPLE_ELEM(3, 2, state), elem)
# endif
#
# define BOOST_PP_SEQ_TRANSFORM_O_I(s, op, data, res, elem) (op, data, res (op(s, data, elem)))
#
# /* BOOST_PP_SEQ_TRANSFORM_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define BOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) BOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq)
#    define BOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq) BOOST_PP_SEQ_TAIL(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# endif

/* transform.hpp
0iZoGBx38fGejMGCO+WjPUt/sVAGIQldY+6ZWWlze+7cUWXsuqfmyB2czTXmKtsfvTHm4lPrLNUYfyfK6kEvirfSypXRPpu7CuIh/JPLETLQQHdbhF1hnupEBXgFB/rsMjn2+N+2eG4iNgUgsH0DR9DVdR78VJETdD13D3ieUgE9ce6UHoYC69dn/Nyr7M8rs0Fac55WiPLB4lNyYdk38CtXOc9pw4nqFKkn0gm/lLq0yozKDB3uQy6S6ZvL35UZuNwIpRfHQ9H522TuFjbv4jMGmFock90sD/j3DKNAPyqvPN8Z/PkswAz4g3VP/oXpvSGvYXDUl34yuUHCZ/aPkZYzGpcvDftaALGntgAIT9yOzdPHixeHTodK7OIeT5iIibYbmFF1D3c1G8NxshYqyPLzNKu2Ohk+cJRlqb2WdOC0A8U+T2B0amNmEWukveiA1ZKNU8u4kEpt2xIzF881Q6hBlrX9XjWyx2RN5em5AQQQJIUZPehfroPBQUtysl/M+mjIcFvQUhtN6Zh/objPQVKf4P3y7y7OWAiPoXrrTW83yNrX2jagtPy1W0/hGtc3AjIBJNqSJkenrzIL9o/d0GGI73dDLjdxHw6eO09iajGNsXq7XytyUl+K4so5ohr0wsMzVuq+BzzC5fcU2hlW8FmWMU91viAlI3SibgAEPoyXNX2rly2XbRKb3L1Bq4G7ZY6qR376tQiGCPH0
*/