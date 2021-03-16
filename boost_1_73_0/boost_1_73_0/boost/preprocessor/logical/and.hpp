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
/93hmzrDf2yBD8IoPwE+rOZyk/bDD4QxioyBH9wPnmdBJtuhl+MQJ5/COOo8cq0EjPHG90VfIEYMqQifhJg+G363d2vEEMhrcnWMJxFHuyGHmNOZUQg2vq8MuehLyDvngIcRJgW2wx8c5Lke0Z+wzwz4nqHbGC2H/b8Cv9xzB79HEbxgnDcX+VP3IsgT9U/A+KdsBFEhxq5v9saYbir8Zr5Be7/G+PdXRp93QnviMeKFjF5djDzoMPwk10HUVwQ=
*/