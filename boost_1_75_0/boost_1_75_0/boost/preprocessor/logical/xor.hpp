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
XVABU6f5QxUfrJ602Rt+8hEqb2Izb/QN5A2+/AXhIwNrZmD7/fRTvafl4QvtPeLjB2CkWOwdgdvsyG7R8xtZGBPpAWj2hXSF/5H09/HR7g2C6EfXsxsMH+35Z53tLsoXP0yzJ15gOtXPiutPPu/5/BaRbg7yH2MGxjsATYhNV96PrLGatk06f0Sl0GozwMMrPDriRuq8BjeefeAyzrmUrecEQXdSy23QEXOqf1i76jPnDd+j1qMQMOQ17pWSz+BGeRzNCebqtzA3J9X6D8IW79ulBUb8Y8r3Nfs1oldv70AMOddNkvXWugvfzxC9AlpAbVI91R/O6KYlVnZw84+O8smn7CnrgxslKrxJdytKr8pClFc2zm3YjpUdBygpP3fXYr2uhPc+A/iTyn0RXXWZSXcmt5uh7HSyeb8dGru4ojmp6rLv33Si3FYaBn2+eH5x344BHRHvZp53FfGnUI9cq8nkvi271slNcBMBoY5cey/UceaSNHp8FrNmncudsOKy9LpdJSNDzP/TbsWWY/M78ionRa2IEtcqPk5415vK09gedtPQnJL+mDVNvzehEqvXMxMS77IHiKSZNCPUsUafjhPTvZyfdL9OJxM4TvxV4gkQMVJiKnonNiwCFZ34o88pCDgKC6VF/8QAtb9s89jkKc0tENYrkP+V3V9tMTiL2e7YeD7e4XM+eaWDyO4W9YOJ/crmkyVHyJ7RtKrm
*/