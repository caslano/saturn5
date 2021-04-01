/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_05042005_1058)
#define FUSION_NEXT_IMPL_05042005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value+1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
d4xhIGRxitfc664J+KkS6KZaCT6LOGR4sTIv9wHX7FXi9Bnsgwej7Wl4CAm5DKXoJHUMtLXoKOTemsB5t5RQQfY+l40huiha656cLfeDuVXhETVaX16oJT2zJ8VkFOZUt3Jg0ZHlUxV/k5ZHuGqfLyXqpvv1Aay7+94164DIOWp/bMgc3/RB0FEKih9NepuaFAK8X5R6lKCkjViO3GKKzYl7aYdn7iH5EkKMYCexxkjiZpI+ISD1LuFqx3Mw1+ea0wIVIm/e7CnGvGyWKwSjX3S3ZczxelQC952bcdccKaXz29itxXWhlYcOZxvlFxWBsE7AP4WceMgOr+Ub6FIwVD19r/OjUOZ+8maAqGY2y9RWFrKuYKGSJC6UcPyCeyYBAy0yqwWYwaBxSG7p3vOwLkT9mdKeOI1hcO4ayzck2wGYHLMcBpjZb5sskhk2CLVaXw1403hGgZe5UC4vZ8gCZAZfoufhn1A6iIRFfhwcyjsk2ji48UpNAUIJxHmoG/ZwcFgfUs8ysTZVOsyVje21ixaS3hVsWosmiVciaKKwc4KoJL68YmoSfvHeyA==
*/