# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2016.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT(state) \
    BOOST_PP_TUPLE_ELEM(2, 0, state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state) \
    BOOST_PP_TUPLE_ELEM(2, 1, state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_PRED(d,state) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state) \
/**/
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_OP(d,state) \
    ( \
    BOOST_PP_CAT(BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT(state),), \
    BOOST_PP_DEC(BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_SIZE(state)) \
    ) \
/**/
#
# /* BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC */
#
# define BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC(result,seqsize) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_STATE_RESULT \
        ( \
        BOOST_PP_WHILE \
            ( \
            BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_PRED, \
            BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC_OP, \
            (result,seqsize) \
            ) \
        ) \
/**/
# endif // BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#
# endif // BOOST_PREPROCESSOR_SEQ_DETAIL_TO_LIST_MSVC_HPP

/* to_list_msvc.hpp
L2wC+8HesL9OBxwEL4GDYQkcCi+DyfBamAKXwFR4O0yDFfBC+BBMh4/DDLgZjoCvwYvgW8Z9H7wEHoCjoapDfwerw7GwDtTuTWEObAUnwC5wIuwLJ8OhcIrOL1gA8+FUuBAWwpthEVwLp8HnYQncAkt1vsEyuAcegfvhdJ1vcAY8DGdCT12lZsMa8FIYBy+DbeDlsCMsh93hPNgHXgkHwqvgSDgfToM36PKEN8Kr4U06X+HN8C54C3wE3gqfhbfB1+Ey+Da8A+6Gd8Lv4HJ4BK6Ax+HdMDqC+y/YEN4Lm8H7dPrgStgLPgAT4EMwHT4Mx8NH4CS4Wpc7fAzeAB+Hd8An4L3wGfgofBauh+t1+uAG+BncqtMFN0FvJP2YTgd8GZ4HtX9/+CpMM/s5cBssgH+G0+HrOh3wbbgI7tT1Dr4Pn4IfwNfgR/BL+DH8Be6FIVE8L8AouA+eAz+HPeEXupzgl3A43A+z4NewEH4DL4UH4M3wL/q48Fv4JDwIN8BD8FX4Hfwz/B6+AX+Au+BhnR/wR3gIHoGh9bgfgxHwVxgNf4Ox8K/wTKhCSR/0wotgNVgOq8NnYE24CdaGu2EdeADWhb/ACNgsmn4LngMbwHTYEI6HjWAJbAwvg3HwPtgEroXNYd363HfBONgWtoPtdLpgBzgadoK5sBssg/HwCtgDLoI94QrYB94PL4CrYV/4NOyvzwMOgFvhQPgOXBjC9RkugPvhdfAnuAjWjPHvx8LrYRs4BfaESYRPhENgNkyGi+EwuAymwAqYps8XpsMH4ZO6PsOn4BPwDfgMfFOXM/Rg9wYMgTvhufBL2F7nu4nvJ3ghDGngj7c6vAi2hJmwMxwDL4BjdTphFkyF42AGzIZZMAdOhJPgFJgPi+EUOB3mwQVwAlwIL4ZLYRG8Exbr/IbT4GOwRJcrLNX5Dcvgdjhd5zecAffCmfAvcBb8Gc6Gvli+T8M68FLYCM6FzeFlsAu8XJ8PvAKmwHI4Es6Dk+FV0FuN6+Yg6g7KRAvQBnQANR1MWaH5qAJtQrvQYRSWSP1EHVAiGodmoUVoJdqAdqL9SCVxD4a6oEQ0GpWhBWg5Wot2oAPIO4R4UReUjHJRGVqAKtA6tBMdQN6h2KIOaCAah2ahJWg12oR2oUMoLJnzQfEoAxWgcrQMrUFb0G50DEUPo02hZFSA5qNlaA3agvYjbwr3C6gXGofmoiVoHdqNjqGmqZwvKkaL0Eq0Ae1Bh1B4GmlHGagMLUPr0B50DEVfSD6g0agcVaA1aAfah46i2OHYoNGoDC1AK9FatAUdQtHpnDcajYrRIrQcbUC7kTcDGxSPRqP56EG0Ce1B3hGcKxqIxqFyVKGp19mEO9Ex1PQi+hCUieaiJWgN2on2oWMobiTxoFy0AFWgTWgHOoqiM+nfUDxKQ5NQOapAG9BudAgt0e9/L6acUAYqQAvQMrQGbUK7kXcUx0R9USaahMpRBdqMdqPDKPoS8hFlomK0BFWgTWgXOobiRlNeKBNNQnPRUrQSbUY70WEUNoZ0oURUgJagCrRBU79vgGos+YUS0Tg0Hy1Ha9FmtBsdQ3FZpB3logXoQbQO7USHUNg48gslo3FoEVqLNqPd6AAKz6b8UDxKRKPRXLQIrUFb0C60H6nx1CkUjzJRMVqG1qItaD+KyOH8UF+UhsrQIrQG7UCHUUQu+YnS0Cy0DK1DW9AudAiF55EulIgyUTmqQGvzsEFHUfgEjoXS0CS0CK1E29F+dAytDSXNEykblIgmoUVoJdqE9qGwSdigdqgvSkOz0DK0Ae1CR1FcPm0apaFxqBwtQSvRZrQHqcnEg/qi0agcrUTb0T4UNoUyQYmoAJWjlWg=
*/