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
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
*/