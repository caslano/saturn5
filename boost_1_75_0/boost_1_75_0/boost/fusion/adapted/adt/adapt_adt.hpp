/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>
#include <boost/fusion/adapted/adt/detail/extension.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_attr_filler.hpp>

#define BOOST_FUSION_ADAPT_ADT_C(                                               \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
        BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE),                      \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                 \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE), 4))         \

#define BOOST_FUSION_ADAPT_TPL_ADT(TEMPLATE_PARAMS_SEQ, NAME_SEQ , ATTRIBUTES)  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT(NAME, ATTRIBUTES)                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT_AS_VIEW(NAME, ATTRIBUTES)                        \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        1,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#endif

/* adapt_adt.hpp
c1FEUnS2WU8HT+cF/MkU8Uk6x3+egexUBQCCbQaxU+L46JOE45q8WoJAWkUtCMjczADw4weIANdj2znD9NVOILve12SE3/6w4h2XqRUfu5Bwotaay/uzWHfKb5UGgSlPiDtzhq+S7sj7reyFuwMxxmm5gAu7Vtv/o2ifr8ZPfwEzDhNrmVYG44f3s1bDdTgtR2xZVBYSkgx7mriJ9RdINSyrbRnwt30Hd4jIfxBDNWeWaf8tiRI3ZMETvnEfuUR1uglvoeCUrhWWRVnarhNksJXo7/se7BTlBXUIOCOm+jJTADJ920A1Fgf5qX22/MkIGWVoIBXIHyR44Vb5/d2+VRngQAXcY1naqOqC61M7PJFtf6cMDwi1nWKu276Ns2jlU8RV1WOokkLBaQWwQLxHqDf0O1FvJtTDWI5ULvtwHvsGwaFMGzUFwGEYgMPJT3RwqP5EB4cyBIfiVeomW1H7JivBYcH7eJPtgG0/8BpDJ4lR/vO+w5jxCfhUcXN9zRN8e41fooBk0Pyg+4zRBs1CV4e4RkpyjmJhU/qzc5h4Nd2lTWpCvsunIshhtgIH0SOZjT5QREas/54IPRum2NYN6xwWaZ2awbLR1LGzVSAftKteczVdjGdidx+yfTUxApEeXzf0iw/nO5T3tQSkHSOxMpqvUV9OrRkdw3SNjjCmilS5Y9PalmWwJkqqyPXc2a4IozuwKe456QBaRVgu
*/