/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_09162005_0335)
#define FUSION_EMPTY_09162005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct mpl_sequence_tag; // mpl sequence tag

    namespace extension
    {
        template <typename Tag>
        struct empty_impl
        {
            template <typename Sequence>
            struct apply 
                : mpl::bool_<(result_of::size<Sequence>::value == 0)>
            {};
        };

        template <>
        struct empty_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template empty<Sequence> {};
        };

        template <>
        struct empty_impl<mpl_sequence_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct empty 
            : extension::empty_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        typedef typename result_of::empty<Sequence>::type result;
        return result();
    }
}}

#endif

/* empty.hpp
l7nEV8CuLtbbo7VkH3br5asL8a2kqgzk5UsjEH+9uYafV+QvP5GXX11/Q/5Gbl69+uHij4svIC7rp4v/A1BLAwQKAAAACAAtZ0pSFJ0nY2kCAAAmBQAAHQAJAGN1cmwtbWFzdGVyL2xpYi9lYXN5b3B0aW9ucy5oVVQFAAG2SCRgrVRdb9owFH3nVxyNl7bKmq5P61pVo8BatAoqPlShdYpMcoO9BTuyHT6k/vhdB1hXaRsvNQI7zj3n3HuuTVPlOqMcd91WpztM2pPhfdJtjaaDh3Fv0B8ld40mv1aa/hMRn7zdaOAEB0dSfxMePNeIB2t+UOr/Hp0kz9h+GPXE8yGRGC+Q5+QYhyHPOKohyU7lKqyT5JDQU8gt/MQB+ZSEJe8wLCDbptxYNZceR+1jfLi4+Ij3OD87P4vQEVpRgZEnPSM7j3CV1TufpVivTx1dRyAPUZzuqMZSOTiT+5WwBF4XKiXtKINwyMilVs34QWl4SchVQWgPHqa9/m2ElVSpDCQbU8FJUxUZpFgSLKWklluOUlgPkzOcyTPlPBNWXhl9ytoET3bhAkeQF4UzEEuhCjFjIeEhvS/dpzhOK1tw9nFmUhen+/JPpV/8rmTKSSzEBqb08AaVowghMsLCZCoPMxvCm2U1K5ST0Us2
*/