# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Paul Mensonides (2011) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
#
# include <boost/preprocessor/list/for_each.hpp>
#
# /* BOOST_PP_LIST_TO_SEQ */
#
# define BOOST_PP_LIST_TO_SEQ(list) \
    BOOST_PP_LIST_FOR_EACH(BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
# define BOOST_PP_LIST_TO_SEQ_MACRO(r, data, elem) (elem)
#
# /* BOOST_PP_LIST_TO_SEQ_R */
#
# define BOOST_PP_LIST_TO_SEQ_R(r, list) \
    BOOST_PP_LIST_FOR_EACH_R(r, BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
#
# endif /* BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP */

/* to_seq.hpp
HN35F4J261InKaC3fnlHX7AcIOh62l5KeejsfwVSmkDIiR93YKB3ct+eCkakGF0NPLz0/NaCsudQFTbhuosiAiEoWWVsb63r35OD9t8PowItHOwjsFsC1g9wLHsMUa0hJOXCVz//khbfBpqcRriSakPOaRpTgSPT2QSocL/wZJKVb6Sm4iW6ZNwrMW0Zzf+mZg2ojPtuDes2JIne4/iYNbjkOE5seHQ3px7MHuqUAz211kZD1o31RW/BILxH1s1ULNeLcLrEDaPY8yHLYOGBpB8cYEcQ95enZRaj5XKfKa0AckFh5EfgPfAEenVo3wXnnz4xdx3zJQggnXDgdU6jrDNGLGzjgnVyNxSoHF1owhjqUNhWPcUX1oqajl8V5TBGBOFaSicQQRxkodamEkyoLN/nhQ2yucwBPKmoJR2Y2Zadi457oQMH5bWIjCiDLrMvlcZrojAbnyU6YsHaDBbVjFPA/2P6U7HYr+IdgnninL4ySz4vlmPod2OcKvRSxwtm3Vb4AYUycw0L//CFppwFBlR22d87JbrkMHqN56T+UUXZ96qkMEqbueUsjw==
*/