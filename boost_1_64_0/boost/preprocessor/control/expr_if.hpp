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
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_EXPR_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# else
#    define BOOST_PP_EXPR_IF(cond, expr) BOOST_PP_EXPR_IF_I(cond, expr)
#    define BOOST_PP_EXPR_IF_I(cond, expr) BOOST_PP_EXPR_IIF(BOOST_PP_BOOL(cond), expr)
# endif
#
# endif

/* expr_if.hpp
FoyQqEnSJY/5YTmpkF+iDFaFHtdiFdJbhyWNsvf8YNBexH1aFJYQ4HSXPEUc3R9HqhW24YePf22m2N/O7Ue9QDrGenN8Pzg6L27WZYAgfD0xmuqdxwcP1yYiLlSXjrEJzsXy+Mlp4IIdUES1X0pW0+3gu8WnHyCd7dPBWBzYf52dYttfVUISM9bspCLOlFS7djbqpAzIhi64JS3t7iOh5U+m9LlnRk+aZ4/xCbzuZ9GsMkiBJgAFhFovAWiG0t4RCvo12vQrdRIvUNZ99t/TV9qOf2gsr21Av5Z8hMom9EpWZc8/RD0yI7g0bQ30rn8p3LAqRqqMVGrIEP/iKBvoVU2fc/xQXfrTdrcBOicBrJiAqEJfWVC72wQiPbt1LaIAMKBuIuGIakWHsIPXyWLi7s3enfA4oBgtu+O6inc2BUg+/5Ug91+zM1Qqpq92nKhsfQAk3kyXG+LVuEFzzRVbgVVRJMO4t/PtSkycPzWOdIspWv4bICXblkuGW66CxMu3gM1Bl1denWhC2G+zPtHrLvwcTMe0J2kuauvFsjoQh2q2iSmVFcZ3uMUiCQ==
*/