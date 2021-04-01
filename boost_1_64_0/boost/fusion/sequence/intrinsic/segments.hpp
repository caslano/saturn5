/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTS_04052005_1141)
#define BOOST_FUSION_SEGMENTS_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    // segments: returns a sequence of sequences
    namespace extension
    {
        template <typename Tag>
        struct segments_impl
        {
            template <typename Sequence>
            struct apply {};
        };

        template <>
        struct segments_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template segments<Sequence> {};
        }; 

        template <>
        struct segments_impl<iterator_range_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct segments
        {
            typedef typename traits::tag_of<Sequence>::type tag_type;

            typedef typename
                extension::segments_impl<tag_type>::template apply<Sequence>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segments<Sequence>
        >::type
    segments(Sequence& seq)
    {
        typedef typename traits::tag_of<Sequence>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq)
    {
        typedef typename traits::tag_of<Sequence const>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence const>::call(seq);
    }
}}

#endif

/* segments.hpp
AXB27+vNp6ndZS/hdMtR2Ld9u9fnQCFqHs1H5uUl6kvq2/DDWnUlXb52qGZkDU6VR5zq1x1c4C3coA7ipbOdhaIUQmLDkIYY6iJOQPqKCZyZfrWtq+YHUdwHHE2dzsaafz7Yug9rQuv99cWiEJge+uij0nRhIHZ5+mtuFg6cUtbI+SXvua7F/HTP7cKpNjfF6yL6GOkK/Nvw/CQBsA92k9BkdIqVWkqPIUfQ0bKL6kHBZp1vX9Pc0SiMQJ2G89p91LeSaL9cMSWAIGSyC2IfMDt2XR5nJ7u6Roo9b4vITm1kIKaMW2x2npNsI86mYiw/393umO8SYMqxTS+5c69/W8B4f7K4JbfTYEUmTnIbtUAMVTjaJ/Ij3H9pYIz6vt1QTJK2/4c43jzhUUPob5CUhgaB1V5zQul3YHXkCk6QF1e3aM1DyeXwiTqyhlIKw6aKPHpJ+EvWa8Z9JIpTlJeimetgZRHzRPHbf5r9yivIcoUDE3ZCuUm5O4ydwbUCm4gbv1jfVQulhv9IxxNAavlW3iuABtj0/3ERynqNNLFzwj+DxHmK+s/YKqDyGA==
*/