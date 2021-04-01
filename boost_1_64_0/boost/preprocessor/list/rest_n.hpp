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
# ifndef BOOST_PREPROCESSOR_LIST_REST_N_HPP
# define BOOST_PREPROCESSOR_LIST_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LIST_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N(count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# else
#    define BOOST_PP_LIST_REST_N(count, list) BOOST_PP_LIST_REST_N_I(count, list)
#    define BOOST_PP_LIST_REST_N_I(count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_P(d, lc) BOOST_PP_TUPLE_ELEM(2, 1, lc)
# else
#    define BOOST_PP_LIST_REST_N_P(d, lc) BOOST_PP_LIST_REST_N_P_I lc
#    define BOOST_PP_LIST_REST_N_P_I(list, count) count
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_O(d, lc) (BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(2, 0, lc)), BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2, 1, lc)))
# else
#    define BOOST_PP_LIST_REST_N_O(d, lc) BOOST_PP_LIST_REST_N_O_I lc
#    define BOOST_PP_LIST_REST_N_O_I(list, count) (BOOST_PP_LIST_REST(list), BOOST_PP_DEC(count))
# endif
#
# /* BOOST_PP_LIST_REST_N_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_D(d, count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# else
#    define BOOST_PP_LIST_REST_N_D(d, count, list) BOOST_PP_LIST_REST_N_D_I(d, count, list)
#    define BOOST_PP_LIST_REST_N_D_I(d, count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# endif
#
# endif

/* rest_n.hpp
2oMqDPllrDj+m/0QhvV9BF/XPCK3mrQGmTg192GIKfZb5cEjQH9RioWsH4GAbER3ihyv+7lLWOo7qxcSf2JTmFHX6PzuU6P/Zlfv4J9DRLSkHpetQL++t/B8emvR1AJOfR+abMeGSmyyMptElXPUa4noarlYN77HpwjtK2NoTtMDPlZBjffUTBhHviWOcoGwOznKEMI8DzrSSSg/ZZzdhw8Ts+GwWh4PfHBEUXflN4cmvG2Mq0q1B+dv/0h9tDiWkTBmzAfKOjhHw3WqmRAu6iKr7g5a95RF7riR9myf3L8Qmj1u5113RDH5hCRyr5aM3RnShYx+ufJymBam71ammHsTDhGxoyH1qlDOkSiK1isLhnzGHx9SlkzXlnOdbHtl6bveItGNIZnc4m2MpQvRL+1UHtrGwuZF+k7vTtmtARCc8luvN7JJeiYJS9YqF4Vj6H+vjw5v/Ks5ChYZYFcy5Gmyf9n+3NKJDd+jw3Pg/9f2dfU7oQSqAgzLrK06jVEB54xS77e3HFH7/8z534zAO99g/mZP4VVBkraHwoREyZ5zV2RDhBWCQSW5dw==
*/