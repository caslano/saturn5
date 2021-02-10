/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05052005_1215)
#define FUSION_EQUAL_TO_IMPL_05052005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<vector_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
6eNVb7R6rrkyLGCzgKCGEwPC3MqdVLpEa0jWYYe6S73+LDGvWtIIc/EPmSbwWAxBw5Kp+M8loRwybv4K1TAcag7UjWwmNMxSxMv5UKa2t+E9Y22YT6E74On2lFE9HhTg8U2h8iaSrD6k4W+AKNE//FlTpy62gMfbRDvqTTzglkM4KwCbFWNmPqzVwQog4jtRPJJ8DCoKGyGr1HRBzBp6UpN39nnvteVVyBJqzGrU7lfze5q+QRtndClg0Ag2MlnINMQT7oeNnCzqiuI3bR9m+SEJTLwjiD0HzOkBF+YSTl3nLN3UM1Hbt3dIxK8+2a6PK+QfMQQ5YpaMwtnTOXqlTYFNSeGkYS2p+CAbAfyYga+SnAx94geHH1dbGbPQaaK/Fbv4F3RUK31R34Y3CLC4YiNg4ZfozSAImvXMZIwLIgk1yEI6Yxgp/iG114UmTsPZI516KQwdgIyxm0UvK2ZFX9HEtHTf7rbenbeDzsXHV5U9vcKuXlV39cr0pQxGPgTHcRYAKqewr1PoAAUSMj3pXcqmSYriSZp7jJJwA58eW04IcKN2zFlA60aZcA2eVP9sgfA4TuZbDDXofAocZR7G927nLCnBpOGX2jjEsBGwJiRcOmrDXB3OiqHEvAzooHolMO41md1YMh9NQ8CP
*/