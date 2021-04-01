/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
plinvZXlddhQhjZqxBCrCcYNPCxtKInv0f8U+YgezlW+1L+BdBM26ExD/v9aPthh4sMp38Rx0Ms0Ujo+4u1412VN9E2XE2Rbl3mjKDT92zKnNtN5TYSFdeV2Bd3lv+kMbibUXoo+qcdzc4X70ZS4p5jnfJAXhG76jeeL4lM5tMNkr8ZedANMEJGA5yA/uqetvHCpmy+W5C497P3kC+PSQXSwJZVIDLoPISj9pGtNVV8HcfwOdqm17c1Hkn319NV9u72xixYcY7IPMjYYeyvDeKo9YvXogm0bYBLt489YQ7UTkV1KARtEITW6hisK4FBPLHVG6aRiSVCk59HBISIsEs9NpgTCXbcuUvxgJf2tGqGzuU0qCvX3wue5LK39kmrUMFDGFeX+TB8Z4nn1FRQ1/PjmYBM5joEaC+rIkMNmGBzLyXNfd8bYcfSEXwkHlpKuhc8kh1W6LVyJKB8jmJm1UmGxK+1RKIg9m+A1roGotjRwT7H+8D3uOg8pLWhXNNDCmUCxqZ/XUZub0Q9/bO/c5QWeqIlfmTGmfdc4wV+WVWx5Jx41lB4unZU6jw==
*/