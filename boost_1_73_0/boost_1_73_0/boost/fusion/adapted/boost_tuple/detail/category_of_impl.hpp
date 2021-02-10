/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726)
#define BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726

namespace boost { namespace fusion 
{ 
    struct boost_tuple_tag;
    struct forward_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
WjuAcSEUKJnrDWs44H0pUl4pngFTkHGVNmKFD6ICXXDIRclh6gcL1/towqYQaTHg3MkWVCHbMoOC3XBoeMrFTQ9Ts0aDzBEB8TOhNGK2WsjKwvAcNG/WaoChJFipJLAbJkq2wnBMQ6F1rX6dTNK2KbGSSSZTNUm3VFiFXj+paoHZrNkdyFqDltAqbgLZm7CWmchpRYpws25XpVCF+ZAWBqyyiWxA8bIc4NBVcNWXwCEa2DLJEmrMXmhalKwURdsUcr1jiLQOQHnbVBgOaUG7TCLxJrRVxpvOviNiG2VguaP8hSN7yD0DWWFWMLIjcKMRrJgSyoRrN77w5zFc22Foe/EC/HOwvcWAd+l6Z6gNgVEb4Ld1wxVm0YBY16Xg2U7wH9rphhVfwHQezvwgTuJZZM/ji2QeOaFnXzlwBKPDE/izrUjf70YwKsWKBADH1tGx9QY36CnhTN0lims6avyiqhQCRxdAIMaz6MsDUkUDFVvzQSKQY9FoCKxFKiotUkZwHVi08PwgciPjJ1GlZZtxOKXovSKL90YXKJW4/zSpMb2B/QK1UqJknksI9VmwBvYpqb3fuphnTjQN3SB2fc8IGJ4JG2yGnsLMUTFDG26br5ai6jRPGqrasjwgVYmKkTgInAo2HhVMdl8Xjf2h
*/