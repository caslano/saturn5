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
xGcKoALiu6wsPT7SuPS1UI0ccb+gVG+lr0ifaxx84nJzz4tq0mQ1Rrzt4J+XGGXbPQl5H2iAQUaEh0PXcub+97M1ELQTXEX5s7qTcFFYF5/8WW7/EeMqV/gUQp+VLZ0Uafz+8U2ZRBTpYccM2T3cWu5RLiXxr3BMYUR8StMmN18z4SzSwlkX482WKDp6qajO30EzbSKCZngnxtm+6XD6+F4+ie3BfT7rszgWXKZDttPR2metEyct67SZite+QQyAat168LXyFjOEWCoF7tjKAALSBwU+QxESF/+DB/twqsfXgr0tUS4hNhJNs+OjkiGMJgntCNjqvR3tmMrrmYdoY/p+XeFAg1nJKxNPCCtt6BcAjs26sNtf2oM8SvzG4Ra22iDTxhpozTkHm3TQajfQwuZgoP9oEIKYIdrmUzjXb5Eiww0qaD8E/zUP7A64fwVmWo+v3Wt3OeDdY9CT+r6d+UHE7UUlTP53tE9EUJjJez+poFYuW26YjYnVDD/SP8v15jWDa68QgN3mamatF7YFtBREW2xA6PJ03fqU/BG/8xyKKrgodqk5eta0dA==
*/