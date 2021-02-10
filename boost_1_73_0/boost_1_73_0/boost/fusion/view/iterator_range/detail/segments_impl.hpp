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
utURrhZxuNGVurZI4xF8Zq8VeqZIWCGb3iLpKQrKLnEceOxplMsNvrxczPcy4B/qR3OCD7E8EX4YlMVd0i6MZzMzrYH4dgkRs9pgvVL25lzQCyweBHd9VAM+Nu6CftqDnTj/6HY+yUhuOOZEdqP1itYODwgQWvb6bPQIy4UKK7m6nWerKR/JJgt9Zd3gq/kAgR0e/ZO0O8xDCMLM9Wo8cYi0BBWikAcwk/CuSvPlAQX2w3IywxgCMk89htk/+Qb+C1vw7X2tuitF6jjsAaShwDxY3+UKBWHi4R8LScId3o9wXvA3zd83IlaGF0qQ/EdkE601x9bi4IPtYnIiafMhdxnUq9wP2B+wYKrQ3s10PL6WMh94mVmLvIRmKarhergsVxAojMP4+5/+KcTAHklu4ByQUOoCwcERbQ9A9iIpNqHDJcpRzd/14Ij6jIbN5n4jXuGmTo+p07PpbJT0mFQQjRaj8uKCJ9ZlTg7I1FQHtWAgcKy4hASdYaRRNEAnwQJ3KDtXQ7T8mn31Pryvlk2UAF/ip6bQc4PcntY9ZLxt5CN7W/8DUEsDBAoAAAAIAC1nSlIDlvPM8gkAAFYZAAAVAAkAY3VybC1tYXN0ZXIvbGliL2Z0cC5oVVQFAAG2SCRgrVltc9s2Ev7uX4Fz
*/