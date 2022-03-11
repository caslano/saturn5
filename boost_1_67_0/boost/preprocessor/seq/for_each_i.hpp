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