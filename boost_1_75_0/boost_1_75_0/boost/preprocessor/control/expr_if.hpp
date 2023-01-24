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
z1xOXFt/P9eYjUAmJiMU1k23gBe7TzFi/j114RCBOz2IgIl2M0XAcWrdE81LtLcJ5u1z+n2zZAm851f44IaAQfZRx1gjE4J/++hrrpJp1qPPI4mr1Kl9xtPlApPmdtbj9YJpUdyP/VBYxY6YyC255nb24wAA2RcRu14S+LI041eguZ3xOLvgxbRJ5tcoRGHsj/Q1fprF8r18UTuHHhv0BC0HNmo/9X8BEwYOaPLKxCUICwnZGEmu8un7xuRmdyatoZSjOc181KBBYdXm18eMpSleU0ciFmgKjtrZEKJ8uTglRiwCJ88H8NEXheMDH2XLpMuFdJWy9w4aqoXvU7j6Q7ddM1iHoXXxpTPfI2qvedzEgUNWEVXW92wTGLRSPUoiJ+qPFAGk19Y7LS6AbmXgh1sy4+FckkGDFsuqklrcUuodTM8K3rtg+wucODYp+8bGfLFx7vW01xVD4ONuCb3ztn14s5+QEwS/Av4S0sOZ+fSyWwnRhNTWHJ7uWbvtQIAryys1OqxB0qV8pQc9p4hQiEjF453MOIfvc4AkOAJ60DLYKSLGnpveIgjP4gzcivIxNS7z3+oni0UaOmFt9OgNCsg/I/BB2IcyI8eICi6OnuJzHtD8k6zttaXAoW5kG0RFd87m84TYqeeD7jmcdWczR885Qg/+8BQqDEz2b3pR8ZGAbl77VwRI+YXULCLUjxV70Ndw4P5HS6S0SJn8
*/