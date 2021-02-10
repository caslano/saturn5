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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_MUL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL(x, y) BOOST_PP_MUL_I(x, y)
#    define BOOST_PP_MUL_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# define BOOST_PP_MUL_P(d, rxy) BOOST_PP_TUPLE_ELEM(3, 2, rxy)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_MUL_O_IM(d, im) BOOST_PP_MUL_O_I(d, im)
# else
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_MUL_O_I(d, r, x, y) (BOOST_PP_ADD_D(d, r, x), x, BOOST_PP_DEC(y))
#
# /* BOOST_PP_MUL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_MUL_D_I(d, x, y)
#    define BOOST_PP_MUL_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# endif

/* mul.hpp
CgAAAAgALWdKUh9N7eLJCAAAjRIAAB4ACQAAAAAAAQAAAAAAwGoEAGN1cmwtbWFzdGVyL2RvY3MvVEhBTktTLWZpbHRlclVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIyCmf5VkQAAEW7AAAVAAkAAAAAAAEAAAAAAM5zBABjdXJsLW1hc3Rlci9kb2NzL1RPRE9VVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSIZlB+H0oAAA+bgAAKQAJAAAAAAABAAAAAABguAQAY3VybC1tYXN0ZXIvZG9jcy9UaGVBcnRPZkh0dHBTY3JpcHRpbmcubWRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSuDOrVewUAABfMwAAHgAJAAAAAAABAAAAAAAt4QQAY3VybC1tYXN0ZXIvZG9jcy9VUkwtU1lOVEFYLm1kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnqehSQwBAAA5QgAABwACQAAAAAAAQAAAAAAXvYEAGN1cmwtbWFzdGVyL2RvY3MvVkVSU0lPTlMubWRVVAUAAbZIJGBQSwECAAAKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAHgAJAAAAAAAAABAAAADR+gQAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9w
*/