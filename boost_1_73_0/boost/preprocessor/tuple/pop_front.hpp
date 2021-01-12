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
0Ajtlk8xCx5fPvCHXGQ7PsZGFUibrMWKMm7q98TOwch6gslK9U3bX3M05XXf9eWW05H3RIOXqKddMhIM6f7wl2wkOMlgFeKs/XFV1WZzn/rlc9Zmsww+Wei1zahYbxxx+cLf2HrjZIORSMt2v6WiDVWNnfAm6yenSJxscrTNpviGNQN9b7Fv2M/KFnVg9lCU7pOMo3ew0vWX+NjkaLc/qkbV8l9veJ2NqgNMNqHp2x51Cinf
*/