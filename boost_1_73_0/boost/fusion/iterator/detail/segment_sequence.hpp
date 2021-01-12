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
osaOxsfae12nLjBP7ze/ZBhnL9lu42iP9e5W/56zZIJxstT1wXF+7wH7N9Z1LGS/nO4+07pq7nPOpwbzlevS9iafxzi+O093ff2751/meL5j3vyXecF+XPUv2219uHzY87oerZxtXr/TuGlwPa7wPr5i/fJL65Jl5t/t9ts3fd/jnv9a+3Xi2HFDlPWm/TunyHUsy7z5qOO7wnX/qPu5eNvjfH9vh/Ey2/XSunxtgn8fneE+
*/