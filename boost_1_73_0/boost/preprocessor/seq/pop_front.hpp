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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/seq.hpp>
#
# /* BOOST_PP_SEQ_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_TAIL(seq)
# else
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_POP_FRONT_I(seq)
#    define BOOST_PP_SEQ_POP_FRONT_I(seq) BOOST_PP_SEQ_TAIL(seq)
# endif
#
# endif

/* pop_front.hpp
pBvc5afLT+hAmi8+6WF8X3yM2hN1OTOUuf6ySN/WmuRH1z9gHt6IX7BzC7rEPOC3Db/Sw0CfsCvcXfHuBuROvVqMw3bUoE6nuXsHubU4LhLall1+d0Pm0V5/fJbK4ehKGt+xoRcDdenP/NOa8VgnlDtSNV3CIvGHYxlfWwzZVRU5IT8X6r2O8VkHeffn++BpzDOT0EH8xmrYyC4jzJ0JQz7PYOf9O+Zv6reJ8TkDexH1EvrU
*/