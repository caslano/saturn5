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
5FpRKQ5/mr6La5g6awDa79wsnGsdMOq7lD3SD99PDPoNZI7rfYASrSNFhc0F1zIfH/vsd0mOCT/P3mAa5wwyeuJDcSQs+CG4uuES2LhtIO3UyKT5kq3TCmQZwfyuQVNLuz4s3QBTumkUZkzDsGyxUBCPQ52fJanH/WxhjLvag4V6bRft8HSNMtOYZ2U9K+Nx8iYcCCw+6v6PBrAdB3gMu8vuIU0KvbBLWCoX8MXOaREK0g4n8Sa5+9DFmW69H3uV1ScSv0qY8yfZTJfTg/OEhUP3GgQWXIwxTZZXLmEc1hAJG9pR96O69vXI+ALR/TYZwrIdsaVz+jAP5gp3YOYJA4eW4y7UuHAHMoQjRxcBwMftIuTNSAno8c4+nVUtkNmewdkbNcZVLKIL9JZr+TjsEigOZ1bDVzyxmOvLQURag1M5d98Yl2RWIJMJEiBKVjr0V3sD6bVsT+Y0f2saisgEnWUShU1KtAlzO8N73pYuF3AhLkhWdR5pmdZW+Zry0HwfmX3ixWFGAKBtdKWSranalNt3dxZsZ6oIGI5kr+JG7Adh37/PqH3Xybpl1g==
*/