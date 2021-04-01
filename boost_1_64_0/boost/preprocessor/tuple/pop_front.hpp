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
V/J8LJ5apRdCbCGHw6rj5cxRO5yAmH7TG9eymwN/jhEIgyH0lXqNbc6eOLYuAESSpE8btBwSuQWTGHG0n450SU+3K8s+HymZSJpQBDDp9VzhiCjtZ6xudcN+YrCxepKXPfTIGGDWgw/036d6khUvcHF8QfD2ysRQR8le0N6vnTuOVa0urZ/K3ZHUhySt0Aa0QYkX4bxUIcc1NGS/r8ADYlBDKH8boo0IFAeKKwSAF3Em1PgF3ZQTUbjRcZxpOUvpdsyPySdTQXeRfpkNVsTpjA8/DLxBUDCUzzofOROT5dYPVF97atTqOND+XIYNEOQ6+3DtbgJYAQK+Aen+vgCsojgZh8ucVQXB4agit62aHHtGcq4s4rWQcQCgQ5pTtYL3kkQa+aVAhCIw7gPPydsMRYlhuO/Ozxb45tht/t4lDqnArwEotSlI9/bO54JtL1sG1pJYyczGlApbl+xp05hlNxt5H0sI++tw1mHQHvGddKxkYaChv4eQhrhQNWO1sWs3ASupk2vfWAt8orcyU8xxqfYRGcn9YEdT+NVBTaVgI1dWDWc8A14hodUFsQ==
*/