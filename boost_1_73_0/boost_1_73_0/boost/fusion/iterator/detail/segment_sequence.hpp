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
ozoaz4Q2aLAyQsl99M3B8HKiyQa5TwqtILlNRJGM0FFiIDdmqn9rt9OqLBB9O1OpbqeL8PdzM3mI5ApBTJIZqKkBo6DS3AGSdGCiMjGmFROCxGk1KoTOnSUadCWztipB86IgW6gnuJ7D5jCo0+OQGEwRsTC0aCU1ubrL1WRNEPNIVsZVKdER5gGFMoVpdqDCQ1RaYRv5wkWdU5vg75ZmiTcDJREM7LgD6A12YJRooR340Iu70TCGD26/74bxFURn4IZXZOx9L/Sw9AKdlcDvpyXX6LwEMZkWgme1z1/3tBuNXSHToso47GDxssQk+/nOCpFKypIsK4UcK2Ihbz5i5hOkN3BPA58mSQMHiW170shUvtfEDtOqwE5LQCYTjsUW8gY81YU9Lxw8V7e8fN6N48tBcx96ZiGta3HbbljJkhusEFGfdVbBQOsZ3GGmbGWISLkiRjlJbOeiAYwPi1HhZNlQfQC5yuaJnkGLcuA0fjzBsPWkNpDmSQmtXGlDgJ9UEhIbUpXmfwm27hJhps2TRoMSnSosxgI0E5rVycp+MoBVrUxqxqUpUbWFe3JJAB683XCjVfpl4QlDlziryQu06AseYBIlGW4YIqedNWNmU06twmU1gX8REl040Xun3mETsFPXY4F76gcOwWq3
*/