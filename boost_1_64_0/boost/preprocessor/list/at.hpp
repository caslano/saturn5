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
# ifndef BOOST_PREPROCESSOR_LIST_AT_HPP
# define BOOST_PREPROCESSOR_LIST_AT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/rest_n.hpp>
#
# /* BOOST_PP_LIST_AT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# else
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_AT_I(list, index)
#    define BOOST_PP_LIST_AT_I(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# endif
#
# /* BOOST_PP_LIST_AT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# else
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_AT_D_I(d, list, index)
#    define BOOST_PP_LIST_AT_D_I(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# endif
#
# endif

/* at.hpp
Li71eG+c9o0TmLPm9u4EnJF6OGCJryEXevFxngChCA81PhiIOk4BwJsWtC80QRtvpod0h+2JPJahRGyPdIPNfMfGEPUY2K6ZfKi3CaNi+1xo/r93yuCkaTKi/PW+rlRuccCmo5gfyinUBxAaAh0ubo4NAT96A4Jm5R6c+2gclcjxk1A+4Kg3cXuJxeUh0RfKN0nyUXs6LoLOfDmw5wl4GS/7F67uQ6pW/JRZWB0v1N5O40oON5sXmfyhOTxc8AaEGrWRL16CsL+f5dyZKVvnvgDsBaP1de3AwsFLudJddPBBbyUfErJGY921d0Y1481dGFlGcOo/CcaAfyPz2CzMsx0CEX+4xuN9j4PyIHSLcKn9AoEzYFuScWQMkX5c/kSGBMJv/1a/kjesV3o9quotHweDUEFDrLj586Gv3NSXogqTU50jU7RYpyUfHfv3SngNQ3JPja2M4v6lQlgpHJXM8d8InNxO3p2nCcrxAppc1wKtqPoNkNXgiWUfJkRVuRKwzjj/kv3RLZZwNhAPI9Eq8htksib4sDDylkDcQ4IdBtWz4wP0zI3LhNUS8g==
*/