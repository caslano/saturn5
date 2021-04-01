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
Y2XpnlNomwFSh+vZD65L2b6RDo5MZNT4SzXt1tKnilAatZBYd0e65qvhfJJKfvD6TQrMcekTgAXZ7Haxm2iyGPaMEJnCNNReai5Mk5BwGxyxn8TCGl82vFN9Kv3qLoNEKDu44lsWrVLwOu7cwGFz9YgCcANtuBFG9TrTZ2f/Qn8spMMOTmjp8PEw8mpRPxI65WTaQtVK+QttkxSYVmBiN2WBiXdqC0ObrrvRkK5EIPDjdzS1/UpF49jacFajOJQ87mmOo9PJ4/zzrH50auFSCCAgvp7dIuJofwIggAZe17bI8rBVxXsq1nRKlDOxY9x+TtXJzAUgjiWkodw6u7V1z4Fi6jnw5Ju7I92VkDKkE3gqt3Y1eMF3I3RTa3nb5z8cM2Uv/SS0bb+mvkYXkjnECoiJS27ymwPQkXi/Y4sA3xh4/LpgGIxVLWH8VoXWuiCheuPWB8EJuAnldWJPzbet94VJRibrZR74V/spTwHroC0cUyG2tuDH0l+jbkPAaAwKgf75z0OCw2wODj9kiCm3WGKt3uu8bYTNdMP1cqWR1vQ75Yqc6HOo/rr2EA==
*/