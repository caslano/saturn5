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
utKB10hV6bQpf5+G4qeFalPBZoBFwZaAHQE7CuZG8Wdtin+npR/5wuOD5T9WnEfW8iSqdVUVi+sqI/MX1fOQVxY/O5RGfG8oVV5PTJrqJCWBByW7Sxq+DFvSeEOqJKhIzZ5YyVLK0O0pVWCmVOcMlVK8JEfWSFYF9kOwlWBPgz0LFtAVy9MVc5N69pihVkvfa3NpiKJJUu8yo4e2KJYLxXLFHTaDrQZzc9f22IHj3XTtuuDNiia7azOK0FNl2LY=
*/