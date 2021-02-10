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
TFZFUl9TVEFSVF9EQVRBLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSx2OFVccEAACWCwAAPwAJAAAAAAABAAAAAABFjxIAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9SRVNPTFZFUl9TVEFSVF9GVU5DVElPTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUigUhka8BAAAcwoAADMACQAAAAAAAQAAAAAAcpQSAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUkVTVU1FX0ZST00uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJmpvjD8AQAABgLAAA5AAkAAAAAAAEAAAAAAIiZEgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JFU1VNRV9GUk9NX0xBUkdFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS9JjFG8QDAAALCAAAOAAJAAAAAAABAAAAAADYnhIAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9SVFNQX0NMSUVOVF9DU0VRLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS+DGa
*/