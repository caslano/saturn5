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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITNOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_I(x, y)
# else
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_OO((x, y))
#    define BOOST_PP_BITNOR_OO(par) BOOST_PP_BITNOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ ## x ## y
# else
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ID(BOOST_PP_BITNOR_ ## x ## y)
#    define BOOST_PP_BITNOR_ID(id) id
# endif
#
# define BOOST_PP_BITNOR_00 1
# define BOOST_PP_BITNOR_01 0
# define BOOST_PP_BITNOR_10 0
# define BOOST_PP_BITNOR_11 0
#
# endif

/* bitnor.hpp
mf6r3dRlL+cyr7uRMJpEvjhx5KUaZa8O2jJ2WKxzHBKzPy7fa8VGyq6MHXMotP2EB1n3F8GzMLtkO3202EGjXxEdFmzairb7lUD8a4/Eu9Ltkr0RyNlUpsrrMi9OIaLAhN6pTXJzEIrTP9rLB80B/BUlmJhk/ZGkHTCbvvZMjAqw9i1dcbhG7ZJw0/cy6ucuGScj4Ce6CDpJTyrUm4YfIafWGTuMlsfrzExGpE+iGnpVLCU2zVzqzRSMmyhi8pfU1uioDOvOjkUrwTKsSVyMR3lpuZTvqbmZthtX6yW7z3D+NU08uN054jpJmS17/j77OIbyiF12rZBArLqw1NZbNR7nawVCQkazM6TDuSVGut1447IA+a2TlV98bkTIg8EHluEsN0BfLmLv+s6doUZwaDntpCf2tVk0QkE789shH087mt73JLe8FpHJce91U7N0/tGJDzt0Tt+SQzg/+UxkMaVFphAKhrZ9mrK8KN6HKdQC+CDt8I9sayhHZVg4qkUWMDQmADZnddu1PWQpypCaSmgfDmyKsBxKL01+pUlGsghs1983DmiCIbqx4A==
*/