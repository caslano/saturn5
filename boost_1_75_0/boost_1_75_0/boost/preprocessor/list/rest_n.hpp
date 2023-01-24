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
J1601bsZ84h3RA1jHghCTT+B6n+Jjj20vCdejfpxfF9AsqfBO2fJJPz61knmgm2KvDFcjYi25kIgLcwo37NqNvC8htWe0takSWBsskwp73crjCB6VhuWZzyqLYQhMbK2OlUaG91INa6Fkz3U5H99XdJyr7ts4b2FuM5hB7OIxIw0iGTWQRGaio90R2G2ihCPqqD+bIIvglnvTLITIxZLkm9xkXoTBf11Lmf0FH5jdb0QevhkEv7bkIfPedjn/nGxjyKfqPrtLaasteORDzAOV8ywu9vO2xmFC48LvQATe0PhpOM9bw2JvUA4+bgQlInu+m6Q2cWLwuQO1h8x7vd6r7h9b2RyFwhHoTsFTB2+Bmtl+tPffKXbwfAfOBQqnQBq/Ag80mtoeXvj5clw4zddL7maiko67BMDrIyi01rQgCszovXayTllcR4/A3bmjwQMEkbCp0yk2k+uMfCyd6QMefTVCTtKq5eYCCzsitDoOQ6GEh92TMOc5jlsyzpAemCHOxBbQAQsars8qDyo6PrYZ9xrTxYbw9BN8C3vawa+m/1K//GpxAZR0xG0svrkzUWf2qQ7XCEa4JJmuVOgsk3sZNkgc/68ZE0GIK470CrxeNEq6aChWLhdCogyglOPjO6dFDlw3+ehAO+9cE0CY+P3/szsaLm/rLcbWdfj+Sta56195LjC0EU2k3gmv3tudsJgb3GyqZNU7y1uGi2N
*/