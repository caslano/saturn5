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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_PARAMS(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_PARAMS(count, param) BOOST_PP_ENUM_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_PARAMS_I(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_PARAMS_M(z, n, param) BOOST_PP_COMMA_IF(n) param ## n
#
# /* BOOST_PP_ENUM_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_PARAMS_Z(z, count, param) BOOST_PP_ENUM_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_PARAMS_M, param)
# endif
#
# endif

/* enum_params.hpp
Zz2szwGrf79NHSc/OTxN6XU4fbiP9hXNaePi389rO+Ox8tLc72OR+z87WpFXwBPaM/9VijF1VGc+7Ifu4uu1LIv+Yl/cyP8W8phUAdvvZ8UfQt0cj53oa2rJ3xn7+dUY7YjeUH6tBaw7SD95oxXeXY3xi/hYoymnELJt4aBTowoxhpQMaqxnbE2h/BDk2FDZJK7b9SDfSlBklvUHJVNXkwa7kPR6Hp8jBd9V2dveacwrvoxF
*/