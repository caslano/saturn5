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
AjwfJ/TE35ez4OSIRT14Kr6sy2DOdOdmzL2IDfp/BcedK5L4jBxasTaL4SrQPCX2jYa/yEFX8lwy3ggf23ywTlA1xZnelKT3z0GAbSnx5uGI3PsEtKKceLeoc+QTL8/oYm9cOxgF1xZxNuWQzWWE8U/bh0eq3KuyuucvhxqjlxkvG4Ek/n88GD/EEcwqOSRk+N5QJ3L8rcTg4vMz47A0GvwTSTPWc8OoWFvnal1HaKCqPeRnPBDhu6+uyyXueT3cn8oNU9Zd8xmPTWi1ep1EVyX0rgfJKOcnBI+0pr09hO3Qo0yS1S+faEc1ENpsZhZJPuAF3HXYg2bYsBjAs+R44VjmT/EbEvwxhlheE/0BGapKF1Ua78aEpVQlEjLcwhvwmnzEUiCADT+ct/vNIBaVI5dO9qvm1cXMD6beC/86FQM6Y3drtZ3+iYBxng7x6ieX08XP2hioG1Q4tpU7N/fInGiYoOeZloTrWrDspDHmtCanzO6loSdcZuuduFa+VLaGY/ECuprDgN2VnvhokKWFIlfPj6qpHae20fzO2Z+WXmYlgUx3i8ib1tL1fw==
*/