# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_BACK_D(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_BACK_I(size, data, elem) (BOOST_PP_INC(size), (BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data) BOOST_PP_COMMA_IF(size) elem))
#
# endif

/* push_back.hpp
ymEzPcZtvLiDfLBeXsAJgqhQu78SGeNBzgeZdqfGr+ma5NYAssb2XY3ECyNNueqTxYJuc+i893Cc1mM7IkesR3bTiJlh4rKUEh7HQ3VwHfUqvaqW5rE52bOkTnZ0F+evmM8g3sPeQyrUCpMzB3rUoBjwMbkiUNGQRbvqJfnB4jnpyQP2TZohasWYYjXIKEExE9EQrUqaPWV2L0W4Z+zFTdExpvcqBf9boShGHV0nltHh2Eauqot+IrTRS6asLUVvQEED0G1ooO5nZISf9D9r1N5yf1Bz6d/JuZBrAdh+BXR5EPpyUuRRRBHxPvNqHpdC0WxmoxiaaO1TYc5Np5otCJauhto4ptlc0DvD90Wk1Qtt8dmhKtOIB+9dl8HfIZkHo28eHhUm2uM6C40uP2kcYaXWH8twBijng9APs+tE/+R/C7NJViPtYjVqnQMV39NojiEPPIRxatTDzx6QrB3pk1khN1qBPJT3mC+LqOfA5V6UPHamQcQ1xdMNWOJStXjOHGNLE06bmLdIV7UuQyGwtnWYnH4YBvpUrHAIr/9+SFohTuXIdGpbh8G/OLcQqqW73Wh75TkpwHUnWJ1KuusJ+sbxLX22tZJyk5x8W6LZYhEVJ94Vky8irZXIjcT4xa9bORn9Y/wMjxFiWTti8BxdgNtgfbIERsPyzXKuosYhXgOvhtd7TbWatHAfm7ThERPzdtzS6keWXZXnT2SO
*/