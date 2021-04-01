/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : extension::struct_assoc_key<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* key_of_impl.hpp
97pZwmhZOHkyyhJU1OyO9igsQgmnzHPrKkNG5V9TjkgGa1WM85eA3mVTARA//L8IorWm6gwkuntqh/lJkgeV/4axVEueRrEa+RWWAcE2lCjt3UohJivg1e/tcWqnWejLrw+qLah0WjCDReq7xGbd/Nb4thyXAMAPy0jB070sCe4/G3m3frgxaD1pdWSadDCr6SjmKLaOvjK/eWt7CY7ArEZWezomX8w76Kw7V7nj0i6tFQuS20bHYgHzYsQPEbA/JJM9rmQ4ZjlxUKbvD2GWG5MDt3UJHkFzUxLor4tP4BjjqlTTCyKAKCpzuF1G/jpWLxr1w/3OCLoZtkKAzk6+6IqzMXHm+98jCAV80aXrW3CjEoPEvZQuIy/84ZZ1o5s2loKuLkg3AGI9x6BQ8U5lshvCLHOu57TU+YmtcQeFiZoywJrXypjyfJHBgez+ndNCQvwRVJBjYe8VnD0P0adsjAjW6gz8CCl28ZL1ceYngyPgZvd6lDOd3mF9VFZc3fOfTRX4A7BOIpHprYbTs9rvHpWT/1JSngKeE1ApsCywxUEj2fwZ0QbqUQRtqg==
*/