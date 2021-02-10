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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITAND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_I(x, y)
# else
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_OO((x, y))
#    define BOOST_PP_BITAND_OO(par) BOOST_PP_BITAND_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ ## x ## y
# else
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ID(BOOST_PP_BITAND_ ## x ## y)
#    define BOOST_PP_BITAND_ID(res) res
# endif
#
# define BOOST_PP_BITAND_00 0
# define BOOST_PP_BITAND_01 0
# define BOOST_PP_BITAND_10 0
# define BOOST_PP_BITAND_11 1
#
# endif

/* bitand.hpp
lBTu9OwDAAB+CAAANwAJAAAAAAABAAAAAABbzA4AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DTE9TRVNPQ0tFVERBVEEuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLbcJR/fwQAADUKAAA7AAkAAAAAAAEAAAAAAKXQDgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NMT1NFU09DS0VURlVOQ1RJT04uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKThgOigAQAAMUJAAA2AAkAAAAAAAEAAAAAAIbVDgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NPTk5FQ1RUSU1FT1VULjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSzkRV1j8EAABnCQAAOQAJAAAAAAABAAAAAABj2g4AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DT05ORUNUVElNRU9VVF9NUy4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlLlMve1BAAADwoAADQACQAAAAAAAQAAAAAAAt8OAGN1cmwtbWFzdGVyL2RvY3Mv
*/