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
# ifndef BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/remove.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/comparison/greater.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REMOVE */
#
# define BOOST_PP_TUPLE_REMOVE(tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple),1), \
        BOOST_PP_TUPLE_REMOVE_EXEC, \
        BOOST_PP_TUPLE_REMOVE_RETURN \
        ) \
    (tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_EXEC(tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_RETURN(tuple, i) tuple
#
# /* BOOST_PP_TUPLE_REMOVE_D */
#
# define BOOST_PP_TUPLE_REMOVE_D(d, tuple, i) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_GREATER_D(d, BOOST_PP_TUPLE_SIZE(tuple), 1), \
        BOOST_PP_TUPLE_REMOVE_D_EXEC, \
        BOOST_PP_TUPLE_REMOVE_D_RETURN \
        ) \
    (d, tuple, i) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_EXEC(d, tuple, i) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REMOVE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i)) \
/**/
#
# define BOOST_PP_TUPLE_REMOVE_D_RETURN(d, tuple, i) tuple
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REMOVE_HPP

/* remove.hpp
LopXY4iYT7X+Jp7N/DrYSRTazD1V+EGo0yFz8BDj1tHFt/eoo2kSOgsEx6aKejYTEDIkMxrMpowICL3r4NzDvPVcy3twdArzMfpOv/XAqCoYXRx79+NopgM44DqiWLfRLOiZK+etfK7vYVbonqnS4qE0VJZ5riMcaDTk53S0um7seDJ9ce9+8mfU/aITwKXA3/XZ1wa3W8GH4m/XhVbgurFnU+cCDtrya1vyYljB3A1RmDP0/gnxeHb24Ph+2J+3tU3IX5cP9/qFJNsoZ3GdjQ4bYIV653un4Vk8gWSf7etFCXunbXPzM4gNArx+SsOx9LdlvLd/cAtDdLhPBlO2s3y+/tmjVzsNqZsnP3IffZfvGCa4x6NHYemsWi3nzd5cYjzM0VY3b3yqZaKvs6kMLW/y5Jpr4nHjO9M4nQnd1zhUKZ5vLUmV8VYgnKwrcrEVzmplow+rJqyZx7tAu/q7sd7tzsdvonpxPHWsScc2bbJpYYG1qsrRDvPnXdHzgEYTbwnvfGMIMGcKmJk5B/SqG6ifaIlCvsgzNvVlQpWOUbBwQF3UbdmITFhZA+SQBWz6rAMHuCvMXFWfVUNl8/80QZMeNhpK7RUGWxtjeZrYlqZDP6066NeWNCLW+17O14n4Xrwuqyr5PWSyZai6bm0d8yq9HoUsTvwm9bsPg3tfe37AFPF8uxIbhDttDcmFTbY7bx119xbHgV6E1Tke
*/