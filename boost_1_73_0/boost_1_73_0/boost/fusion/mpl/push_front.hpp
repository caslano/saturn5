/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_10022005_1720)
#define FUSION_PUSH_FRONT_10022005_1720

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_front_impl;

    template <>
    struct push_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_front<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_front.hpp
hdR7Z3kjSR4bGevUe62PI0mtuhrv1KaCipx6v+Pxdm+/rdM8XG1FWXlgw8GKwIrBloO9ABY5jLPxuPc3jeR0UOH35l3FG3SG3puuSo/kdKbjntB7UzJt/BmP4XjS/BdGGcMxYzYtxefvNWbD97R3kDcuS/iIzc32iA192os5J7oeuNx2d7bdfA/b4x62l/swFGwE2AKwe8H2gu0HczRyqEZX6fSbq/o/NmJtyd3QZ1y3Bjn5LFaI4whxHCGGxw0=
*/