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
yYMz0OaufNo1SWy8Ldx/2T9FpTNhKHB1ZEX61G0wAX7+7WTJviWlHLfSAHtemx84sFCX6CSe+7B7ZKtW53GKC8RhDSvVjgTyvjGDP7uY22MY0t/r1s8rz9aq3qjdqtUoVitWW1X+RsuciqcAgFKWXiy2N3K6lH+nQ0fuaKHdiuILSQ6KTCytqgvmPbJOFJLmgLp4d2RNOKYPfer+6Yl/lSKVHcPDUrckYdeBGcCMPC/kzIy/D/2UFQctLnoF/5bV4NmJanVyRZ8Kp+7jCUnzehssgvbLwmhcPUNVaJiZJUFGetMMz/jn4x/foRc6iNNpeVt3uQPZqhX0pq8b90qoeMG0ksKVVhynCcNjehjANwqidOgRpNcadmG1hJ3wcVOHvKSv/V105l5pfmK+gvWct2/vXVCT6mLbYNaddtGs1dI/fuWMrJbfvAXf7Dn4at0wFpvIxQZAj5NcZgUfkrU9jovnhjQFLkBNFz2W5ZuKGCgvibuJagU3aDW7iahmkL3iEZxvkMJp/ClAcNdc1kqKw3dG0QfrhHY/tziBdI9crVfumyb0ooGrxgREsacfATZUSzYtEfMN2axn0k5yS1gLeNWeUuRGOJ156dXTUWgc/FLyxU5+tHb5vcw9qkg8UDYipUdqs6g39Jn1vZr10AwEzRBJWgVnpskXeCQDZSJCqDtUNvPBReCC81kJSK9VdcO5GY1zyMuj3gi88whw
*/