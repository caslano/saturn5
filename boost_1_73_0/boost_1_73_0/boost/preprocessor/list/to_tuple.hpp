# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_LIST_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/enum.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_LIST_TO_TUPLE */
#
# define BOOST_PP_LIST_TO_TUPLE(list) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_LIST_IS_NIL(list), \
        BOOST_PP_LIST_TO_TUPLE_EMPTY, \
        BOOST_PP_LIST_TO_TUPLE_DO \
        ) \
    (list) \
/**/
# define BOOST_PP_LIST_TO_TUPLE_EMPTY(list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TO_TUPLE_DO(list) (BOOST_PP_LIST_ENUM(list))
# else
#    define BOOST_PP_LIST_TO_TUPLE_DO(list) BOOST_PP_LIST_TO_TUPLE_I(list)
#    define BOOST_PP_LIST_TO_TUPLE_I(list) (BOOST_PP_LIST_ENUM(list))
# endif
#
# /* BOOST_PP_LIST_TO_TUPLE_R */
#
# define BOOST_PP_LIST_TO_TUPLE_R(r, list) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_LIST_IS_NIL(list), \
        BOOST_PP_LIST_TO_TUPLE_R_EMPTY, \
        BOOST_PP_LIST_TO_TUPLE_R_DO \
        ) \
    (r, list) \
/**/
# define BOOST_PP_LIST_TO_TUPLE_R_EMPTY(r,list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TO_TUPLE_R_DO(r, list) (BOOST_PP_LIST_ENUM_R(r, list))
# else
#    define BOOST_PP_LIST_TO_TUPLE_R_DO(r, list) BOOST_PP_LIST_TO_TUPLE_R_I(r, list)
#    define BOOST_PP_LIST_TO_TUPLE_R_I(r, list) (BOOST_PP_LIST_ENUM_R(r, list))
# endif
#
# endif

/* to_tuple.hpp
CgAAAAgALWdKUlD8FozqBAAAKAsAADQACQAAAAAAAQAAAAAARQYOAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX1RMU19TRVNTSU9OLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS75dHL2AKAADpGAAANAAJAAAAAAABAAAAAACKCw4AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fVExTX1NTTF9QVFIuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI0NKSOJQQAAA8JAAAzAAkAAAAAAAEAAAAAAEUWDgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19UT1RBTF9USU1FLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSrTt7GEwEAAB4CQAANQAJAAAAAAABAAAAAADEGg4AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fVE9UQUxfVElNRV9ULjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSiRpedysEAAATCQAAQgAJAAAAAAABAAAAAABsHw4AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJs
*/