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
7S7fWFBAKXQaiZZ0kDLB/ho7YaZOtQDytcgHmd2oADXbrkbyq1ANBtD7YSNyDnYflijos8kOmnBTO0qb90dMxW5qVwrSSL61j20C5dhdGdTAkIhgI3V/8ky9WA/Bu0DcYFTx8MIhdldtoFTVtRSqYO8P/OL+X51XbDeJL+JFIqglHAcUrGSPWIyJ5d/fh6Dqx3YoKzKzoiDS79jHjR4RN7MLy5Xa5YDSvIfEhKVs6lmqUhKdZPhbVV503rjoHN9qKfiv8XaEVAVnn+Lx8t4YUGTd555uTykQSWWsvUEhyEEXAsIDSFlhghMvnATFeH/MAQ9j8OO5zgyn6iSyAJuvqtoZmye12gue10Qv/pA7dH8pAhzwYJxrvWvtTqvytPatt/Rp9pqeurKBWHSFzoweK7QTFgqv2wSuNDHZdKxP6PAvPEozI0bWZm2P6jS21X4T1GfdHNiannvk5qibVuKgb12Uz//Ez/TkIYaUfuiIgcXK6yh837jtSMFsi+hIzmw+pUZwOD3Q3uxkNGuSIT+mQNer2A93hJQxd9Qs48hoOMPXpKAzc6ZPvTmSo0+UO/JjTbI9os6CZB3/yMKnCWll+LFxWpgzUXkWdWqPW3j8yvKyNvahkW+6lQ35VnQjK8FvadfLmQptBqLZ//50IN3wUCIn5/wWbKp6azv3x/7R5tiGhaBzVJmt18WgG+C3TlwoTbTwLr3EFq0pklvh
*/