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
# ifndef BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_SUBSEQ */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# else
#    define BOOST_PP_SEQ_SUBSEQ(seq, i, len) BOOST_PP_SEQ_SUBSEQ_I(seq, i, len)
#    define BOOST_PP_SEQ_SUBSEQ_I(seq, i, len) BOOST_PP_SEQ_FIRST_N(len, BOOST_PP_SEQ_REST_N(i, seq))
# endif
#
# endif

/* subseq.hpp
LXZlcnNpb25zVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUlG7B+P6BAAAGAsAACMACQAAAAAAAQAAAO2B664UAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9zeW1ib2xzLnBsVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjLVWbjgCAAARBMAAB8ACQAAAAAAAQAAAAAAL7QUAGN1cmwtbWFzdGVyL2RvY3MvbWstY2EtYnVuZGxlLjFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSLbgyeaIJAADoKQAAJAAJAAAAAAABAAAAAABVvRQAY3VybC1tYXN0ZXIvZG9jcy9vcHRpb25zLWluLXZlcnNpb25zVVQFAAG2SCRgUEsBAgAACgAAAAAALWdKUgAAAAAAAAAAAAAAABQACQAAAAAAAAAQAAAAQscUAGN1cmwtbWFzdGVyL2luY2x1ZGUvVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUm0XiEcDAgAAOwQAAB8ACQAAAAAAAQAAAAAAfccUAGN1cmwtbWFzdGVyL2luY2x1ZGUvTWFrZWZpbGUuYW1VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSITb2fBcBAADnAQAAHQAJAAAAAAABAAAAAADGyRQA
*/