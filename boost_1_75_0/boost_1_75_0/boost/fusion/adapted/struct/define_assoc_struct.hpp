/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0_END
#define BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_1_END

#define BOOST_FUSION_DEFINE_ASSOC_TPL_STRUCT(                                   \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_ASSOC_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)       \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_DEFINE_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),   \
        3)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT(                                            \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_assoc_struct.hpp
4fdNwk7/VBmf6nGpM5yzYRKnI5vyKzMUByRsIwxfxs7cGo+6/TjZ/kcupVnJqEut3CuE+yPTDjkhzSlAaKb38Du9+7GBAL0hUwhfl5HpKcn5lyhtpccHthUF0h6AxvDnTxCfe3ZhS47Z+LubqLrIH4JT6nllcXz7PNE+tW2K/KEF0DqHZsv7tu7QOm0Qo122zljsmQ9C2VN7k9o6HmvxKOZ/oRQygyIibnUVHZCSfxnMHfjYc1B7IPWRScpi33MtNmsuNWuOxPyhTEXcqOM7kf/LJdSa5/G15SV8dlO/X0v7pwM2HN3eU+neamzsL9Ffze84rMnwIhhoT//bHscc2EGK/44G2ufexIF2M8UW5TwSx47xD5+h82uPmJ9rrFAeo/AgwAD8gNFBSSFsJ/6zoWdgd734qNzyqKFb3fTi/XBrLa0plPSsdAPXj1+G0CKhCRuDE0NkjrpHQqzk2p/b1DKZIbEsNTNsylqQCJLXN6CEe9QtRA/uzfUIPecWokYMCNP3p81i4GabWmaDTTJwtcpAKTNQTostT/DmIvEwLyS2gZDREpuVQhaAYcjFVminiU6cqqATw8S7NqkVd+a6LnZIJRsjJ95u6yBolxWA7nec0ggMFEOuqdqzGq+M6OP+0gL2Das1aTU85DYnNwLvWVP/wTpK++QOsMKpmHvcj31ZJIiIWaoH774r7z5Ed++DuyCvqy+G4XqDs6Ls
*/