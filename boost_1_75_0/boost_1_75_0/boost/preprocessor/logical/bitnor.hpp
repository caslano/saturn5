# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITNOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITNOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_I(x, y)
# else
#    define BOOST_PP_BITNOR(x, y) BOOST_PP_BITNOR_OO((x, y))
#    define BOOST_PP_BITNOR_OO(par) BOOST_PP_BITNOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ ## x ## y
# else
#    define BOOST_PP_BITNOR_I(x, y) BOOST_PP_BITNOR_ID(BOOST_PP_BITNOR_ ## x ## y)
#    define BOOST_PP_BITNOR_ID(id) id
# endif
#
# define BOOST_PP_BITNOR_00 1
# define BOOST_PP_BITNOR_01 0
# define BOOST_PP_BITNOR_10 0
# define BOOST_PP_BITNOR_11 0
#
# endif

/* bitnor.hpp
EU8QZ+uR0EL0YgtsbALrawYeNNvzLlHsTfLsse1G9toSPBrpRix+0R50uMMOzfgod4Y9m8kGcuRsjrFunz7Z+cc2lZiyC5mOilJ7MmVM1B09/Si3+MmpH+6EL5cbsoAr5uGkPwN4hDS5xRV06SoI5cB3c976b/DprllfAo5l5bZtROXusO5tkr2KjGh8KCBSyV7FzFm9GJfGd6LcE4cilaOHBgy81Z3YUIaUp0IKq2RYRWavckD2uNCSVVavVt/g4ZbZwYICMeB56yQL0K966zrRjFvFoaXV1Hua2Mt39FSM/EzAkey7qUBfm0rOI5tS5QKrK578k2YCdp6UOevtS0CN7bEXu9WHlcVhVnUihf1boQ3q5cQUV3UrEZFkVxn1OyXZBzeY7Ejsn08PDtROJywJAc1rww32nrfMOQYw5hzZI10uI++qe6iyf5hLF12qv8LTTOmZMMH2txQAx70g4P5yCA1bFLK4MnKImYo1yK388mbNer++RHDxx4xE/J+3frs9SD/8zvFWK6e+R+mlmPhz0igdf+z33Kw/ENOt0ofCM5DNPkF4rUgvDHEG/Mtqh35VyadyKaZocuXVWV1e8Apfm/esOl70/ukxMRyX+s8tZiQXsHiirrtnpj0O5uuCqgPm89J8VjM7hR69zfoVk4I6E7GyDW1W9ZHplcQqE4U1pvZIVhPmNYzGV2T3j/lV2dAPqAB1n7Rkq3XE
*/