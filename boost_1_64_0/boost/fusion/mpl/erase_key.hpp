/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1907)
#define FUSION_ERASE_KEY_10022005_1907

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_key_impl;

    template <>
    struct erase_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply
        {
            typedef typename
                fusion::result_of::erase_key<Sequence, Key>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase_key.hpp
vnGvT16vnln9wuaUUKmZzsVGbF0FQHiTaDnDatssOp6BM9SGT+UPboCu0RYgdCwGmfyEg7ONJvlaw9AxTOgyW6/5cOAFfNJ57s0P3rH6KG/RLnX7ksoIsflMRl/aTJfgPqJUbBvqnQNKNO2flLjLaP/O0quxOtEZ9/LyZJqKR4D9BN5Mg0ZSHqXnu6OFVqXfXLtCejyve1SnVadLAFKeGESXgpYD2FrFTcImpKwq518btIfUFdubyNMf+o7XjZJnjxBHzGPs/wPPSiBlFKZkaKGfw2yryBELCoOiG9uL1e1LAph9bnxI0xkoKIY9u0I7Vfy8WsclkMKx9gn7rmFQm/4L8+i9wjNn03bSqpNE4kN5nhvzdCCC4kZqFyC4yIPs3Gu8F8z+zWwIerfC5CSkAys0CvX6przUy6ugwSScrrvUp7e8chBi8K1XfNJoX5t2U92/8NHlLOn9vXasZnLHYRaVZbHTAN5LgOtdG706nO+UNk6qLdUl6vGX0TTIUpo20m8vgndWxn3yfF7gu18GFEaqlwcWLvPsto1OLOo+mkrRS3Re11yqgt2YaA==
*/