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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM */
#
# if 0
#    define BOOST_PP_ENUM(count, macro, data)
# endif
#
# define BOOST_PP_ENUM BOOST_PP_CAT(BOOST_PP_ENUM_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_1(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_M_1, (m, d))
#    define BOOST_PP_ENUM_2(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_M_2, (m, d))
#    define BOOST_PP_ENUM_3(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_M_3, (m, d))
# else
#    define BOOST_PP_ENUM_1(c, m, d) BOOST_PP_ENUM_1_I(c, m, d)
#    define BOOST_PP_ENUM_2(c, m, d) BOOST_PP_ENUM_2_I(c, m, d)
#    define BOOST_PP_ENUM_3(c, m, d) BOOST_PP_ENUM_3_I(c, m, d)
#    define BOOST_PP_ENUM_1_I(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_M_1, (m, d))
#    define BOOST_PP_ENUM_2_I(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_M_2, (m, d))
#    define BOOST_PP_ENUM_3_I(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_M_3, (m, d))
# endif
#
# define BOOST_PP_ENUM_4(c, m, d) BOOST_PP_ERROR(0x0003)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_M_1(z, n, md) BOOST_PP_ENUM_M_1_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_2(z, n, md) BOOST_PP_ENUM_M_2_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_3(z, n, md) BOOST_PP_ENUM_M_3_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_1_IM(z, n, im) BOOST_PP_ENUM_M_1_I(z, n, im)
#    define BOOST_PP_ENUM_M_2_IM(z, n, im) BOOST_PP_ENUM_M_2_I(z, n, im)
#    define BOOST_PP_ENUM_M_3_IM(z, n, im) BOOST_PP_ENUM_M_3_I(z, n, im)
# else
#    define BOOST_PP_ENUM_M_1(z, n, md) BOOST_PP_ENUM_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_M_2(z, n, md) BOOST_PP_ENUM_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_M_3(z, n, md) BOOST_PP_ENUM_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
# endif
#
# define BOOST_PP_ENUM_M_1_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
# define BOOST_PP_ENUM_M_2_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
# define BOOST_PP_ENUM_M_3_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
#
# endif

/* enum.hpp
Q9nNKbFT0V8r0KmVS1qNKnBh8PoNGFycTKKhzRm+dd+RWkI2lL5tOajntzIgfvLOykWTL9sAOrw4bUBKyOneerNeBItZoLwBOr74b1aLwj/xUoLyhHWuLz8Z4bCwHOwPQ/ICd7r1Ih03YYdgoPOc+JeI1SRChgDPb8NwlyAT+dgt9UpK70JYHy+SKGBdBNcddB/EBflTQvjRdBy2x8Oai2p38F4KfeoTSMl/UXq0e2tK4ytJIrHicUDZ+t7E/LX/SE89pWkLuLwRYGA3KvrWUs5Emfdmfa4OoRf+VXu1H8aS9TogaNAwcbzsqfQ1P4GjcFkWA8qOUCAEi8W+5zHJuLQc27VoEKGtAtGeALavIxWiIE/CF7hQEliJLoG3df5hLz1Y7iEXFxndi+dYMVHRzqaTR3xigTztH0baQKYU924f8mgmGWYlQj+MI94qw0LbOcAObADYh5UWOQtKEojV10iyLqibJKteePuP3oUJMDFwZYBP0Pq+50WkP1zQQABY6xRl0Kv9cT/4b8OfTXEiSbDmzm1yzhPGFBMWJaTV/p9Qee6Jh27iseNEfA==
*/