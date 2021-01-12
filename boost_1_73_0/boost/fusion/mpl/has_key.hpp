/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_10022005_1617)
#define FUSION_HAS_KEY_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct has_key_impl;

    template <>
    struct has_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply : fusion::result_of::has_key<Sequence, Key> {};
    };
}}

#endif


/* has_key.hpp
I1rQhh70YwijiP4i7UUyQihECcpRhVo0oBkRdKAbfRhBMI32Ih6pyEA2wshHGSpRg3o0oR1dGEDMXPociUhBFnJQigrUoREt6MEQor9EPyMByUhDJkLIRQnKUYVaNKAZEfRhECMIfpm2Ix5JyEA28lGMGtSjCa3owjDi0mkvUpCOHOShCBWoRh0a0YI29GMIo4idR9uRjEyEkIsSlKMBzYigD4MIzqedSEIGshFGPspQiSa0
*/