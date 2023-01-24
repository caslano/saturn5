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
rWcyp9ShicS69VC2nwdMSZ4R5k/W910+DoVircL+siC+STL0rgzyjuIza7Bp5h01+sezKrkuo5Pf0idmNWPNesW2b4L6AD1XJsyAPAlDvUaI+55utwHYunq5t/UvUDq3FXWkO+sKNIuX7UXpgKHHH5V0Ph/o8pZ95FXFvDZtRZzb7tQoE6jt+By8WMu6Km6jPweQXWv4s0b8bcioXK8SGLyev4qEdsnyBltGhfA+IEl1B/vjOZwCWQ8hO5FaahO7nwnBXnIzuhtnqAvh4q9IUURj9KuiD1NxBl4B2N4CV1R7PZXgnHszOOJeWaKd5P6vuV9TH6iDF3gO/af/avEjxhCIPEFpGQEKTfrkxDo1pH5y1DjvOuaqwC27MTRzNq4XWDULbZBB88vO9mZ8cqdz96uvC+h3Xnchm8kU6M8diGu87EXc5b8SGJUPMtn3KTXD3VdK8Ip9Qt1pzADOWVBtf5JV4ctjLMtSSWlSj82JznlLMOvEdcxlukpVls6Aqha5SrbzyC+WkTrjYrsqaPY1qrhCeZjUZVjwrgl7tFNF7If46PBX+6HLGuxMVz/TTIJY5wjz9xWTHoxd+0CoPGUXmGoqm5xcsCGyBQESqnhtP+vCdG7frPT6NjJNHoJ8Yc67rMKogfuBjVckNfbuWA1Ies2Zye2GX6plbMNjZyqN+htQTJxRn76lBCm1qrCZ4YoJQxZJ5reqnRDkb4zP
*/