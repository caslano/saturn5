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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITXOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_I(x, y)
# else
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_OO((x, y))
#    define BOOST_PP_BITXOR_OO(par) BOOST_PP_BITXOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ ## x ## y
# else
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ID(BOOST_PP_BITXOR_ ## x ## y)
#    define BOOST_PP_BITXOR_ID(id) id
# endif
#
# define BOOST_PP_BITXOR_00 0
# define BOOST_PP_BITXOR_01 1
# define BOOST_PP_BITXOR_10 1
# define BOOST_PP_BITXOR_11 0
#
# endif

/* bitxor.hpp
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
*/