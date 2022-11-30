/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct segment_sequence_tag {};

    // Here, Sequence is a sequence of ranges (which may or may not be
    // segmented).
    template<typename Sequence>
    struct segment_sequence
        : sequence_base<segment_sequence<Sequence> >
    {
        typedef fusion_sequence_tag tag;
        typedef segment_sequence_tag fusion_tag;
        typedef typename Sequence::is_view is_view;
        typedef typename Sequence::category category;
        typedef Sequence sequence_type;
        sequence_type sequence;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED explicit segment_sequence(Sequence const & seq)
            : sequence(seq)
        {}
    };
}

namespace extension
{
    template<typename Tag>
    struct is_segmented_impl;

    template<>
    struct is_segmented_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
            : mpl::true_
        {};
    };

    template<typename Tag>
    struct segments_impl;

    template<>
    struct segments_impl<detail::segment_sequence_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename Sequence::sequence_type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence & seq)
            {
                return seq.sequence;
            }
        };
    };
}}}

#endif

/* segment_sequence.hpp
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
*/