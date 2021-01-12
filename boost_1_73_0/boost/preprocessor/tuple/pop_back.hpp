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
KaCMXy5f+UY2Mh4pGIXeYLNOVT2i+adBG1mP6Gnh87TZLp2ilT44qOMD1kqPktiijoxmqtKt//uPrax0vQw+ocXYZVOV7oVvl29npTs6xiakHvttRcHX79kpXzG+3iafUJJs8yl6Q/3hHXr/O8bkE0KVA4xFlPHtN6s3DUTGPgajRQez3WZUPfC35d9tYj3wWJNTyGxdMaqt3f/9m6xW+xp8sohnu4SKOfe1D0o3sDn3uBij
*/