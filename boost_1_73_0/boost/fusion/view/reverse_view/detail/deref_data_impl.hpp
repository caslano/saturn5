/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<reverse_view_iterator_tag>
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
iEa60bTLMprWjZB7OUa/j4o09Bq9/e0aqpwzvjpUpc8I1md7noGW3swp+r3hGOoT3+avpzXc8TcNxkZNs8iX9LRLAAO/5PLC/LChIG3Nv3iZmqanPDTf/qj43nrSaK5+fIegL3La6csKGhyLRFu8iqCtg2byOXcDRTuM5U5PjaIgrhof5dEb1jTMghTf0fnlxUGf+zC9Gym6YlPhYT3M/hYe3Ohf02+q6McuIm7yb2Y3U7R6
*/