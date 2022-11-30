/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_SEGMENTS_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SEGMENTS_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/sequence/intrinsic/segments.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/view/iterator_range/detail/segmented_iterator_range.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct segments_impl;

        template <>
        struct segments_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef
                    detail::make_segmented_range<
                        typename Sequence::begin_type
                      , typename Sequence::end_type
                    >
                impl;

                BOOST_MPL_ASSERT((traits::is_segmented<typename impl::type>));

                typedef
                    typename result_of::segments<typename impl::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence & seq)
                {
                    return fusion::segments(impl::call(seq.first, seq.last));
                }
            };
        };
    }
}}

#endif

/* segments_impl.hpp
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
*/