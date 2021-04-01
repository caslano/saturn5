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
fol6bud1fuFZr29ugwVhoVPcWC2kLqPDD1Gp0OXvK2VOPI/6Ih0iD1yltlSZyey6vnuB1wGSLApVQ60SO/hwodIPLPe6g2eMhWmVSBJ4zCJ05VPq3HDJPND/b+sXYnF9S1hqonD8LfTgWJMFfYI0IIRxmmtnA7lNL+fnQfTkV9mZHGnUIqGdO4k6IBs+FuPCfEIqJDnOZqWTy6DQcbDnEacHi6jD2A6z9BCH/sLRc4GQgXoxln1gz4ippvVAzb++LVBV54PdBGdZPgVZbnPTwH6mRKY5vMIT5zWBJJk/kQBfI9q6QDMR86CXh0WNUGcMK6j1LK5h4C1OcYLQzzMGIXyfx2vhTs93KtXbU2iJ5CQv7356Nhz395RE3pypiKxowDI1TMfOI+T1AhyzbM9BHY0bA2Lu1WQRI0PHUdhjnUERD9ulXf7HQD98n1K/XuL9/68C0ROrKJpK8dYsyARCXmTkng+dj/L4jmtjsJipaTFzV3j5oWS4t5ORvCQzn8VAtlSoRz3VYN1CFUyqxvmffDihn+OGMkKwNakd4Vz3gkm6iNbWj7sm/kiQDA==
*/