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
# ifndef BOOST_PREPROCESSOR_SEQ_INSERT_HPP
# define BOOST_PREPROCESSOR_SEQ_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_INSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# else
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_INSERT_I(seq, i, elem)
#    define BOOST_PP_SEQ_INSERT_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# endif
#
# endif

/* insert.hpp
CpnE2lrEejDpb0jSakP5+bO3VZ4/7AG0KD2hkcrb3b+Cc45+Xf3JSr5hXjiBiRiccc75+wsbW7mf2MMMcwZW3OIfU70mTFbqksmmBLetNTWVE+SdyEmKTTe0bUSBZw06xpxczo52iPqgrQcpjM0vFB/6t/6IbqtNB/4P1lIVUyg/pn4JBJPaWDz5CYh09lu9f9l5wbVcP07tm2ZnzPvaCH2GanFGfBUu6JHh+tv3VPgP4EjoI8p+IZRQjsngw5pk1kUU4koZM7uvOBT0woH1x5kblHmD8Nu5tx3B/HcQLkxQUI4uxqncnqbuO+pM4F58KA05FPJ3Rg1iGJh2wKGu6y5igVB2MRTRk2pF8u7lj0A9h1cETdpWPKgAo0IuhqYb2u6jBXrpkP//UNKYoDeFvISprV3IrlOtGcYO9aF2/q86k2IgfRtfAJ1AGqJc7o6uLCq4TfJE369KW8xnv46NnX8+NwkM7WGUW9Cyyb0DdmNKzWk2eDO88+LUZM8mPOhoS973/nzMeN2DVFGLAiJB7D3zHbYs4yW1whc0dQfBnmxwy9OXFSVh83xSFQ==
*/