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
o0lSbL+sjA/2Dk+5Meq196NjDu164Z5nW1zaf+G+rpFPdLztkg8LW237dtGRGxpMntr7xY4hNVZ/6aw/o3PBT7Ne3dLrxVXNR5/Ja/q/+LhZ7X5OHhW35dOlLyzel/rtudvfKqmfPDtqZWmbhNSCF16r/dbOJ8+8t7nn+sa1b3m2c69eg/ZHP7Hv8ilx216b/d35P7u8P/OpmQv2zBwf9tgw18OpH99au1WT53tNHDuw19bideMW7dk4bnat5Mnu1xuHPd8ntfsbCxs1GXTgi25DRtSOevirWvV+Ov3PmfNeqvXLf84tC5sx4e5WexuvPdK215cHg9r3jFo59s4f/ltwZFiMwRmkGHQf/puE/ocf+HuE6fc+wu+9jdOFPtX5EMg4q/MhYLhV50NAT3U+BFxenQ+BjLM6HwJ6LrbzQpcXQPdU54sg46ngfBG+wv9CyddQ4fksfpk///J9H4RvPDQ8+exrbVr0rrNoy8lHn44fP67eO0tDOjy0+p9rQdF3o3uvKXWd/c11Z6tPu7ZPDG/3YNy6Br//cWDUD9dd63zq6Y/vGp+44uCMZm3OvxQ2+u3Jfd48eyZqVfPXv33h7sy/cuffl7zk2KTwF2b90TL3mw2f3PHzU3EpTVIiNr/0ddcDKcea/PZq5oefv1onbvnoW9uHpE97ek3nVTN+mpPmfLnuhsOJg3f/FNzsyaVHfoqOezzlnxu+7nHn
*/