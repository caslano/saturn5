# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
#
# /* BOOST_PP_ARRAY_TO_TUPLE */
#
#    define BOOST_PP_ARRAY_TO_TUPLE(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA, \
            BOOST_PP_ARRAY_TO_TUPLE_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_TUPLE_EMPTY(array)
#
# endif

/* to_tuple.hpp
AAAACAAtZ0pS6wH+3KMAAADpAAAAJQAJAAAAAAABAAAAAADhnwUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaHR0cDIuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIZu4wokgEAAKsCAAAlAAkAAAAAAAEAAAAAANCgBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9odHRwMy5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq7H4XcJAQAAiwEAADUACQAAAAAAAQAAAAAArqIFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2lnbm9yZS1jb250ZW50LWxlbmd0aC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUns7o2rMAAAAZAEAACcACQAAAAAAAQAAAAAAE6QFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2luY2x1ZGUuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLaF+e/OQEAACcCAAAoAAkAAAAAAAEAAAAAAC2lBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9pbnNlY3VyZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuSK
*/