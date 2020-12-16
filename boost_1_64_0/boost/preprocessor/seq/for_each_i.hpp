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
O5oR6pkrURdflHTl7qigFqF+dHBe11gUEHhNdyiklpmTUccJJo6Qd3xHMiMXIBojQqZjM/Ctn4oJmayzJfxl8ywu3vTC8WasgiQkfSnDplSwXqw6dTJ7NWnR3Re6k9mk6QnWTwkKGik7KqcH54aYBwF+jk4/lOI7LnehoNy/0BAM7EjL+c/NpLnOpJp8ZBwunna9LpgRe+HSAIbZ60WuGGhankGFTvGdc/odEVaErHx8omDWNy9wXPsztI1wJewPJ71XLKEsdUOZlDclZxEN68mnOrbyfqyrXsO2X0Fltj67V50vZjN1QrUjFr4RIQoxl5M8HCJ9++xlpk1Dtn1eoYFhKIMn9wjxOmZ/DBZdNkwDW1s1oiTb1LMh0AZxQ8VWsBTFVOYaQ4sXzu3yzjTQfBMhTvBrqNMD1ehJFr5/logaTXOK3jSP+ccQdnrFZQxnRnX3zMLFD1kGPILuZviRyJxNZDq4d6jil9nlRBQdYz32irjL4vGusy01eBD0QQub6r5ex6EwfGC57pZU1NGoFs5rk1BrGPTCj2PBTeMxmdffFY0wtWeurSR8qwk/wNcfUfoRCQhAV5Eh6HyZUekw9uwoJ/paemU2nErvgq3Janh2GnNXkyv/YomRMIe3tIRTwCvqa0JeKWWU/XmENxIX4exeY5QW95aGVTpImAOCybfZYtkCnvZnm/hof8AeEkh35ztXBHkGOdoYq74ZBx+DtFbKebtk98WCIf54glEja+9o5mipFaMkTiymyP4RGQivg0BvKfvonQvuj/y1Awaw3LUqnO9InjbCC3XiYOyyE+KFfLziHwW/Evk7I7w/DSKCk8kbLSAkxiD+0QOiccr9YBWQQGc7721CVXoe2xNRmrK/1ge1w2N/uBC0j5wrI71oR26kaS4X8VVkoSjCpAm89mzzfqwkg709kzZ5NOGdJowLW4uxqlL6VeU655+a4woCeAP86QwLAYbBquaS0rx09DRgPA2sM+tiYJmbQHf+HTGw/AMxsKhzMbC2BzGwEVRxMKh5oJ8mACuAJIARgDdAEkA5wHeAFQCwBaAnPYAggAKANoAZgDcA+N/0P/ae/Nc5uzILv/pVZwL31/iL/sbNgD8CgH3yZ4DGnPqVL4ILaG0A+Kd8ADNA+wNAPPcvBnQbAMJTf+mBqd/7nUL/k36nK3Oif+p5+hbACGAN8O+AMRPgjz1LjwB/BYA2D/xbAIIAKgDvAMIAcgCaASYA9gCQgNdHDyAD8MceqVEAjoAOBogDyAQoBvibefmXeet/7OMN97T97cbf56d6b/zqUx0GaNZFETDE53ne+L2v9fM81QP+u83v++E5H/joL/bDALB9DeA5x+Vo4/d5hP0P8k8zp3/9vubN3/OGn/NQJwC9BvDcp3th8/c+8c+vH2oLqDkAmOc+1oAWBHiuA0lAOwI814kHoDNf/8pDTQN8PsDz/BQDegHgeT62tn6fP6S/yWNHfvJwT3mvKP/k9YKdADUBIAkQBlAP0AZwBEB6CtQpQBTAwOnv2/aAkeYMqB2AYIB/MG9/NU9ph8CxCPA8T/WAXgB47ie9Bui4MGCennPuAA939Cu/Bw3Qf+wHDfcX/aDpj37VCSegr3h/5cTKHP3eDx3xyRsB/o91ifQXdekN3Ib8fLwB+o91ivIXdZpz9CtvpRzQK1e/+oV//6MHQH/yW4C+A3jO74E7/n2/vPi1X/7UDxzzyb8EtmsAHusv+otrvBEFw356vOjxX+dEvz3+vd897lO/exfAywAe7+n+cYAvB8B/8s2A/mM/bIJfucp/28//r85vM8f/z9P4X++X/Zf7m7dP5D/q//98/fvb8+LR8+u7+L0+IZ/qc+Di9/o=
*/