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
nM+m+GxldEODGaLGrzSNPtqxQmeiW2ZVxOIpeREN2lXLiwxZPoA2sDWULTnXK+fJjggMzhVIKhTbnjokU31XvVvXeGyazdWCxbCvGwAWyjTgk5XmGFaa9CiPASBW5UShN6AQO5uBa+jSQJ7uwBL3p0pbcbNm96Bzunu5tWsPh2xp1xJni9uP/0VpIj2eP8KTnJCAZ8XYPjjB8KRtahNmfqRJ6ANhjJmbTnPb3O/xvs8a+Ork0Ug57eQ+FBneba0NN+76SpNRJimJAKYu6O24gFaVi+Kr0mPU3cD+1BJSOott7kXXr2LZ5oJtxEgosl209FNZv8NhVeLPLnJs0xsLzwvAbsu2s1SQpLtIhwe3RiFjwosPXr4I0gTnpZ5t6lyqsok+4YMVpWtI4tfNTl4Hb1ISEuz2YHttN1uaOwhBuhRDWzFyk2Zo5VpZbxEA9niB3q6oBb5w/e+RtF0R9bk6z/cHL5RTqeXKezC/fqJFTLnPoG/eb4JthG54Y6CKwFwROiNjOIHVpJj1xEXcK4hLkS0EdFBZzAKULF0aXs0QrRVhfEq10BN3OGwyWQ==
*/