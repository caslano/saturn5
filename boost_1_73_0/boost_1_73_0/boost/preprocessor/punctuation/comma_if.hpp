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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
#
# /* BOOST_PP_COMMA_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_COMMA_IF_I(cond)
#    define BOOST_PP_COMMA_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# endif
#
# endif

/* comma_if.hpp
UC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsvbaNqKBAAA7wkAADMACQAAAAAAAQAAAAAAHt0PAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRlRQX1NTTF9DQ0MuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ1rVt+pQMAAJgHAAA0AAkAAAAAAAEAAAAAAALiDwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUF9VU0VfRVBSVC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhfPE1g6BAAA3QgAADQACQAAAAAAAQAAAAAAAuYPAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRlRQX1VTRV9FUFNWLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSLEKeBgIEAAB4CAAANAAJAAAAAAABAAAAAACX6g8AY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9GVFBfVVNFX1BSRVQuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIAOiDLOQQAAGwJAAA5AAkAAAAAAAEAAAAAAPTuDwBjdXJsLW1h
*/