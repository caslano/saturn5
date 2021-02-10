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
# ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
#
# /* BOOST_PP_AND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_AND(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_AND(p, q) BOOST_PP_AND_I(p, q)
#    define BOOST_PP_AND_I(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* and.hpp
b2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NBUEFUSC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUinKQw7aBAAA3AoAADAACQAAAAAAAQAAAAAAbbUOAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ0VSVElORk8uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJA2PB6SQcAAGURAAA6AAkAAAAAAAEAAAAAAJ66DgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0NIVU5LX0JHTl9GVU5DVElPTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpi+JmDyBAAAQAsAADIACQAAAAAAAQAAAAAASMIOAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ0hVTktfREFUQS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkrnccNnBAAAnQkAADoACQAAAAAAAQAAAAAAk8cOAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ0hVTktfRU5EX0ZVTkNUSU9OLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS
*/