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