/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT(                                         \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_TPL_STRUCT(                                              \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)             \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT(                                                  \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_struct.hpp
UmXqdNB78eEVaf3ntf55HrTeXNsUlGB246C1OA5a7+0etreNrKJEbklacs9DS3KfgvIcR6Etk4Loc0VVCn+25eJ0cY/wqoO7WCamVu3bYefaEoZY1GrHTX6eZUKa8WS/UZuKRghJUT3yNPHd5KU070atykhIqwVJs4RUi4gtmK4WGSarXRhhqGQrYJ4SflMtFpJkSbW4qyS4hR3XV61nn0sLq8CHRFHjySpSwhTTXtDaa8LetbldmduzPeOkvc97NrEUdTZuVcUh6F4qZbnMhKKlziDA/+sgMDerGA9aJKNlu3DhrNRb6Lku9ATBHrKf235rSz63rX4ubs1RBL5p8lVfD3Eqaol9iUadJxShSbKrjnVmp4C4W5DjsR1V48loOuqOBr5jzyMxJTovjiPWWWoTctOwjqdjPO6seCqIOU8ge++TdzYe9HDK0W+Od2Wnb4dthNqqurs95lle76PXH3iH/UF/eul4UVScT1+5Lw7c55Zg0pueT4bw0Ruc95wJRWDYEUw7781Gp2aGGvcV/dsA3mAtTnQF4fnwdDi6GM5GdhobJi50gb3m93rgDfwRnjUOJ/C9OQE1nBRNqMG94VntOf8DUEsDBAoAAAAIAC1nSlL0/xxywQQAAHUKAAAxAAkAY3VybC1tYXN0
*/