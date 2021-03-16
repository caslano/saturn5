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
8pEabkwdHR2lENVLuO/CPa2csIE+Mi+5orvUWVzuruyd7rB/Li+cn/1+yvnjm8c3j82ev7p8wdj4e4vP1rZuOZ+2IcxPn7+3s9CZWu70EfiU7uw42s3dnVcplyjbNig7MAcov6SsUx7EU/b/H81P7+0ud2d7o+/efu5ostSb3zN/zfzirlGju2dpfqGzV8mf9di7KPS8fsNTaf9l+hLopw+WlfOUUzY8cRqF/fxEn0x03zIum4yty/6fumcBj7I=
*/