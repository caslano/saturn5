/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, (Sequence::next_down::value + 1)>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
2PCnd3Gscmdfh5wfg2W4sBqSzNXKb5Mdfn1yVBOpm6P7eFnYfad+YKqlajVmKYh6GYj6liAaZaNobAtgDJnpkJMimmurYWq/0jv9EIMyJWFLhzMYdvpDTmvS9dvQTLsHpx0PWVNAkLc7sfJztbxdZZTC2TEce/CZqkkSg++hqYsa/kQ0dKT6PDZDuNHq3afGgKKCWaneCmFVQDfVYwP7hIHtdboI5uuKbGCWGAzUe772WlbZRknvJcFAnOyKsFiKEJrDrizeGg6dIx5PQ9fwg3dg4+BI4ikJZ/JlffiYMiSwMZw//y5SsbKm2pqkyErWUN4v50ieq5MkEWjJXAQGDHWU6LFSUWQYriKZz2KPG8GxIC9IjBqI+RLRk2kly0z2jRcZkqM2AC2G/p9TeiOFAji/uT4XuaZ9ZeQtvmn7o9awc+47XjV7vT6x9q5XkmCl+JwzrjgeN4k5cDwf+81hu/+l53j1gX3Qh81Lf+wP3SOofD/0W/DJcb7wEQVZfKNxmSUAazWBwc+7POwiY+mtIQwWl/eS/UjvEXkqVUjaNT6cilVU1c4kFpprNF+HLFBWnu6UueN4EWExLKVwZhio7S4dNtka8M44dSiKe8WO1WLhWmqle3X3qsikAiCTKPYP025Hz3i7/qWoy1Oz
*/