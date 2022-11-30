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
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
*/