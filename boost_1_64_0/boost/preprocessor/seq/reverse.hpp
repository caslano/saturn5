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
# ifndef BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
# define BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
#
# /* BOOST_PP_SEQ_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_REVERSE_I(seq)
#    define BOOST_PP_SEQ_REVERSE_I(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# define BOOST_PP_SEQ_REVERSE_O(s, state, elem) (elem) state
#
# /* BOOST_PP_SEQ_REVERSE_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_REVERSE_S_I(s, seq)
#    define BOOST_PP_SEQ_REVERSE_S_I(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# endif

/* reverse.hpp
tZ2FP7vQLfEuRCsyme/gbNl2ho3q7Q+tgK0syVkmKHsjuII5bqOuuatMRi3DZ0B/vhuDxFHl/ZWwWe1tkgdFZunjpiqEPw98f59pUTcX0UHm0otfqTF7YfHy7gbfbfBK20H57J2vmyWBWUa0DNV4AaDVrl1d3Am7Ab5w2ezWJ8F9pKzn8gL9rXAjzSWggejf5PKebJMHkoJpRuOxwyPP38ZfYu5oR62ozx7R2aqVKrhTmy223dBRhxs8wBS4BQAm+JzhOgYgAcKkneLv13LiXUkWIvEkHcN0I1MWPdwvEdgchEX2KY95mdTfvOoHew8xFDMHEsflnDSX5ABRDbGQ95jwdUV24Qj1hHj+4/kgBnPD7NOBs3dj6yPgdG7VSy5JpEcUFEVBmcTJgdxbIqISTsliCzdQtQSYRW0YJNKBu+T2NaPdMr5uRfvpkRA+EOtL6l7QEf2/DkkLclfjyrLl6O6RRRmFC/XDaCBtd8+qmjAWMdJF0D6Iij5I3FJoHzl7LtaR8TMIaWSb7NFbMEfF5WetYmLa75peaQKkwNgo1BzDQ+IrE13MYWaoHQ==
*/