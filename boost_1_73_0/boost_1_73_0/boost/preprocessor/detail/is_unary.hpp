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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_UNARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# else
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_IS_UNARY_I(x)
#    define BOOST_PP_IS_UNARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# endif
#
# define BOOST_PP_IS_UNARY_CHECK(a) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_UNARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_unary.hpp
ve4AAABeAQAALAAJAAAAAAABAAAAAAB3hAYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGZ0cC1ibGtzaXplLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS+segztEAAAA/AQAALwAJAAAAAAABAAAAAAC4hQYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGZ0cC1uby1vcHRpb25zLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSHhVhp6gBAADwAgAAKQAJAAAAAAABAAAAAADfhgYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGltZS1jb25kLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSOcWs704BAABVAgAAJwAJAAAAAAABAAAAAADXiAYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzLW1heC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq45uXRTAQAAXwIAAC0ACQAAAAAAAQAAAAAAc4oGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3RsczEzLWNpcGhlcnMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKgctPi
*/