/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::first_type
            type;
        };
    };
}}}

#endif

/* key_of_impl.hpp
eJzFgAE484SdjMbdDHUlH+d5Q+RJF3nctXtFlVNj3bVkv9021UmQJ6HFRnUEQ5mkud44V4cySU0CKIOzTXj3hgGaPjZM+XOb6S2A63wdrv0M15cE189tQuBaPVSHq7UZroqj0rQd7lSaDhTd7f9AgImIcyO6jq71lO8uShctlMsW3LVoUIz6b7Tzhsvcf9FO8GWLIVNL1MUF3YAtQbq2G7Bysh1xGUf7TNE+9fFezMTAo/seZNjvFbcHHgu050XHH4hbh23rgnhrFbpl5+pIzsS7OFSKx+ob0aft4yyNI6lCUfh85BbuRU5ioTFJYMWvcabeYiXyfvciO7PYyAXoEbwPpD7XgPEn2t5ym3k5RAbj0f0G2Z8SYnFYbAy7++D+sLUPbR4dUlmuJJVkP65huRL6/Dd/vnANfj5LgXKNrreYaPJnsWCm2dnRQbSFQXdYw6PF6nZ0h00x7rAp4iICssr+69j4xdXiPpvIyzVVq4IdBq/vD4B901S/nS4l9lUwGiQPnqJ/uStjy78qFqV3QWuDZGuNcfKqH+LmwpC037iPDH8W6G4u4P3zaqOfYXd7sR+yfUJlBbr+vHs6mW6bDl83BhLqPP2OP5LvUTqAXlQuvb51+OOEZlzXrsK3mT3gxnhf6TFr0QV6SgI93vFlEXubHDnRU7rZ0ViKjIwM6A06jEAUnIxGS1LFTe//Hfyjf48If8f/3+HXnY/3
*/