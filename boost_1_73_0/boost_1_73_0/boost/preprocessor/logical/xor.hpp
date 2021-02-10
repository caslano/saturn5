# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_XOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_XOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitxor.hpp>
#
# /* BOOST_PP_XOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_XOR(p, q) BOOST_PP_BITXOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_XOR(p, q) BOOST_PP_XOR_I(p, q)
#    define BOOST_PP_XOR_I(p, q) BOOST_PP_BITXOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* xor.hpp
tkgkYFBLAQIAAAoAAAAIAC1nSlJW3s8NEQQAALgIAAA1AAkAAAAAAAEAAAAAANSuDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZSRVNIX0NPTk5FQ1QuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIbqoNV9gUAAJAMAAAvAAkAAAAAAAEAAAAAAEGzDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUFBPUlQuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL3eVK3RgQAAIAJAAAyAAkAAAAAAAEAAAAAAI25DwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUFNTTEFVVEguM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLpkJssHwQAAJAIAAAzAAkAAAAAAAEAAAAAACy+DwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUF9BQ0NPVU5ULjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pShsdMnncEAABiCQAAPwAJAAAAAAABAAAAAAClwg8AY3VybC1tYXN0ZXIvZG9jcy9saWJj
*/