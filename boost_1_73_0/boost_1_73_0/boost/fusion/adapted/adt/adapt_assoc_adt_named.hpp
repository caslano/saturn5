/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_assoc_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                  \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(                                       \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
    BOOST_FUSION_ADAPT_ASSOC_ADT_NAMED_NS(                                      \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_adt_named.hpp
68FoXqm/eWKeNojjz9T8wfAG6zdA9elo9Tnu0TdZfaaus4pbrFf2Oo6/Ae7GBml/+tb4JraX2GksW/uh2u4rsckNdYc9On3x4ld6Rs8Hzwc+nTMpeEGR4XLNq41Pr1K383vO7u4Czd/4xA2xInjkcJkLTVplZscqTrguRMKl5ikxTSnXSSXWuBGSTM4pEwWn4Wy+Gk//8GmXiyRv/exVTTpXdZFSzm45VTzh4rZxs2WVIZXBA/ynQhv4rI1QMgA8J8OrUrdubBCs0IrYLRMFWwOOGcqN2erf+v2krgpk0k9VovvJoRRBbsovslohmpLtSW0NGUW15j7Z8z6VKhWZXVEibG7rdSF07h/DAqBM+6oizYuidQdTwXWTAqeorZZvT9IW0QtjF62ktmi7XJWPDqKsraOsriTgUBacSxUK71MtU165864QB5S2yq7kX2nZMfaUlERU1AkjGkcdWjMttE8fxsuL2fWSPoSLRThdrmj2jsLpqvV3OZ6egxsCqBXxu23FNaKoSJTbQvD0Efh3nXQvWF7Q8Hoxmc2X8XI4j6ez89EkXNEZdc4G9GctQe3TnzvUKcTa9p5+CX4aBANs2LuYM72PNTe2y/iCUBo+owuahlcj7ynHN8/QVuPq+3C7MXam0Wo6m0fjyPtB
*/