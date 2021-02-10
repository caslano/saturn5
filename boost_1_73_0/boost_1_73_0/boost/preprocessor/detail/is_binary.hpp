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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_BINARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# else
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_IS_BINARY_I(x)
#    define BOOST_PP_IS_BINARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# endif
#
# define BOOST_PP_IS_BINARY_CHECK(a, b) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_BINARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_binary.hpp
c7wAAAAVAQAANgAJAAAAAAABAAAAAAAzeQYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvc3NsLXJldm9rZS1iZXN0LWVmZm9ydC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgqcA3MdAQAAsQEAACMACQAAAAAAAQAAAAAATHoGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NzbC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqplUdHrAAAAVgEAACUACQAAAAAAAQAAAAAAs3sGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NzbHYyLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSNSRNhuwAAABWAQAAJQAJAAAAAAABAAAAAADqfAYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvc3NsdjMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ3jlpztgAAABwBAAAmAAkAAAAAAAEAAAAAACJ+BgBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9zdGRlcnIuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLOrTa3oQAAAOgAAAAtAAkAAAAA
*/