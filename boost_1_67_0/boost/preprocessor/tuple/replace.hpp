# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/replace.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REPLACE */
#
# define BOOST_PP_TUPLE_REPLACE(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_REPLACE_D */
#
# define BOOST_PP_TUPLE_REPLACE_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP

/* replace.hpp
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
*/