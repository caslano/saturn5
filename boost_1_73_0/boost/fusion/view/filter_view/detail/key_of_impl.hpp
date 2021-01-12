/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
xQzORbN3rSaOEAMQqpT7Vj/Z1X3qKydFbqml6izS8noZemqRp2/IPOH0Z6jOIBNLPaKTzn8u9ZgjRwVGihxLkZ7ubA32jwKLXr/Ci/xOg1WeIo4d+5gYT6rQTotUy51xqzluL1cAlttLWNrw3cYuodWYghIE+Pcsm1dxPky+4FeEKSq2g3ZYd1HS1zcu8b6bhfAPRQqvFwtybL+rxKeBXTgp5t/At/2OGAsiUQ4XTg8Mo3mS
*/