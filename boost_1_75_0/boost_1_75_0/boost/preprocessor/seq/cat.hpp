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
/Ou194pU67soPfQMVQcMY3JQ0q2F1b0fldMV20sCIiLou9sDnm+XlP00iDjIbFo4xgHQrgUj3M0Dzie4DsWGHn0Hbqs2Fx2r6yx7lzFJjaTIKP3pxFDzSPsgW9yS2rt08MJiJEXogoj5ozq4imHjpzbTDd8uLInCVlkWKteb1ETjvnukSujKql+8aHMbo6jxIUWykKIArb4MdZPtp0f+27wFLqoNJs1U7LM7CFOSZnsZIdrCQVuFsnJEoi6OqO/kgOIAn8b7CpnkW7j9Yak2DJWpge52Nxfi7harxzzKvVJ0JGTrqhfuLsZVsXWU/qCJVu4rThKtLCDzs015nEhpwGlPRDJdTzyQDEQTYkpCQE6Q+6uR0UZ+A+gUf0MwFTMRQ6pwzvGnpyD+R/ZU65R6g8llRTG6yuuNL8V/i2LocxpYcNQfXnwzl+niprJi/caouGnEmuq6/ZgMABEW5TIcRFei6kYO7LBxE5Q4/RH920jqwqFFCacA+aVJJDPdm6zhA1kURh9AbgpinfPBo3o8dURU6WDMOqea90e6D3a9bA0GvfBu/Gj6pM4HYnmLsYgP3t5ET90/mdvlDlhMzkxE0gJfUgWvFwOP1Sk4DJ+H4SplQBbttak7VDpGLxZXunJg8JPCOlMWs1fuBVs5MEwkH0ZkENYBdMXxAtd9KevMywzrsF1imnvpF/t0KfF+DvRbIx/GSEt0bLLzJd/i
*/