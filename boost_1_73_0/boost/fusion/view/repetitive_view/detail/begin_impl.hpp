/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::begin<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq);
                }
            };
        };

    }

}}

#endif


/* begin_impl.hpp
9x4WwoNFlpYV1vSNY6vKcuj7dyL1vb+8AO+KV9D3mx+i78ihydvxJfp+AGsrfDJ5uPqDFe0I3GqzxS5/0D/WB53n4ZiirywM+0OUmPbQH3hn2gcfDJbWhzp64Kaafmp/l77YB//KiTHCfPBetM/+UMzvF+bXFhsxhKlGYRaHK2u1ben9/I+MtRjocNBXFd1bGPTnlzdWuc0//q1y3VH5eKkvDy54b17Fq7z8Km38zL1cxJ/p
*/