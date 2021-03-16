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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_NOT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOT(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# else
#    define BOOST_PP_NOT(x) BOOST_PP_NOT_I(x)
#    define BOOST_PP_NOT_I(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# endif
#
# endif

/* not.hpp
9xnt91nt99/ab9J8jBl0+BRrY4Xu6vLz070hIfEs1mcZtEjynyqf58vnHY3ccOWveB6i5zNemaeG3PASD/xWD3y5R34jJH/Ly6mPy1LvtwyJX7WVP/7ReDf+KInP3/vhH/fg50j84+Xgn/Lg50r8U+Xgn/HgF0j8MxK/vPMBdveOOF/Ade/tnki46zySvZFwfjrKcXWuxz7f8wnSRuYUODhfyDMK/gnnK386o/iaYoVzwJ+OhaPOCpHnKSSFbxQ=
*/