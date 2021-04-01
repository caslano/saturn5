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
JtR/R3yji0rYnHj8MhXDf2FR8y8wriu2/pXRbJLWyZnovqghE5YMTml2+VaCj72OH4Skey2HZIU8j/XgejOTEDdZqOhhLF42RDuqqaxCIU53rhKvh9dPf04KNc+1a1wpowdnRpAMFT/VTShc7tUcNW4AlV2fhUB3hA9NeLGejFYUlIaODQm12GiQJA0Q33xBfMDnadBlTHtoxTtPTCXLTmTA5CtEtg56HG0iAbWlf3BSGFK4dJudKPCHqwjyt8MZsrIVG2kjojfa3i+KHH9S2nBaxBQi2yKpMVq9w90nBbyVOyfik9qGtXV/ILfOGkbuR/HoX/sYOeHflf+TZuZ0TrMzJeffvAWo9uIFmoQsE/qU/z342AsoJ0vUQN1pWqAw5eOY7CIRlWu9gAGD/e+Av7QDR6Orq3euwzp0JutTQRIknvK9dr19NbZ/PwBi23U4LNr4IookclvLateqrNrqm6b/YHPZ/VQtynxttk3Aq7z0aQ4hVWxVZPAltFFjqQuVwWiudhqcpUKGr8Og2sdphXGPbG1rjvBJwb88j7o5HOc3TUJXGAL1fG3/Qw==
*/