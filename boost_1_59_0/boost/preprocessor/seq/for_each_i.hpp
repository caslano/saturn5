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
# ifndef BOOST_PREPROCESSOR_SEQ_FOR_EACH_I_HPP
# define BOOST_PREPROCESSOR_SEQ_FOR_EACH_I_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/seq/seq.hpp>
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/detail/is_empty.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SEQ_FOR_EACH_I */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK(macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH_I(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_I(macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_I_I(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK(macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK_EXEC(macro, data, seq) BOOST_PP_FOR((macro, data, seq, 0, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_I_P, BOOST_PP_SEQ_FOR_EACH_I_O, BOOST_PP_SEQ_FOR_EACH_I_M)
#    define BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK_EMPTY(macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK(macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK_EXEC, \
            BOOST_PP_SEQ_FOR_EACH_I_DETAIL_CHECK_EMPTY \
            ) \
        (macro, data, seq) \
/**/
#
# define BOOST_PP_SEQ_FOR_EACH_I_P(r, x) BOOST_PP_TUPLE_ELEM(5, 4, x)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_I_O(r, x) BOOST_PP_SEQ_FOR_EACH_I_O_I x
# else
#    define BOOST_PP_SEQ_FOR_EACH_I_O(r, x) BOOST_PP_SEQ_FOR_EACH_I_O_I(BOOST_PP_TUPLE_ELEM(5, 0, x), BOOST_PP_TUPLE_ELEM(5, 1, x), BOOST_PP_TUPLE_ELEM(5, 2, x), BOOST_PP_TUPLE_ELEM(5, 3, x), BOOST_PP_TUPLE_ELEM(5, 4, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_I_O_I(macro, data, seq, i, sz) \
    BOOST_PP_SEQ_FOR_EACH_I_O_I_DEC(macro, data, seq, i, BOOST_PP_DEC(sz)) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_I_O_I_DEC(macro, data, seq, i, sz) \
    ( \
    macro, \
    data, \
    BOOST_PP_IF \
        ( \
        sz, \
        BOOST_PP_SEQ_FOR_EACH_I_O_I_TAIL, \
        BOOST_PP_SEQ_FOR_EACH_I_O_I_NIL \
        ) \
    (seq), \
    BOOST_PP_INC(i), \
    sz \
    ) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_I_O_I_TAIL(seq) BOOST_PP_SEQ_TAIL(seq)
# define BOOST_PP_SEQ_FOR_EACH_I_O_I_NIL(seq) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_I_M(r, x) BOOST_PP_SEQ_FOR_EACH_I_M_IM(r, BOOST_PP_TUPLE_REM_5 x)
#    define BOOST_PP_SEQ_FOR_EACH_I_M_IM(r, im) BOOST_PP_SEQ_FOR_EACH_I_M_I(r, im)
# else
#    define BOOST_PP_SEQ_FOR_EACH_I_M(r, x) BOOST_PP_SEQ_FOR_EACH_I_M_I(r, BOOST_PP_TUPLE_ELEM(5, 0, x), BOOST_PP_TUPLE_ELEM(5, 1, x), BOOST_PP_TUPLE_ELEM(5, 2, x), BOOST_PP_TUPLE_ELEM(5, 3, x), BOOST_PP_TUPLE_ELEM(5, 4, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_I_M_I(r, macro, data, seq, i, sz) macro(r, data, i, BOOST_PP_SEQ_HEAD(seq))
#
# /* BOOST_PP_SEQ_FOR_EACH_I_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH_I_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK(r, macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH_I_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_R_I(r, macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_I_R_I(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK(r, macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK_EXEC(r, macro, data, seq) BOOST_PP_FOR_ ## r((macro, data, seq, 0, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_I_P, BOOST_PP_SEQ_FOR_EACH_I_O, BOOST_PP_SEQ_FOR_EACH_I_M)
#    define BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK_EMPTY(r, macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK(r, macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK_EXEC, \
            BOOST_PP_SEQ_FOR_EACH_I_R_DETAIL_CHECK_EMPTY \
            ) \
        (r, macro, data, seq) \
/**/
#
# endif

/* for_each_i.hpp
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
*/