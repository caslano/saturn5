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
AAAAmTwdAGN1cmwtbWFzdGVyL2xpYi9saWJjdXJsLnBsaXN0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtgn9SyZAwAAhggAABoACQAAAAAAAQAAAAAAEz4dAGN1cmwtbWFzdGVyL2xpYi9saWJjdXJsLnJjVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlA7R81kAAAAggAAAB8ACQAAAAAAAQAAAAAA7UEdAGN1cmwtbWFzdGVyL2xpYi9saWJjdXJsLnZlcnMuaW5VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSx7jV/6AEAADzDAAAFwAJAAAAAAABAAAAAACXQh0AY3VybC1tYXN0ZXIvbGliL2xsaXN0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSox5corkCAABRBwAAFwAJAAAAAAABAAAAAAB1Rx0AY3VybC1tYXN0ZXIvbGliL2xsaXN0LmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSCRHoYK4CAAB9BQAAHgAJAAAAAAABAAAAAABsSh0AY3VybC1tYXN0ZXIvbGliL21ha2VmaWxlLmFtaWdhVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrcmfkpxAwAAOgcAABsACQAAAAAAAQAA
*/