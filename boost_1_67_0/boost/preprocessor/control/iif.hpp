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
# ifndef BOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_I(bit, t, f)
# else
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_OO((bit, t, f))
#    define BOOST_PP_IIF_OO(par) BOOST_PP_IIF_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_ ## bit(t, f)
# else
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_II(BOOST_PP_IIF_ ## bit(t, f))
#    define BOOST_PP_IIF_II(id) id
# endif
#
# define BOOST_PP_IIF_0(t, f) f
# define BOOST_PP_IIF_1(t, f) t
#
# endif

/* iif.hpp
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
*/