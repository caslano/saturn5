/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05042005_1136)
#define FUSION_BEGIN_IMPL_05042005_1136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef vector_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
wLYTfKhx3u795juh26+iEc/7HmJh4Y4YknSFj+3HhXguhcTDfObPvpNWPpxQyqxzzSs5Si2lk2WoWVyNEqa31/L0Bz9R1GF2hUGoAgF2dz783+l5NYQAc2/Vx1HVkTrsE9iYlxe+CaEM9reNbFEu53/ZY2mbRyDRNMKfY7vHfg7Yswhq0C1lgfVd76y52dwIaouOWrTevCY1Irda//2gexBpCNPOd48PoOU+wRbJk6NFhgVF3vlVbH4EpDwe8B61r4tMi0Zedxr8qTEBtt6V7owk2oJ5dxH/hGaxMPks32kon5SAZI8eIkufdsGJsDxui3gdDVz1ZkLGK5d6pyPrAp58rFu1rzFuxRhSppsigIYyu1zDQjWxX6s6RJ2Rb5uLXfkS2BvIz2W8lMn5UNSc3jfNTL483VyeEBhB5b0fRAO61hNGl1Y/O0HoW8Rll+CXawEiSl4XJ1v7xRewSMv3DP27sdNWrqhmVHfIslqu6w1N6KiLUgUUcSVtxh/JhxoP0W+dgHMojXFTqycIhux0ehJi8FMuEcsOU/SQF+G5CeonMnuBtIIhfDMuhA==
*/