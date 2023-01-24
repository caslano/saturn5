/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
PLJC5nEFVFgh15rICimxOcjpHcOZ6+AFmhXS5m+tLXJ8rL+1YY3heIQ4cPob51tefnbC1nbaYlrbNzVN9t9J3BgpDIKM8ToXW7WxiUUAY2QPfO8GZyndNsjKt+LlKzmRFcjE+NvJ0hDroyp+0hauh5/B6JST5HCvk/3qUs4qq/RWXi+1akQ6zHq6gn8KofLAjSVNfKCs6VHUUIhOqhsv23MuezwLM6cnCqOlyJyOvDXxaeJ27fkzgT9t7KmkJB1TlV7wT48k5JUnnuJ65VNot5Q5q/yKfgo+XbKansXwVI5dgaAT+cdbV5MZc/gLeCAVxl+5Tjrh71ZGnTRHDoCTWmo2pRr2YWzQkyA25aGECHN85yLtTNCFfDUbJVV72ctWVmU1oSoj/KaNEKxGOLP4R/zF9B4ERae2jOxzsF9UOwutBsJXzwmfyaybMlTHGbZ1V2CKjEJBFOVIaK2Bkw1av0/4gUUHK5w/r0N7CJSqNxnsI6CIbVlEUmNTvByZ/Q/Iy4V5wnLdPbQ5k0BOHSHUqwRSr27ulqScWs9oTipyy4J5oFOBtS2JKFKScvUEks8fjsYoV0Khgk8VI5hwnu23zPo11iCZwpc8N4/Rib9O3saNSZghd/pEi6F7Nzw6h4xnkHnGfYvonkN0L1HJX0/KSmKwP/Zxy9xwJSJRqRhPnTxpCfHhWEARQ+vy8B7HOAjmM7iBMfNMeXhDVs8a
*/