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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_II array
#    define BOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif

/* size.hpp
cy9mdHAtc3NsLWNjYy5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtAur2PLAAAAQwEAAC8ACQAAAAAAAQAAAAAApH0FAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2Z0cC1zc2wtY29udHJvbC5kVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUsf01ENdDAAANioAACQACQAAAAAAAQAAAO2BxX4FAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2dlbi5wbFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIOrBYGaQEAAH4CAAAjAAkAAAAAAAEAAAAAAG2LBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9nZXQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLOq94OBwEAAIwBAAAnAAkAAAAAAAEAAAAAACCNBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9nbG9ib2ZmLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSpMG/O94BAABCAwAAOQAJAAAAAAABAAAAAAB1jgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaGFwcHktZXllYmFsbHMt
*/