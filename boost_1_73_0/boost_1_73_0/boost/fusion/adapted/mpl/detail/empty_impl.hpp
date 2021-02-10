/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EMPTY_IMPL_31122005_1554)
#define BOOST_FUSION_EMPTY_IMPL_31122005_1554

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Sequence>
        struct empty_impl;

        template <>
        struct empty_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::empty<Sequence> {};
        };
    }
}}

#endif

/* empty_impl.hpp
xQ9H/udwFCZz6rj2U3nkvT/0frIC0yCZTcfwxR/NAmfKDX4AtHUdpNEFiLar2rFlqbHFvf24tIKz8cU4uhqnkR0IpCSVaSHvxUEA/iiOcOR9nsILtIQeEhMh+vqeKrJL/DR4KOb8D1BLAwQKAAAACAAtZ0pSOUTt700GAAB5DQAAOAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVU5JWF9TT0NLRVRfUEFUSC4zVVQFAAG2SCRgrVZrb9s2FP2uX3HhYUASqHL6APpYV0x1nNaoKxmW3NRYBoGWqIiLTGoklcRDf/zuJZUmbdq1Beo8bNG8r3PPPWR0OoKDn/YKInIH33wV7q/AF75fGy20+puX9ssGRfEB/A8anuL7d4Qaw43Vh2IfvsvqA+w5q2KI9Zw+F8V3hDulJOnfmIxPC/qIK95ysJ+obqfFWWNhb7IP958+fQL34MHhg8MQjpgUvIXMcrnh+iyE55Vb+aNhV1eR4S9C4BZYG33iMG+EAaNqe8k0B/zcipJLwytgBipuSi02+CAk2IZDLVoOk3SxniWvQrhsRNkMfnaqB9Oovq2gYRccNC+5uPBuOqYtqBo9oP9KGIs+eyuUjDA8B8v11gxuKAnWGgXsgomWbTAc
*/