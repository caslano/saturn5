/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
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

    template <>
    struct end_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
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

/* end_impl.hpp
pjG4TDG2/2xOLpbUN7kQI9/sioYmF08toMnFGER+N55nWo0MY4LcwIqGZqJIs80CS8RaLKgz77xuAc47r+W2Mb42550STfuh8QFYANCzFhZAwIQz9B5TFqRfakZC5EDwZvH+Tq5ye/yOa77E7cB00eN95kGPp8dDbxdRb+t3YW/nYeyh44OL4JIZb1TMh57OjPc7/vwCv0fc2/CaHQBq/1nWXtM7p1cDPu0p8fdRvWXmYchPfLAlvTu7Wm74p1fXOWzIlLlSdgjpgcVnoS/6OucywKUt2aSXACa6s+dZMYuyIRpuqVLZJKWy3M6tqLLrmlTZA1/ROcYXLZDqVQrVaxWqj3Zkqgf2N4Vqa6Z6P1Hdt9SiWr3UorrvPKbqbRLVpV8S1bZE9TmF6gsK1W57ubmvaRLVUYKqaGlo4wWyjT+lNk5QakhUavjyUuZ7+49NqSGc+R7VHKluWmJR3bbEorqpDVOd0CSq874gqucRVY9CdbxCdW5rpnpZk6jeyVTXRyLVixSqlypUf4plqlt/aArVUKY6gahuWGxR3bLYojomhqmOaxLVTz4nqt2J6uMK1acUqv12sjxc0iSqgz835eH+UJaHoQh7Fh6n1NBOqeHLi5jvlfuaUsM/nxHfz0Qg1WWLLKrfLLKoLotiqg81ieoMpnolUc1VqI5RqFY1Z6ptm0TVzVR/boZUWylU2yhU341gqiv2NoXqsflE
*/