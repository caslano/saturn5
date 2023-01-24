# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# else
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_SEQ_FIRST_N_I(n, seq)
#    define BOOST_PP_SEQ_FIRST_N_I(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# endif
#
# endif

/* first_n.hpp
KjAae2tT0SEHgICf9nqDxrxq+pDrVpr89/CuJtK+3vQ5sBYJeB/pA9y0Bk/3THkt3OQ1tqMo2IRK1FYXoCCcniqv7qfORA4cPJq8SI9DGku2kAD7cWQQzt84u2jxhwYhwf/jbOb/zdnq7i627tYeHv/eF/fVHvKS8GhGw8Kilxx8TaVHS/gnvE+db+jZaWcdijnx0SgIT0k6LX5yzopUGlvTBSu76sQqHA+yDfLbJzYYd/I7r/hS1dG38Qu9FxpQmRVScSwVUnAEFnENqbzY7fDFtfby8t45MDHqa8Ll73vGHyY3/LLSeaHcHlPjGy5iEvB9edXJgLDwYrwk6XPrK3tFnexpVi3ukE/Jm2NWPDpeB4tHFYq9KJR1q05fh4xElw+0Qvz6Arf4zFDr/hCi0SuyjyglmjPlVVythdTarMiZS8ZkzX2mF2WYAwYC3vJO5BsFTDT2rhkasZ5gantoCXxVOiutBFODpITaumXm9zUBA+VUW6ldguZkAR8LI6t+aKA8TL99Hhv+Y/kqxnaSKkQJL7kWDgq0lH9RVGt2eeaxLf10kSvl8DUmFVndh2F1uan3ZCMde2e1W/QAkdk3xepaTwHvDoJipc6NqXIuarK+40fRS5xTEG9LEKSlAmPAZ/uDxYm7EuYPwuvcAztIivOGkuQcTDGW7kox+Al4SV0gX3885LlL90pc2ARBFXl6VzGADA/v7EqluhNU
*/