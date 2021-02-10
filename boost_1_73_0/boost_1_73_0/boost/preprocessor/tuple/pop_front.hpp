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
# ifndef BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/pop_front.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
#
# /* BOOST_PP_TUPLE_POP_FRONT */
#
# define BOOST_PP_TUPLE_POP_FRONT(tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_RETURN \
        ) \
    (tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_EXEC(tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT(BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_RETURN(tuple) tuple
#
# /* BOOST_PP_TUPLE_POP_FRONT_Z */
#
# define BOOST_PP_TUPLE_POP_FRONT_Z(z, tuple) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_POP_FRONT_Z_EXEC, \
        BOOST_PP_TUPLE_POP_FRONT_Z_RETURN \
        ) \
    (z, tuple) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_EXEC(z, tuple) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_POP_FRONT_Z(z, BOOST_PP_TUPLE_TO_ARRAY(tuple))) \
/**/
#
# define BOOST_PP_TUPLE_POP_FRONT_Z_RETURN(z, tuple) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_POP_FRONT_HPP

/* pop_front.hpp
AC1nSlInoMLltwMAAFMLAAAZAAkAAAAAAAEAAAAAABU2GwBjdXJsLW1hc3Rlci9saWIvaG9zdHN5bi5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUv1PyprDEAAANDQAABYACQAAAAAAAQAAAAAADDobAGN1cmwtbWFzdGVyL2xpYi9oc3RzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS+NoQEI8DAAAYCQAAFgAJAAAAAAABAAAAAAAMSxsAY3VybC1tYXN0ZXIvbGliL2hzdHMuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKYoWuC8YYAAJAVAgAWAAkAAAAAAAEAAAAAANhOGwBjdXJsLW1hc3Rlci9saWIvaHR0cC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUva1j1qeDgAA1C4AABYACQAAAAAAAQAAAAAABtYbAGN1cmwtbWFzdGVyL2xpYi9odHRwLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS94N826VIAACyKQEAFwAJAAAAAAABAAAAAADh5BsAY3VybC1tYXN0ZXIvbGliL2h0dHAyLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMzVsZ50EAAB0DQAAFwAJAAAAAAAB
*/