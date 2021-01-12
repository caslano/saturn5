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
# ifndef BOOST_PREPROCESSOR_SEQ_INSERT_HPP
# define BOOST_PREPROCESSOR_SEQ_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_INSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# else
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_INSERT_I(seq, i, elem)
#    define BOOST_PP_SEQ_INSERT_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# endif
#
# endif

/* insert.hpp
s4vo+srrmtQczNzH3Bz2PuvUqthq8t5Sk3djxunyFfrxC/P7tTnIApvSuiv90pN+mqdxdxM2s7Am3oy3d/w0eRZ7tnAAc08VPXtX8a1ThizowudY7lC7TJ9PoO+Y99ZW4BfglwzJrIrd36WJG8vOfvuZU0ayK/6L5XO9kKlLbCxtDWMcUP6szuxa7cQettAknvlzF+MrPYI9IMr0Po6MfLBbA3nXLOOoh5cu308hr5VCv1Af
*/