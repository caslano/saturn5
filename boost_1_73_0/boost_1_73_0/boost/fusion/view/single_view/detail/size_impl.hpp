/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM)
#define FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM

namespace boost { namespace fusion
{
    struct single_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef mpl::int_<1> type;
            };
        };
    }
}}

#endif



/* size_impl.hpp
Eu6x7gRcGVR9k+fpBO7Z5SO3q0TLmcg97EjF6Bk1x7L0nElazkQtp5R7+oqcG4Gntuk593LPdpJTquVM5h52x4ad486mPd9LzynjnjI/+Tdwk7Wccu5hd0ebG0tTX86t1XP4XvDJ8jOvgE3KnlPBPewIzH4yPflm87mSe14FeV6u0HKmml1gzsPfBlyp1nOquOcgyZmq5VRzj3q+sOfUcA+93qjWcqbVI2c695wA+XyfpuXM4J44kRNz/csoPac=
*/