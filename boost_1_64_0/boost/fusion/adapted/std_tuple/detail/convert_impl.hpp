/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0940)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0940

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/detail/build_std_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::build_std_tuple<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                > gen;

                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return gen::call(begin(seq), end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
76V5i+YIEZzy/NaCD4/N6aOawdrbWDNJII33mxbaSH+9bsonH1jVatQyr669I+aurr0zZm5f2rs0W1Cdbkyt88J9d8xduO+JmQv3vZotbY9Wm5NIMOb3UrzR4b2lCabb9Qc0l5CJfTBick7+hyIm5+R/2LBib12x9y24u4n4OUku/fpHkpzCpzb9UcMXL+VLrjY3f3/M/L1kkN/nH+d/26ZE2ieg6e+Jn4Q2ZnZE5XSAKdt+CjqaEoX/adLmEj+X/+2F/xloOvzzWIvC/yzrCJ/zcz5pA+6ex8/hb90fXACNI2Ht89A4MPbthUaj/tXsDS+PjfYbx5X1uf0X9eSVgWH4/+KEja5vl6Q46tsXEkyf/3dpwWnf+nFDw3P6yFeXWU2OayH9ctG70zOV8UaL9S/6+sQMwr7C6XK/xpVa4x28lIernD7JW8fGs3YF7/urPZZnfAgHsy9phhGezduXLaMdzxz/NZ4mebjW0yUP1zld5gqvL7TSWHmgf6TEm0nLpWOXmdX2Jdk3+ZXeNo0OwvlqTxtZ8/01bVMeOaZ/QPqDr0dM+oNvREzO07ohYEOV4pVQp10jG9i9lkmbrEk2iOOm0IaShnmmiE3yGiQ1T/atyEbGcd+OmIzjvhMyHvxQvN+NWB7Fe3Ns05jEfOYtIQvOH/9ewZeODZniKul6faunS79zm9YpD6zfbnSzXIPGXvrM4O8rXaafMaekGFbEU5p/GOqyUp7nljSfzFzafqx0fW/WHVo3STasbvc/3KkYNquT/hPoJiuV1nhxcCzmj0QvvOzudv8Z9PE8q7Zrqyo2TT8P9Gxthfrku6CbITu1y1/Yv9uZWwN9t6chGTn36fcwc3sBfom/zUoSJMy4Deco3Buz8XWMeX6IOQ3jqQdDX/Fr1rEpjrXfWK1Jh7ySdh9r5FojkvZbaObvvqkm292vNJMZ0n6ntBx2D0AzNn02vN8rzazypHQ/yBpniesu2T5kdZXGh6GZZ12Yf1CaCZf36xmNjuCY318eGhgtmX/RCtPiCJlGX5336yVtChPuK/4UcayyIxPM+UQ20tc+GjNTNJyGel+D0vCXpE1hwvPLj/XkdvEV2z2+XjvjHaxXeGK9drV2o9OoVac4zCd72mLBFnzwVGzn2uzTEZN7Yp8Bo3eMOuvhWV/37xv1mdw36uty36jWy2P9Y8vK/n2jMZf7RmMm9406NroYSST9374u9416urzznrP60mHTEx/rV1KkcYNNI5vChPK3oc+kgto9ggHX+6qfHzBdOW3cG8U2hQk9/4KY6YpJNhunbVApuZ5tEtrEFZLC2jS2k8oIP2/m27j6sbmvu7ttt7C6EYeGFyzVv+lfGDJ8/9gy0PX9O1sptqxUHvMLFHNPCZvCxM09BVwKlePfOuD6u882IdOFivBfkrApTGweto25Lliy2S620QVLfc1LY5u4YBHn9rGtFC7KcIfQBuXxskDXv1t3DJj+HrWTYvS9hcpqVVatyzrnlwc22tc7B4xfvNPZNA3f+fldQptVnc4M2K4B021+t5A1TZgov91TjMqXn90j5Pqu1IDxmqV2dgqe3VN4eWS+ubtZ3Ye3V8Skn987YvJbYR/NBvvH+tU3030jJmPtV0ZMxtr7aRa8I/b3mevPDwj06WqntgrPHKiZen8cFOh5RtXX3flxcJLLPWmzNDc/dUsq77MjJnnvi5jkfU7IuFJTeg4RtnzpMaVB16fh2bkp3uBnD00wXXcOs7xcGl1ufjksXjrgvUvnxdz5/vCYuT74CDA6CMm8ZUdLUueOjJjUuVfFzATJ75RXCxteuLgUDQDdGbtpO/eOe23MVXfMYRwV28AvzPtjzl0F9oTNT3M=
*/