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
# ifndef BOOST_PREPROCESSOR_SEQ_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_SEQ_FOR_EACH_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
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
# /* BOOST_PP_SEQ_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_D(macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_D(macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC(macro, data, seq) BOOST_PP_FOR((macro, data, seq, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_P, BOOST_PP_SEQ_FOR_EACH_O, BOOST_PP_SEQ_FOR_EACH_M)
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY(macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK(macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC, \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY \
            ) \
        (macro, data, seq) \
/**/
#
# define BOOST_PP_SEQ_FOR_EACH_P(r, x) BOOST_PP_TUPLE_ELEM(4, 3, x)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_O(r, x) BOOST_PP_SEQ_FOR_EACH_O_I x
# else
#    define BOOST_PP_SEQ_FOR_EACH_O(r, x) BOOST_PP_SEQ_FOR_EACH_O_I(BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_O_I(macro, data, seq, sz) \
    BOOST_PP_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, BOOST_PP_DEC(sz)) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_O_I_DEC(macro, data, seq, sz) \
    ( \
    macro, \
    data, \
    BOOST_PP_IF \
        ( \
        sz, \
        BOOST_PP_SEQ_FOR_EACH_O_I_TAIL, \
        BOOST_PP_SEQ_FOR_EACH_O_I_NIL \
        ) \
    (seq), \
    sz \
    ) \
/**/
# define BOOST_PP_SEQ_FOR_EACH_O_I_TAIL(seq) BOOST_PP_SEQ_TAIL(seq)
# define BOOST_PP_SEQ_FOR_EACH_O_I_NIL(seq) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SEQ_FOR_EACH_M(r, x) BOOST_PP_SEQ_FOR_EACH_M_IM(r, BOOST_PP_TUPLE_REM_4 x)
#    define BOOST_PP_SEQ_FOR_EACH_M_IM(r, im) BOOST_PP_SEQ_FOR_EACH_M_I(r, im)
# else
#    define BOOST_PP_SEQ_FOR_EACH_M(r, x) BOOST_PP_SEQ_FOR_EACH_M_I(r, BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define BOOST_PP_SEQ_FOR_EACH_M_I(r, macro, data, seq, sz) macro(r, data, BOOST_PP_SEQ_HEAD(seq))
#
# /* BOOST_PP_SEQ_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FOR_EACH_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
# else
#    define BOOST_PP_SEQ_FOR_EACH_R(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_R_I(r, macro, data, seq)
#    define BOOST_PP_SEQ_FOR_EACH_R_I(r, macro, data, seq) BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq)
# endif
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R(r, macro, data, seq) BOOST_PP_FOR_ ## r((macro, data, seq, BOOST_PP_SEQ_SIZE(seq)), BOOST_PP_SEQ_FOR_EACH_P, BOOST_PP_SEQ_FOR_EACH_O, BOOST_PP_SEQ_FOR_EACH_M)
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R(r, macro, data, seq)
#
#    define BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_R(r, macro, data, seq) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq), \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EXEC_R, \
            BOOST_PP_SEQ_FOR_EACH_DETAIL_CHECK_EMPTY_R \
            ) \
        (r, macro, data, seq) \
/**/
#
# endif

/* for_each.hpp
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
*/