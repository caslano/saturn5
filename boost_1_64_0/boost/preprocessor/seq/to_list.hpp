# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
#
# include <boost/preprocessor/punctuation/comma.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
# include <boost/preprocessor/seq/detail/binary_transform.hpp>
#
# /* BOOST_PP_SEQ_TO_LIST */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/detail/to_list_msvc.hpp>
# define BOOST_PP_SEQ_TO_LIST(seq) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC \
        ( \
        BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq)), \
        BOOST_PP_SEQ_SIZE(seq) \
        ) \
/**/
# else
# define BOOST_PP_SEQ_TO_LIST(seq) BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq))
# endif
# define BOOST_PP_SEQ_TO_LIST_I(bseq) BOOST_PP_SEQ_TO_LIST_A bseq BOOST_PP_NIL BOOST_PP_SEQ_TO_LIST_B bseq
# define BOOST_PP_SEQ_TO_LIST_A(m, e) m(BOOST_PP_LPAREN() e BOOST_PP_COMMA() BOOST_PP_SEQ_TO_LIST_A_ID)
# define BOOST_PP_SEQ_TO_LIST_A_ID() BOOST_PP_SEQ_TO_LIST_A
# define BOOST_PP_SEQ_TO_LIST_B(m, e) m(BOOST_PP_RPAREN() BOOST_PP_SEQ_TO_LIST_B_ID)
# define BOOST_PP_SEQ_TO_LIST_B_ID() BOOST_PP_SEQ_TO_LIST_B
#
# endif

/* to_list.hpp
3S7254aDzm/Bd7U5n3eB251Y9eo0IrE4/l0hK0q0U66vvHRt7SCTCWnJSPAqs5M6IuvrB3l2kGAiTTYEMy4jNTKZ4k2ztJJ0XO7GPc1jGucHMvayndgI9iG71CcISt/ebxHsLFz09YEGKpw1moVECm60ApfbqNrmIAFwSOYOz/94iY8OL6x/evTdSl2WZBlRRy8nJ1s2+N2ht3Jv8Va7AEor/VlIxhqoDLamz1AP8mWvTO49ErP+I0XdjhEsc+dsVsCfCup+xGH+iQWBI7XFrFaGqBLBX51VSyfxVST/lPPSMhwoM3/gw5qvhpr9ySlv6dQVeRSfZhncVGQMRnPIfaSIGnfrCpGWfcgSeEinsgnYMk9EnvXPIHLDm9+NQtFsAkimpvFk3lqt9v18iGY10GWM55NbLjkWm4EEG8oA5qtbTSQ9Zn2onqOF88KQAj1HyyTDRlKQvc6TJxs9u5IQJ1udB1mWm+vgTU5ZWDysRYfTtJO+SkDQR6qqjwXEkYMk6WG+yJn7tzG6aibLrKgmT0KSn0uLjMw7VqATWUsDYSRLNC8Ys+uLk+d6Yw==
*/