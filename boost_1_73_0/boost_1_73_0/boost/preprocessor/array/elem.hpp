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
# ifndef BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_ELEM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# else
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_ARRAY_ELEM_I(i, array)
#    define BOOST_PP_ARRAY_ELEM_I(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# endif
#
# endif

/* elem.hpp
CQAAAAAAAQAAAAAAhiIFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2NpcGhlcnMuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlInUWANmgAAAM4AAAAuAAkAAAAAAAEAAAAAAKwjBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb21wcmVzc2VkLXNzaC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUj6Uj+bNAAAARAEAACoACQAAAAAAAQAAAAAAmyQFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2NvbXByZXNzZWQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLZ98k5ogQAAJcJAAAmAAkAAAAAAAEAAAAAALklBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb25maWcuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLRh8pDBgEAALYBAAAvAAkAAAAAAAEAAAAAAKgqBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb25uZWN0LXRpbWVvdXQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ0N9+bAQIAAMMDAAAqAAkAAAAA
*/