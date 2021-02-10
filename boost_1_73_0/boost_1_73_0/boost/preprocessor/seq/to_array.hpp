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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_TO_ARRAY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_ARRAY(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# else
#    define BOOST_PP_SEQ_TO_ARRAY(seq) BOOST_PP_SEQ_TO_ARRAY_I(seq)
#    define BOOST_PP_SEQ_TO_ARRAY_I(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# endif
#
# endif

/* to_array.hpp
Y3VybC1tYXN0ZXIvaW5jbHVkZS9SRUFETUUubWRVVAUAAbZIJGBQSwECAAAKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAGQAJAAAAAAAAABAAAAAhyxQAY3VybC1tYXN0ZXIvaW5jbHVkZS9jdXJsL1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ0WqYmHAAAACEAAAAjAAkAAAAAAAEAAAAAAGHLFABjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK8MjShxgIAALEFAAAkAAkAAAAAAAEAAAAAAMfLFABjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvTWFrZWZpbGUuYW1VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSNhUoq9x8AABQzgEAHwAJAAAAAAABAAAAAADYzhQAY3VybC1tYXN0ZXIvaW5jbHVkZS9jdXJsL2N1cmwuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJd9v4ORQUAAOELAAAiAAkAAAAAAAEAAAAAAPpLFQBjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvY3VybHZlci5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnFn
*/