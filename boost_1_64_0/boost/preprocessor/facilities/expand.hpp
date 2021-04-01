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
# ifndef BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
# define BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_I(x)
# else
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_OO((x))
#    define BOOST_PP_EXPAND_OO(par) BOOST_PP_EXPAND_I ## par
# endif
#
# define BOOST_PP_EXPAND_I(x) x
#
# endif

/* expand.hpp
PP7aiJXmt8bvjhxAN0N0odc5HmXQ2jqSKwCA6B+exHDOT3H35WWV7fePoloHJfQjuDIPyrwFYhoStkFL9d9Oj01/QHElNpcszCW9qVVeJy5pyUvmzJCs0t1/eBpjof8yDWsTlbGfAxDsFVH6Z4x21z98l2QGHbgfY2ln6xNJM2bxAi+L0vtgo/Vl+IVR9rFzwGYT1WqcYKHxROFjON+dQQIlnVa2qW4p/989813YkVFJ8/tgJMtZqDWBih/WfykAAaTXHkknKtHHUEnsiQxS5Ser746KopjLyNJTrpSqm1QncyNNQ+G8dljbYB3w4+KQbjoXa94YdNxzW1F9FEDzJDiO8D2o5oU1zielfhnyWWwnnVkHnTN3phKPYGIt+KHNXvE/ANkuydV8fqviI5GlkVQaVALNXAOK7FJCIJ/weT5nMz567xz9rMFqUMfudNibpvWtSwQLdygKaxrRcNDKfFP5idVC4Z7lBgKPSoduor0mAs+Ms+w1DSJtoluVKRlbxsP25+6m2zEWkzqk1Tw/NF5+Y+X2UEUC2e2/o6rtjJMCsiLGmh0LWSG8Bw==
*/