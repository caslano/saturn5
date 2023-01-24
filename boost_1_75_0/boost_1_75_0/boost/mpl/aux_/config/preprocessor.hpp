
#ifndef BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
        || BOOST_WORKAROUND(__BORLANDC__, < 0x582) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502)) \
        )

#   define BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION

#endif

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)
#   define BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING) \
    && BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING
#endif


#endif // BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

/* preprocessor.hpp
n0ZsfGD1VN6KfM3Q8p4+nLPM5PF10tDGc/4I+o+RI460TR6fb3/jyCJGIdajs2Pk4Sstb1ua7rNZc6Al9fjTTXBsjIrKJ7y0U/lC+/jLGhsrKKOR/VNp4B+lLBY/0Nw96+/Ua4uYfzqYkpmBKoBCP6o7FiY4Bje8gWmbhM4rODjNDPt8/6QZUencPMAMb/StpgY0WnYK//HfyEjaJp0vsLW+nkqU7F9zeRs5OjeiGVoPg9oOhb5wIvz77Jnwcab70Cbwee0BbNe6v5tfgs7/5KNOFo2Ax0HHi7925PsZdEICBUS8NFTuhnOTT/0pRc/5MWexL3awTzbcPbRmTL1mxJ01rl7v7Y+IUuSNbBn+PQeUtXNpSszzcz9bpFWgXd1Mav/J+rUpOon20oWxFrTpyviJ0VklyQSRysV5bTmE/xFJ7/3ffvJ2O54vwWpYLVefQwte+vUGoDz+6v0uqtSahmfg7h6skdxS0Kdu4qxd4Wdv5yFfEjbAbw8AAvX+zqEFaWNl0lLu8pCM7O6HEjG9AYji/5+j+z9HOxz9vsH0B/TfV1bF05JnRv+XykTwnysrDXMbS0dTtn+9WB3dbc8DEQNIhnyfJil3eFr7aKnFdFFWsUbt9UQ+BxEYpFlQJzhSjPHIfvfxc6ZhCbo8N38UHgvDkPrkVpUikVVcsUeL2oUF4M/icpRX8AMcJ24r1VErZZV6Z5fK+kl9XGZk
*/