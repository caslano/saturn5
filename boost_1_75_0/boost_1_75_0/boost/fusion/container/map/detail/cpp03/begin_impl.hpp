/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
3f3pdtYcy4y08K7vHeLfKBVUZtyBGdkCqNJj7ZwzUoHBO88TaL0x5w9NmVNSuCzR4onepX0vNrlsZbvo/+aVrijiyOn79d2wX19AxJfMdG54Jng9CJJVRj1Th/BMoPsd/Cw0U8fwTIAlwcWhmc4Lz3QYprAyNFOn8Ex7IdPY0EydwzOBvZ7gDaGZzg/P9BJk6hSa6YLwTKBoFzxsCcl0YXimOyHTztBMXcIzuSHTO6GZksIzdYdM00MzdQ3PZAPsGGvK0T08x9+wCQww5egZnuO/kCPJlCM1PMdu8zb0QSocfLbMcCww+RVCNLjySCgaiMV/7nDEAScFDhGsiLVETVOHZ2PE0ZswOEhBkILvKfiKgs8p+JSCTRSspaD2JllfFNX3lh7x5xCMmKtHNFBEOUSguY4dImJbfpXnw0TLA+L/s+J/w9JES40Ivxb/rUsSLT3E/yHif6H4/5z4v1L8PyD+x4h8qQLReojQDQgnwuEivE+EOs8GML1YYHq/RYZWuzhhBKbvQ51Tctod6s1s2BX4CG/2ZvabVxwaMOB9s5W29A6Gqh1g3qEuu/t6eG8gay2ZynavMrqjWxveEetwVowC3ajStcCJFdT4tUBJmji74ALRXfoWcGwtJadhkyjKZk5vmmp7jjm9wN0SsV5i9HLFtljJRitnd1ZpzFt3r4bqguujwNst/MxSNhLDqEs/9lKWBnFegyucpn6e
*/