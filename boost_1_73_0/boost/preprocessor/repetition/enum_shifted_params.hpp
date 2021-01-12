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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_SHIFTED_PARAMS_M(z, n, param) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(param, BOOST_PP_INC(n))
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# endif

/* enum_shifted_params.hpp
rRTE+OXsv+Hxdq2mDfPI9+s62AbkXmZ77rVENe81UL59kSHyL4/lefyaNTXVWofyE9LR95XUJwP71J2xhpwPUOfQ1eis6qPwMqyVezyax6uqP5pTv+TpTy63cSzjZh3yo85BPuTLOLlN/FnVaRtyuuyN30LdSiC/O8h9VwJ1SkXWRdHZEYxT0qdUIp/y7GFQn+jB1HcQebyIfXJB9u4OupjusF9AOXmPMcXwy/LskRUPJC/6
*/