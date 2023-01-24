/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_05042005_1145)
#define FUSION_PRIOR_IMPL_05042005_1145

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
        struct prior_impl;

        template <>
        struct prior_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value-1> type;

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

/* prior_impl.hpp
p4DwOwV3el4FcAeSfyu4/JuK8u8Duvy7JiqEO9QqxRNDpN+BIP2Om8jZw0cysIfvhDnvsTLiDFWcM0xtxBngi3LTh8QZ4EfQSfFvlwhPnmsoCiMWXHinRdO6hDfPQQEJlPTgBCNjQJgYNzGG6CLBGPB1rIeq+jySFr2KM4YSKAEIpAQmEmNoEIzhZnQmPYtJhHUG0ecdyBoPUgQwiNsaMYh8xb0ziqSGYDoyiMP3CwbRkzOIfOXFO6g7uZEhDAJFjb3KmfHRGkvKTJvT4OnurMzXLHsXYf03UxLuIuXy94ltFAWvwQBA2Gb2UsoJlkZY6m6BiwtKJN57XUpyOg6LULTPl/fRsM7J957ZQcMSfM98f2O+9+ntNKyyiLBh5cGwLh+PfG9OGN/LFBUDy6vnLE+iJORwQg/ML5szv1Gc+VU3Yn43w4EDY3/rryH21yJCsL+aO7QkvR/gn1qm7mifQflQVt0RwhgDFUbJkrjf5xXWECnXwDM3VYQTBTBF+P4Bp29K+wqMcu4/xCirOKNcwakUYqB3EjFKFE9xPJ9y0goySuAm5JZOnVsSNRpbwQeBdWwYz7nluTmizgDtOrnWuOUqzi1PLAkz4DJu+cUSwS338QlY1RS3tHFuOSbngrjlgheIm7n5czp/xr1Ozyj+PANcT1nYG/hkCf47qzdyy1/XUIHv+PMQPJVR9PFj/rItr7Ulf771muYXp/NM
*/