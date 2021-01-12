/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_10022005_1620)
#define FUSION_BACK_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/back.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct back_impl;

    template <>
    struct back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<
                typename fusion::result_of::prior<
                    typename fusion::result_of::end<Sequence>::type
                >::type> {};
    };
}}

#endif

/* back.hpp
3d8//bub5z/3zBOXLNrU/PbDX91SdEbjndNvKN5b09Gw8IqvH762o/DyCelXvx2af8MvFp71zye+tGdfOHJ4y+9G/31HYseaP8S//9qfPvncWSsuXj0nct+r188tSnuh4ceHXvj50dzfPf7zfXtvn3n41J+N3LP+F29O+u2/6t7527aPtv1y+4n/2hc9N3jHwY/vyHv6+n8fnf/+lH8l/erNn2T97ObHP3/j8kOPH/p5Q/dT
*/