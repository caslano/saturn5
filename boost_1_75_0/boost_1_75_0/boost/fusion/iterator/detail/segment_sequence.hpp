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
wxljxjmcdq04CJTTAcMnRtDZt02q+rWZznQTpKqImaUx24UzWF71KPsjxZoXjz6mu02m4upDFaPlhXtAkJ/mkmpMZSH1qrJQ+/zlvcpcoYIJy3viRa/0/PalSa5QXao3pFpyjz70flFk3LUg2jhm5Sy7IncWhger74vkeBikEqseXodW7nKXcsajfFmtSY9jngaP43MpQmDVh0CuujmSvhrEwG6u0IWrltwHL6yDFqxZiu2YsLybVFOL71/SW8P4BTlUZ0H46lD7VUuPgaB3E5w+Vo+QF74LnL2bl7Q1vsjgyX7lQJG0Lb0H8jwYhXSzP+K1eBHqVUVfJ5A7o+PgIZ0l+iLJ2/NTTVtgGkxUD/SAJXpgMyrnchuprNu62w3SU/lmQqyocyt11lNua7Pf2u44E+uq9NgwRB2CEeCKySXPlXuBX9K3gkYpek3hipylvZSjgmq/pxwIFW7xAEyLWVlwNLPI4Vl2Z5UW6InayW4uwvH62qybYBZhYFGgE6I8Tv2qPjz1V/Zh/ROlapmBm9qTz1tBCvOm8b4oW7fjNgj/CtzrvXBGc8G6mJEDW2Qebo1W9/rutDN2AAIs/dPOaYz8ra0et2OZtuP96oSaON9dQ/dv7KWDno/tpb8/Qws8U2ln9x1rDbnvZOLFAt5QW9+IbahNpxM31K5z3jZR8AiwYRfUDovyeHBEZJa5cG7e0t65c/OwhRV4MlqI
*/