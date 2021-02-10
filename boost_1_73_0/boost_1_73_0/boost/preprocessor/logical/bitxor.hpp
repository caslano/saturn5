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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITXOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_I(x, y)
# else
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_OO((x, y))
#    define BOOST_PP_BITXOR_OO(par) BOOST_PP_BITXOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ ## x ## y
# else
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ID(BOOST_PP_BITXOR_ ## x ## y)
#    define BOOST_PP_BITXOR_ID(id) id
# endif
#
# define BOOST_PP_BITXOR_00 0
# define BOOST_PP_BITXOR_01 1
# define BOOST_PP_BITXOR_10 1
# define BOOST_PP_BITXOR_11 0
#
# endif

/* bitxor.hpp
L2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NPT0tJRVNFU1NJT04uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIE0TIUCwUAAGYLAAA2AAkAAAAAAAEAAAAAAOMgDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NPUFlQT1NURklFTERTLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSlsAM/sIDAAD7BwAALAAJAAAAAAABAAAAAABLJg8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DUkxGLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMCR0k70FAAAxDAAALwAJAAAAAAABAAAAAABgKg8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DUkxGSUxFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSwCIy/GkEAADCCQAALQAJAAAAAAABAAAAAABzMA8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DVVJMVS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvKjJO1VBwAACBEAADUACQAAAAAA
*/