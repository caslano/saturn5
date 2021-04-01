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
6rcvCQRxdDI8M6ks2wBgfRz1kBAuuQPs9BBw7jN6KKNCjz6l31Gc+ybwOylIBIEHN8ML1yKHzm8Cb+VZwS8yXAi1QDMKjdwqx2sU/XyQ7gaWhBHb2PZZvTkVfZ8yGSHn2SWEbLE8LKBA6dJi8nuthJyBYHJoEe9mZJEl8CsFNWWER3HHOVGmBBpzkaulAt4b78dxVksNbL9/Q0TVrIN3b0ECI/vIhi7jw0jfEvNwFgYJmAn7q7ItvsAPXjMIL+xsPiFzt4cKsj9i4MLkqy43en22CUfadHe+E0BdpFfZgtPfpuPHbWpijA//et7WNFzIv9OA0hvvGoCd2FfZwRxiPIvIqSLY5E1jVSRYiuXIO6ekNV35hxjxBGRCHZXKxLXn/ql1cVjP2TIiuWGGOOjoZoE9cuKchwbf+Zg4vbOU5jFGNnneUoLGBVI+O7p5qYky8FESROKGLh7Uyopy4Jd9ONmWsybJKZb902wSSNz14FmCk0NK6CuGObDo05k8F80w8IdGnWow0Mh/OmIr4PBd747mX2BYoNxFMorlbSqcMtvVp/rfVDGjsb3YfA==
*/