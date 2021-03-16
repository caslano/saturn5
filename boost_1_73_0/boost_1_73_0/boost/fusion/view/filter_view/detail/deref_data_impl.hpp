/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
GzsUfTuHzEZV252OcXFwJ6ZeM4TF7YWHE09fZmutQmIMgcfQl1M03Cw8RAE0bcPhnS4qbzyBytyvGR0ouXWYQN/mas4RLS68O+i7ZVpnnY+RRBFtX9+2/r5e7aXm+dW/tTPC3STremc/SV8mhfs9x2SZZhdlxlM71Y/IMudclOGOT3Vua8enVQDt/lsBdHKkMRDHWNZVAH21oJkyyf0cwTUG0ddytK4RQJtEAO0ULOP0GIJl7pxFK+nisoqKPRQ=
*/