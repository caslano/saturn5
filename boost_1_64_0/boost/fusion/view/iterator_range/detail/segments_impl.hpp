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
rsEvNeokFdiCJAlYI2RbnccY70m7fAWLIj821xzdSG41j/dsaxtIXjELSpHkITTE1BBvdH7wUZc3hy4roc94aZrEsG4OMea1rdsXSH4BS9NExEkcYX7mPFmfGdO8vkvzSn3BheR+ndfgSn+EPkqPxX1ZyiOKUkSy9JnzOmmL57e0DRNVZJkflcx9tdTuG+E7xS7P2YxnMU99VRdtH9vAw3eKn0/3mULhBT4PmRMxr1WuB7k8JYviIPDyjJFAerZcqLMuj58yIbg+PMmnvtEHrfGKeo8V94KAn4xJGMlShYI1zXnFt4FzQJdPsUT6Io7TnOEKzrwkTnX+OsnLY6kUMbSKZGTJivq7gec2Db4yiTKeeskks30nt0kZP+3yFQwGPxelH1XZDRZRA0l8NNpv3MuyIgwV8jj6jvv83220oSjCPC+ikJGwj8iJ5fsl7W8lggQ0MXHYULNwLP+Z5BUy7gfAxhWbElKxaQcWzlPekgdJbuxvO4Sx5cU3QwlvwHhUellSKqewpEVxD53w+TAQPBmLIGrwYaviuuQ89VmErgsVjFF6M4bajy3KEwdREPpKODzaIYvuvd4k5eOMg3IVUdpk0pGuW/3+/kbdyijySl8GrHk9p3HG94UGX6J4mAeRdPiu9fcGmzcab2p+t9F/uZeGUcTrPrhaB/bu7ujdvWb//ZLweizMRBlnUeE+Ojyt3//eKGsqIhGXcciabkWNN3SPMfqGLs9DX8Y+I5HjGzwnKE+WhWmQZPbNYsqD62KX51yWSK5kVmkX9rY7vhnNoygiFSVRwsjsrzHmFKPfT5mVofChMZztpqbNwzhuhDdhZuqSJQXlRRPWOoO6xRq2L81KFWU5a2xPNu8bfLpR5kT5MpUNPrNzoP2u6Jj9LqNjPQj8IhQFre94t7vWGEu/JHwRU2FZxn6YsdZWKPYj8nY8yhvmKvFyKO+0MLA1L9omj5ZXhjxOPMkbvJgpxqwhfIKlHgz8WJbsgLCydr6Hb2y7/CVkG0ghhFdVl35vh761USTPkvl+JGRkjdRB1/JpuW8RGRnzPeF53I+pjDY/2h+v8c33c5GlguNjwLTsA5yfefStb5lGSVnPz4jFcs/NaRtxWcZCJIoRr8KGHfitR+x4mELdykIx6qXZiA/n0zldHIItTkPm3jBvxqo75pNzdj8TsuQJw8Ve6xvoN76B0HMJGGC2tqOHgzM66Lg4S/hCJlJ9JzFmU6Jq45wQ/SL8xreiKKXwEmTGNVPjG7PlN8744hhy5Sny0TUaw30El+8sz9NYFV5muAZw2dyWb3XR6qLf6Kuw4EWqNENt0rQu0776NO2rMuKizGTB3CjNzXe9v9qoj4TBKsKcbdDqtHx3bjf6LAq8QpRlMmG8gA3o9tlvCR9nUgS5lwYha4duaM3jOwGdhxQqFlnhGdYmG879Azr3D3IRJ0XCSFSKRkzRJ7o8ksmwjAPhl2xyQ7WhhwHVwyQGIxuAIk5x422emytap0xKoZLSM6x8xeuqCz4G28L5GK0TlC/LFc8NTxgQFuS5TvMp4kIv2gPNc2Db3aL5JDIt/Dg2PK22w3UtzQfMi1RpLAzPMq0PtvdXXZ6zcegHeRBKtr27c4Ws5/A7GlCdLfKoSOLMY42rqc05yi9pfXjCUx01nJGdo4av0Z8Dqud5mXtBIGLWCslIdWKB03lCVJYqlQFnU8Oj0nZ/Im+sX6Iiz2QyYZ1MTG6gDnL6nS99mWaFKNi0kION7/wlwusz7U0EneCzZljJRtsMG3xBlhcFFxkjIVXbfG/ljbmXkEEYRilruPHb/sN7SZze9wt5yrX7y8S7v/E9bpQvVUmswihkzevbjbnvd2k+UZYUWZA=
*/