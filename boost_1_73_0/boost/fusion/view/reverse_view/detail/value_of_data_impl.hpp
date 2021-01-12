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
B/WaEtTXNQV7PYb8reC3jVXL2NG138jLVFmOh9fC/bREWzu2Mag7ctR7I3T3+CQVDkpyOjFB+94oy4bdSuy1Yoc0mG/6YFWMVk3UcverWTH3wy6KPEUWZroJ3td0Gx8VdLLcYVZCWZt9BOeHraNImYdxz8r6h4cr0IvS6WFMLrQYlaXdutpVtCxvZ6/msgIVTFngpcw87NgQ8gSZTQm5QQn9bH8Tt0f4l5MsTx2MoQ9VWm7q
*/