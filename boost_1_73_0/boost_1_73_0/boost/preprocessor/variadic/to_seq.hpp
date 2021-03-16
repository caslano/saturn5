# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
PmKHmFRETohhP05IJ6eotETWy8R0sizcpKg8f+INz2Vl3OSovFjclKg8Y1o24yqj8gxc9/R+i0xl7p7efxEs+7o63m41nTGoj6nxNvsYtqM2nX40R5dxdel0IxyXOS1GHk/5Zcz0GFmM6fpnfqMpwl3/zGcWbmZUnpw2H+DOjsqLxZ2bXp7KMIHfzksvz8c10L4i67fibLUxs6JygjnEjLkgKicyz/hCExPMha2t0/PWWdbAXOonwgn4egq2iJ0=
*/