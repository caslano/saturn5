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
HqJC24kyzGAiC1kRwGYo/ROc+zmNsyg9suTj5LSCBMq0JaYTOT1dePT3dG05SluHjsGRLH40+1yHicXpYLrGvYleDXewppT+xySJZKo+05vxkO7QcqqppHnCZiektTpxUPtnWguCCPDI0qlVpH0SQAaSMegG0Do5GffuMclU6CC44NFmTV2iQH60sFkj4ybv7dToZ7wBaI+Hu//+W6qAfR/+lvHNdeDwp+a3lMlJffryTut2XjvvvcxjjQFnp2cTbC1xJKYL1lY5HNeKew8dPuzEtmtk8ei7u4Z0Z3dkPjnENshcBl/CnewvK0+YJ29QrSYlRecnl077MlGu38/uP3893wDJxfVfZ5nOk6kbp85jZ8c2+gjPHMR/+AyIYgSGF3MuBfBRqFzwkJhNLrrqcuYJ6dzUpXx09fI7okc/pMw1iz3LYyhgwXIgQ221svoZTMXQZ0ROH+jL91zwXfaYC6Nu9RI0uHVILjUgt8e4UMeQkJXOzQjgS0gbU1FSJGTEPIfdF02WUqzJMoa5UmxCSsugW0qrUtiC4BTxELHsE4eggLSdBb0fBJZkysX7gvt8RQFsvKIGYo4lMWPs4RYORet84PBjAWsmcME6IHjeGhu2NMi9T4psasZN3Yb0zMzGHbnDOGFcdndYlz5x3EdIqmMN6EBW5VjaHRU/zuNcibwJyJk56eatv7Vn50tv1FiGC8aSDXnPH6fgY6U1
*/