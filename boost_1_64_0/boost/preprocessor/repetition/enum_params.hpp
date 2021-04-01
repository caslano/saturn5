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
jy3GHKB7W1W/fFEYE22Bp6sxY40kCAxqb2r8OzaWpbAmL+YF/eHcF00Hnt228DDg2/37vukvm0pqAYHTNdLee9iYW89ipXLi6zzEplPaFf81tHbx8E/V0N4eukoVi+skg8sq2cxiJPpPrB3Fe34QJrINU10lUlk2D51qo7JvGnor4E9jZJHU6kMCixcDus7iZlneV/kc7F+MPosCUmTIgkxb+bvwHy67CcCNa4O2V1Ck4LYGmIVxWTalasJ5UANLzTMxh33SJEhaRx2iJRCMO87AQAGRr2+i+yNPUGLkg5nsi89vzvuXbwd8q4RRVdlbqeQ49iuviUMML8rphDIN1EESBk5myacgCGL2OZWS1lNcPjgu+Ll89ZY4ZMgbDjQsLz/22gEN80A4+oJCTm+1qMFNNuWkF2IGyU9IwgwQNuVyBlfqucxwxM3Ezsv5ntyxhCAdbToBpHMT/db71KLIVC6Waol4GnwKLXP3PHFE3Cgj1cgb1AegyMFWq1CxUStIUtBFofX9jEuHxaUYyE82MPrHB6y78D84g166nQ5E0Y7dEfJMouH3+Y475A==
*/