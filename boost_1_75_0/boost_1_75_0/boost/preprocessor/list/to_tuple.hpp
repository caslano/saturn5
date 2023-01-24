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
zkYxH4usQ3LN2B8VihrdW3FalF6DXWWu3xsS/zwzpcxYiKOcQN5B+vCB6/Y4j9vw6EPnUfd0zY6G1pga5Wv6aTfnxbLFbgnxDrk4q2+aQl4a/muPOqNuZ1BZ6lfjHcLVe5RHWNaD4E6rdfLVZGl9rE1jhbLF3bv7EoW22WX9Z+1SF8LkE9mJUbhMdXYEzEoePzPP1SHIXh2/pbHsZ9zKIA7hEJMCGGKiZ6W3XevQS1xyp6v3JwfPENIdZhfMqNF2PXbon6sJXTErm5jA0Q5sd5YDM338MXfatF99c9OLHKIuzHZza6zd/HCNq+x6LYJps9kO6pfsQIIDVOMxiTCZI3ItWJXNXWAeduddEWNz6FvwDIDl/ivkexa8LhPupwbrn6GyKJVXOzuV81Ev00qdVDuqiv5hUc2kYVALIGBbMYhiVkupUrzS+l3BToUKkuh9o+s9Z1B0CicXjsR1lPyw8WdBiv3Qvlbshw4T3vPDV8/cy/OPzKTFPSDHuCcCiI2gotNXvLkQ0a3F+EARsKhgVNbeCTroMAfMCvGC8B4foRXeoh7NXcc0Iocajta2q/MTkvPNhLvFZTmv8+cA/8y1p69XT26RJnKyzpnqMNlq0dXPmgHE336xir3f23xnyLSRjmo4gvZh0ehM3stCQ04k4NR5JsNScYk91uVTYz7GAdHMJ2cGvboALj2ZtEqc8z/NUakyMg06iTwfte2i
*/