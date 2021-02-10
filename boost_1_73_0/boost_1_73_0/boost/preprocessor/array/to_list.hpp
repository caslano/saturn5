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
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_ARRAY_TO_LIST */
#
#    define BOOST_PP_ARRAY_TO_LIST(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_LIST_DO, \
            BOOST_PP_ARRAY_TO_LIST_EMPTY \
            ) \
        (array) \
/**/
#
#    define BOOST_PP_ARRAY_TO_LIST_EMPTY(array) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(BOOST_PP_TUPLE_TO_LIST, array)
#    define BOOST_PP_ARRAY_TO_LIST_I(m, args) BOOST_PP_ARRAY_TO_LIST_II(m, args)
#    define BOOST_PP_ARRAY_TO_LIST_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(array)
#    define BOOST_PP_ARRAY_TO_LIST_I(array) BOOST_PP_TUPLE_TO_LIST ## array
# else
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_TUPLE_TO_LIST array
# endif
#
# endif

/* to_list.hpp
dGltZW91dC1tcy5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUs2wdHz+AAAAlAEAADAACQAAAAAAAQAAAAAAs5AFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2hhcHJveHktcHJvdG9jb2wuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJN8m9G1wAAAEEBAAAkAAkAAAAAAAEAAAAAAAiSBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9oZWFkLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSlG6AXusDAADTBwAAJgAJAAAAAAABAAAAAAAqkwUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaGVhZGVyLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS016/+9EAAACUAQAAJAAJAAAAAAABAAAAAABilwUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaGVscC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUm39hWzsAAAATQEAACoACQAAAAAAAQAAAAAAfpgFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2hvc3RwdWJtZDUuZFVUBQAB
*/