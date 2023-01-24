/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<typename remove_const<Seq>::type, N::value>
        {};
    };

    template <>
    struct value_at_impl<assoc_struct_tag>
      : value_at_impl<struct_tag>
    {};
}}}

#endif

/* value_at_impl.hpp
bygQY31cv/oMBXXmR7PlOek7s2mYf52vU2Yr/RuPGIYmHrE7NACP2A0uJ0czvEfQlUHYr+cUQP2uE5X48V+onc/rhu18F7XzS3+35vjxd54148d3lJjx4188QID6Fnp681IVPX0zuxSI5m0N8g5QTXE22rfy8Am9R9Tz2AWtNBPl96ymcTYoYZmxO13HxXwHwuNoGYANHKqArFOyWgnYtAa+29fPwKGGT9cBWDDLe1gW+QjvMcv9nufgEixZgoDfsireWTLP4fngnaD0PSqUfqrpeaFA6VuYwVMyaKpXRVM9TFqEII3Yw8vflX391bvUx5/wNfNDur79blCf4/KIT8Ah/sNm9nsW7g6dzCijULUM6P8DPNW6qFhB0u/6THszMglEoKUNRaDNFSgCj2BwqaP8aGsMA4FCxpuFFAYCP8R8pYjDQPDZ+6PsVtofjsyE5j1RQhgVMzU1SRH8QrC9K6I1wkTsKv4Qr2v4PREy7I+gx/CAUTxPe+HPFCqiT+4chuUrubpK2vw2srJa4Dz/ryh4mV1FRDkI62swwGR0CYuAQSJQcCGzgL+BBVwfzYqiUCO6awPM/yQbB54sghmvP6sdZEfNn1B00pbfApeN4hXIF7gXckWsNxliRwyzQgKZNxSZI8a+KQ5krG45UKm2eCYBQlrTPBzVrN7aSHYLWvXYJtaBgvBC9JjZ00LDfjssP0oGSjrsQgJoivZk
*/