# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
#
# /* BOOST_PP_ARRAY_TO_TUPLE */
#
#    define BOOST_PP_ARRAY_TO_TUPLE(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA, \
            BOOST_PP_ARRAY_TO_TUPLE_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_TUPLE_EMPTY(array)
#
# endif

/* to_tuple.hpp
ZZctizdF9pyQGvR3NcR2mz6x6Nzd1Ab65hW7Qq72zP/vwNdRwb0lPJiSQRujgraALxoOgS/xkW1MtGa/itNprkK3cwMnpeZ/Kr6oRM/a+QQ8zg6X4Sk8zJ7YUQ6Ckjr++uvgPcpRp1fGTJX/HyVBXAFG2ti87j0Bal0BU1EldM1vendavLOgdsa3QoS8KshBUCRJz2INdr2RD0JuaZeFp/B6i7YAuRpiGgOiW0nGw1hUR+uFnxRXyB5+vu+DD/a7+gssMHaHbr2Ftw9RgAcTsIUZ/i9kO316n4+yTeVva9ACr2B9lTj6kb07wLQsyDuesfNuVPK23em6vz36WhYtrmkx75PjSj+BkItXJAszkbAq1Oh9rbAgpitH8HDPbTEl6Ubvpcsyqe+RPS820lk+1ugRuYO4doUP4snt3AjQx4MLZ+rzfeSTNNodxsFTULg4ix4aZqw+cy/hYt2rrR8j/ATmCJQOcyr6jNHG4vE1ZTueHb7tKJ1cizL+bl51tXdLE/NmPuKpBDEF5GgSCKB0eleY0zsjB2XKWB2j8z2y4zdQasRVibBXqkF4fQ==
*/