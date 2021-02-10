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
# ifndef BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/reverse.hpp>
#
# /* BOOST_PP_ARRAY_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REVERSE(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# else
#    define BOOST_PP_ARRAY_REVERSE(array) BOOST_PP_ARRAY_REVERSE_I(array)
#    define BOOST_PP_ARRAY_REVERSE_I(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# endif
#
# endif

/* reverse.hpp
dHMvZnRwLXBhc3YuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKY1wRBvQIAABIFAAAoAAkAAAAAAAEAAAAAAIB1BQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9mdHAtcG9ydC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUubMFpfNAAAAGgEAACgACQAAAAAAAQAAAAAAjHgFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2Z0cC1wcmV0LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSgP7DqScBAADcAQAAMAAJAAAAAAABAAAAAACoeQUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZnRwLXNraXAtcGFzdi1pcC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpLq09rcAAAAeQEAADAACQAAAAAAAQAAAAAAJnsFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2Z0cC1zc2wtY2NjLW1vZGUuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLRNpPa+QAAAHIBAAArAAkAAAAAAAEAAAAAAFl8BQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0
*/