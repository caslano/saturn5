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
1ooWv6f/5hebvNX+P230v8gl5jEG7t0LppVdon/V9b5ut4g/uvKBug0wImzFn9Tm2cA2jXd4u3MfXMnObXu9cCEIOoPdyI3Ej4TmojdYv7LK1VPcZySVF2U3sqoTpHGYbYvJlBfloTaNYo+6KXyz978XiZQX5Zqy5sF4cE4xuPpa1WnCD4/hTEKrlPUVgzAN0av6o6gQke/x4mTv5Mwb3aSJETl2fLO3Z70SMj0op0ZdL2EGzutbvBq7heGsMNd2pjSRag2Vy+rvjz/hH4/1A9ITU3bM23J4fbwHYRwWqI5ytDjKygptfWNXTBf114LlYmrXPbPvHLhpZc30cjfn53WX1h3d5mWydQncG6T1FItbSkr4VvECvu94wl5y++HypjXcthPRLacs7HGv/6xqu5xE8muj/cPc8X/HhvDw/KdIUGeiJW/4ZGHM5gcJ43EAvjYScnIt3gc8pCOxIaJ0hBNME2xpQzet2awFAwuoYaiSfC353B2uXb1ov7LQ4sfchmwVAuWTm7SjwRSPdZvSBJtsfuW5Yg0mBgfdJWVlUQd14d6XXIBHXe3Qn0JWnszWlOuJtoPbs/vca9HJlY2mgFerqs1n2BK/XwxxcVFzrNiXjNmrav79wi/fUTB14B9yVXwnjqjL4BpHERKoHnq7qzMROWvdpNpIbKjpiGNBRH0KW5hbCkdIO1Sc34t6PSTXEubg5/OKxH00aQOE
*/