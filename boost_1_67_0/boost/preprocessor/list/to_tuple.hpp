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
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
*/