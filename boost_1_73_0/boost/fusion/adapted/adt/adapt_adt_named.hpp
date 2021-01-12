/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                        \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ADT_AS_VIEW(                                             \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ADT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)            \
   BOOST_FUSION_ADAPT_ADT_NAMED_NS(                                             \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_adt_named.hpp
gWfBj+Fi+Am8GH4KfwU/g1fCz+G18Av4a/glXAv3wjvg1/Ae+Be4Hu6DD8Jv4Cb4LXwcfgf/BP8Kn4d/gy/B7+FO+AN8E/4IP4A/wU/gz/BLaDnvdwfwB+iDP8N6kHOWHwZhECbBejACE2AqDMMs1WfDRNgIJsFmqnfSc5Vpe9Je1vRMRZYh/OR7Cz7YCGbADlof7gTXwi7wRdgbvgX7wg9gP/hXOAj68HcwrA+HwDTYEzaF
*/