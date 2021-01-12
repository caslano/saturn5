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
# ifndef BOOST_PREPROCESSOR_SEQ_CAT_HPP
# define BOOST_PREPROCESSOR_SEQ_CAT_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_SEQ_CAT */
#
# define BOOST_PP_SEQ_CAT(seq) \
    BOOST_PP_IF( \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), \
        BOOST_PP_SEQ_CAT_I, \
        BOOST_PP_SEQ_HEAD \
    )(seq) \
    /**/
# define BOOST_PP_SEQ_CAT_I(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_CAT_O, BOOST_PP_SEQ_HEAD(seq), BOOST_PP_SEQ_TAIL(seq))
#
# define BOOST_PP_SEQ_CAT_O(s, st, elem) BOOST_PP_SEQ_CAT_O_I(st, elem)
# define BOOST_PP_SEQ_CAT_O_I(a, b) a ## b
#
# /* BOOST_PP_SEQ_CAT_S */
#
# define BOOST_PP_SEQ_CAT_S(s, seq) \
    BOOST_PP_IF( \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), \
        BOOST_PP_SEQ_CAT_S_I_A, \
        BOOST_PP_SEQ_CAT_S_I_B \
    )(s, seq) \
    /**/
# define BOOST_PP_SEQ_CAT_S_I_A(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_CAT_O, BOOST_PP_SEQ_HEAD(seq), BOOST_PP_SEQ_TAIL(seq))
# define BOOST_PP_SEQ_CAT_S_I_B(s, seq) BOOST_PP_SEQ_HEAD(seq)
#
# endif

/* cat.hpp
qKn47/MNuX1Xl9feworm12QneQa/y68v6w0JO4Zn/KMhO1rpksayZ89NXQ55a9J4jSHdbhiy/poh208a8mWwIW44PAN66aKFa9Jpr/k+Gk0+X0qZU3lH2ffUrbIhGWGsd7tocitek/MsE84sIE5z8mljyLLzhnzUSZOtdw0ZeEmXq5/z7p8phqzcQD1ma7J6jC4N2AmMPIWnOVmXywnMJ4sMuRfPryNuunhs12VycV3uHqa+
*/