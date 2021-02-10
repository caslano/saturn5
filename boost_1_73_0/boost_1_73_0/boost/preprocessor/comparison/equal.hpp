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
# ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# else
#    define BOOST_PP_EQUAL(x, y) BOOST_PP_EQUAL_I(x, y)
#    define BOOST_PP_EQUAL_I(x, y) BOOST_PP_COMPL(BOOST_PP_NOT_EQUAL(x, y))
# endif
#
# /* BOOST_PP_EQUAL_D */
#
# define BOOST_PP_EQUAL_D(d, x, y) BOOST_PP_EQUAL(x, y)
#
# endif

/* equal.hpp
OQEAACgACQAAAAAAAQAAAAAAf60FAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2tleS10eXBlLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSWJuZjLQBAAAWAwAAIwAJAAAAAAABAAAAAACkrgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMva2V5LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pScfvNzPsAAACQAQAAIwAJAAAAAAABAAAAAACisAUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMva3JiLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTXSWjusAAAB9AQAAJwAJAAAAAAABAAAAAADnsQUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbGliY3VybC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhj9dTHSAQAAIAMAACoACQAAAAAAAQAAAAAAILMFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2xpbWl0LXJhdGUuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKRpTU1EQIAAN4DAAApAAkAAAAAAAEAAAAAAEO1BQBjdXJs
*/