# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/pop_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_POP_BACK */
#
# define BOOST_PP_TUPLE_POP_BACK(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_BACK_EXEC, \
        BOOST_PP_TUPLE_POP_BACK_RETURN \
        ) \
    (tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_EXEC(tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_RETURN(tuple) tuple
#
# /* BOOST_PP_TUPLE_POP_BACK_Z */
#
# define BOOST_PP_TUPLE_POP_BACK_Z(z, tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_BACK_Z_EXEC, \
        BOOST_PP_TUPLE_POP_BACK_Z_RETURN \
        ) \
    (z, tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_Z_EXEC(z, tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_BACK_Z(z, BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_BACK_Z_RETURN(z, tuple) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_POP_BACK_HPP

/* pop_back.hpp
SwECAAAKAAAACAAtZ0pSI2wmtioHAAAzEwAAGwAJAAAAAAABAAAAAABt4RoAY3VybC1tYXN0ZXIvbGliL2hvc3RjaGVjay5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUieU3TlDAgAA/gQAABsACQAAAAAAAQAAAAAA2egaAGN1cmwtbWFzdGVyL2xpYi9ob3N0Y2hlY2suaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL71X2p6yYAALuDAAAYAAkAAAAAAAEAAAAAAF7rGgBjdXJsLW1hc3Rlci9saWIvaG9zdGlwLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTpwTIBoLAAD9IAAAGAAJAAAAAAABAAAAAACIEhsAY3VybC1tYXN0ZXIvbGliL2hvc3RpcC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoJIy7TvDgAA0icAABkACQAAAAAAAQAAAAAA4R0bAGN1cmwtbWFzdGVyL2xpYi9ob3N0aXA0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSI6SsB8UIAACHFQAAGQAJAAAAAAABAAAAAAAQLRsAY3VybC1tYXN0ZXIvbGliL2hvc3RpcDYuY1VUBQABtkgkYFBLAQIAAAoAAAAI
*/