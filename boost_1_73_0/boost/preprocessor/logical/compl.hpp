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
# ifndef BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
# define BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_COMPL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_I(x)
# else
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_OO((x))
#    define BOOST_PP_COMPL_OO(par) BOOST_PP_COMPL_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ ## x
# else
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ID(BOOST_PP_COMPL_ ## x)
#    define BOOST_PP_COMPL_ID(id) id
# endif
#
# define BOOST_PP_COMPL_0 1
# define BOOST_PP_COMPL_1 0
#
# endif

/* compl.hpp
FVkAcL66ksl4qG84KRjE6KAct4MpKUI6UbHEF576QwMC8eGFGdq1cd8VbiKCgWGUZFCKGMtGYVmgBA/K06fwhZjcBWZoIikKGScRQjpxPtpxiJAIDcXCQS63cIomsf6aybVQUQuTiiXcEJbVaGQv7T3Ywmm+qj2ObIkHiCWJE4pF2aL7BMHC5FjYd5wrCxXNFwlT5SFcMI7Kh/Fbbnf3fgRFi4WM9iV9yO0Ehl+ogXHh7HRx
*/