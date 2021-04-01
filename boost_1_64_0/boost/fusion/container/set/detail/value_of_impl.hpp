/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename It::seq_type::storage_type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
5JkpvThnkslem2erkIH2V2N7eWJc/sw76niv4bXCaF0trlsEgTlEqkNPLQeKWJGYQNpk2RFR0c4bIBKVLD5gAx9OUAwRQtAKkgxXPoHP9k33gcdkJ4ZTeYqUWoa6oZUW85hYsXU59pv/SwrX7fZ7Udnw4rwyfY1JBZWwym2mebgDAeQfQTUjf5zxFaOOkYQNO7AxIiQzHiN2lvZR1lHop5AGfngdLcX1XYqi2DB7sv82KIxmuvVNLDTKVOxI4hhkWt7/umqtvJasrBgtwdXr+gCsOW+9Dd0BaMzJgZWnjDgUUo6KlxPMNyXBte/OUKXdtUlRwZ6aTafKS25ziVfwVYzy1l3NTGp/Hs/AYppXWowVT0ruetIrB1OYMydyy7YRquhRvL8Z/BAz1ug8wnPl9nyBKIjoDkHKP2JlFJJXdYt4tmxX4iDe3wsWZM/1/+QN7awnGs0FhqRo9Px/3e1h5UjmGiPt4myzfKCTpY1NmDmUXLS7IpUpZJWoGZIEwDCqS6fYpEogBRLNqAr2JDoKmLj7mkBjRnqJP5hOXA7Qf0bYhXbcY2x5TEDpZA==
*/