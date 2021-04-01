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
yTe6vCAp2cQmcJv3rH+l6ZG9bswkOomcPX3Q/oxURlGKfqUxniwWoHf8ZMaa70b81uI5+qUPKH2ZJA39LK0Klo9y9f1KnDBp921l/y3YNdsx3CTrVGJ4hFcf5pwCy35SckInQYRXZWiCyau/OBmYPFaoHYgH31bNmqx9qwywlNSRrbvMfCMu9z6dCYGzWxmFlRqHjrPbPK/fnZhYcpbkl3pNpN5j5WPUHOaYuBSo4m13p6LLPBQV+3PLm9J5NsR32bZF7SBFX5NfGWjMWd3GuYZ6wPxXIj8uQxEFygRk5IcB++Jf5aa8GKd+O0VbfUxSmaEjQMCxDNkPiK5LBOikS5E7jpM9i+6IH0Kehu6KwjrNBuIys9mUi2jrUWiutqmzfrRjzYPgnO5mwfyUoaHNLuci3/3Jp0Wx+HyBhBlUjcNs9fmWZgLosVD7/1qOYMKlnZT0uviry26nP/ldjX1Oim7icNb3LIRm2dPHZXo3LYp6x9tVLghYMnDcpFVexHS9cYL3e7cvg2agsTnptlaiKoVVQOMLB1woQTxCTZ+PT6AaD7p/IbwnrQsKhg==
*/