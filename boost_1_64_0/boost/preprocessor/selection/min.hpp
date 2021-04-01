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
# ifndef BOOST_PREPROCESSOR_SELECTION_MIN_HPP
# define BOOST_PREPROCESSOR_SELECTION_MIN_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MIN */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# else
#    define BOOST_PP_MIN(x, y) BOOST_PP_MIN_I(x, y)
#    define BOOST_PP_MIN_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# endif
#
# /* BOOST_PP_MIN_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# else
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_MIN_D_I(d, x, y)
#    define BOOST_PP_MIN_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# endif
#
# endif

/* min.hpp
4IOTPi68Q7WnU4S8rwi9iitIL6HsVXECPt7bcFIhQSJS7qmDnM1ElAqbQMCgD8blV6DDWLCAcSeU5RZZozwAm9Vt8JwD5bw5m8N56KPgn6fXhBooWiRSe1eo4woiUn/z9L3gCvt7Al8rhy+cHI5P8g4aGxCFOm7dhqUkrZt+vpgAuKS4EXiBhPu0G3+HbqGLm3N35g/BdPXdUK2RzttPWTWW0P02cROZXMUw8Gr2XT4K3429UiZ5ZWvp0h9h2IM8usy6kfiCspB0kZv5Ih31uAVxcSqGO+YD/erhqZ5YuUSdTbhF6vMQUqAbuUs8nc5b1fAnuKWOUN5h1e5Y3pIAdGQDG7IaXY3xDnslrIYwVfh1kkuZfYaukPu5ah+KxglbvtOO7TLngPKdRrhFCUNz8TU03RCNn7h3c8fF1OFHfkE0oBMJOvj3Qg40n9+cAY5hb7U7LY2UBw84un13LSj4v42nC4RrTcBGkObwldVlDGDSMlxhfXA+tYvhiPjcBFuXuoNlc5VClvykDCFMOrJuDdV00Ga8NNhtCGZtNgzBSmKvYkFnMwhNl+da1w==
*/