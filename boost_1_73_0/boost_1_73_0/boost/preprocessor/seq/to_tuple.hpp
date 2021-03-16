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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
#
# /* BOOST_PP_SEQ_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_TUPLE(seq) (BOOST_PP_SEQ_ENUM(seq))
# else
#    define BOOST_PP_SEQ_TO_TUPLE(seq) BOOST_PP_SEQ_TO_TUPLE_I(seq)
#    define BOOST_PP_SEQ_TO_TUPLE_I(seq) (BOOST_PP_SEQ_ENUM(seq))
# endif
#
# endif

/* to_tuple.hpp
sdIq7wthryqT37dw3H7F+CahPmyv2gNQ2qv3//Pgv0Kmumf7cFsilNG4nynjD5KxXcj4I0bGDtJrrY8P2/lOK0YVfX1L06ZdFEM/iBi6M9tsAzdny/Ic+Il4frbkK1wdSF1c+JWwv8XossJqg38QFvLN+ORxPeNXkF/cfI338sNcxzpua6lpjfPNcpVt92SbPmhKcpoRNoveUyosgN6XrrtfZjFkQ5PWKKfJ3vnqneVx9ZVqo5WyI+qKJ5yg3jw=
*/