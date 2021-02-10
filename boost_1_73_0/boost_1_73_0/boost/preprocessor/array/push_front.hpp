# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_FRONT_I(size, data, elem) (BOOST_PP_INC(size), (elem BOOST_PP_COMMA_IF(size) BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data)))
#
# endif

/* push_front.hpp
bWRsaW5lLW9wdHMvZHVtcC1oZWFkZXIuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJv6lairQAAAPgAAAAoAAkAAAAAAAEAAAAAAO9WBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9lZ2QtZmlsZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUv9oaHnBAAAAIAEAACYACQAAAAAAAQAAAAAA61cFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2VuZ2luZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsi6oLWeAQAAxwIAACwACQAAAAAAAQAAAAAA+VgFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2V0YWctY29tcGFyZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhj0e0J4AQAAeAIAACkACQAAAAAAAQAAAAAA6loFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2V0YWctc2F2ZS5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUptFqUQWAQAAxAEAADEACQAAAAAAAQAAAAAAslwFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRz
*/