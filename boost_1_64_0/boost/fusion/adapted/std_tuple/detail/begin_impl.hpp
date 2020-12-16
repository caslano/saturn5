/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

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
0qCW3qV4T7x8fTYoO5vOnddrm3dsW9tlfXZoT7vGNoRte9ot5jpJFMbuPWzsfNceATfn+lGeX+HreW66uyl3FIzzOcWxZ2DbqXYaNfofp2Evn1P/q3/b7u041R/K2z5O47LGywdZyyncfX2b6PfpK0MuA3OKYz+fh5mktO3vbOQ33wGiSbmZ1kZvA7SlA8WmnU0Wl3O1TSfG7KAUK/cTOzjBSgNcH2bFjDsuxDk7xcv99GxfzIodNkWaiM/pxfH8IWlu0sY+mZvmlD43V9vLptxPYRyW5vYlQ+1rXi+bVjE5IefvHZ62s50p1fEj0jZBY+R4j1yPrW6zr4rtbPp5L2jMJe3w02tiG6Sb0/LamAdp5riO6mHHJtz++7XNdGuNHbvNFz3P1PhkQOtqfDKodTU+KWldjU8WaF2NTxZqPRhfLNIsMb4Y0jwYX7g5ZWUj73cO/5gkk7HH4iSXsceSJJexx3CSy9hjaZLL2GMkzeEjtjk2aeOqD9X70aRNVIWorpV728KM4x1L2mF4DJtlyqbX2Gm5sgnHPscpFo59VijWa+yzUtmE45vXKabHN8crPR7fsD9PUDb/axxzYmQbj2P6jN3rY7veL2HkoaKewdiH73hUeq+xRjW2AWY+rrj/DmdeE95tem885vU0L/eDZ0lumg74RIpT02E+meblfpTjqiRH04FNI2mDKoiyPjllE7oUZb26py3MUG5TYodvfVxfpwt9dJR+9NLlZeo7ZzNia9zaphYz/ozHlJ6ZYZ2V4P7pUxKs0mTftplRffMMkP4c3AzuGCPMTqjTnbqYf08yyiCVxRpwDNbFaLxdbeMb+alig9EmzmeGboz95IKvY06Nio76Bs/BT9OcL76HAfM3aE6XvoEi36d7fNhievYMjy1bIM9i/l3zgSXlkJ+pOR0S5af9LJ8PLwj42Zpj0y4sKO1v8viYx96smGnaXr7e4rFyf5jut/o88tnbNC8NeGG/XTM0FM3fobn5Rxj3Oz2+fCTk79LcrNkK+bs1N2eZhfw9Hh8oh2XyXs1HSkvC59+nOF2UOrvPy9/7Q36YXx8/oDh1iUH8H/R4uT/0/Yc0Hyt7Zf5hzZYNeek6R7MVc2cdvnyOxz8ScksR70cVF4S9omAzWYa7IDFHrnXpOKjP+ESaeWdgfVLZ0JcINqTnPxUxCcSdnZy2kYiQ/nOtXWuGLg2otvm8ic9Y3eQWz7pyOC/BzN5SYp9NMczhnW9ZF8TuIWUdt3Z6XSGFeQFzDPzRheLZz3sM1x6yCT17IXju+m/Zc3ORMM448ncx9G7TL3HaW1qwcrlSnJtfGRqk6SHaWxroep/FpT5ze00ugz5ULi8rjVbKpdGh/sUUIuft8iSX8yS+mOSyd/8KcLPCctjsl6H4KXjwKxNcrz27KsH1vYhXG150U/PXdbJ8rHWM/V7xJegDQyOLSqO0V50OMuHlk2zz5YRNd6LSbNFFPBz/NZGN/x342ojr9QjYnxrZ0AwgsesjRr/FeL48ZtjdWtRKzJdHNuQ9ev5rMTOvf7fwn9ro15M2nEc9hvpGbNdYAx/ckGJ2qxhsbkzawNWwuSm2MeM/BIT8fjOykbs7v5VgjTqzbydYdxrz7BGjM+OLU4ApkzTPHtnQVmn3/ezmBM9Mo3ZnHcc8D8vie0kbXRYc1q1JO9Q49L23JW20PzEfn7QT33w/yWk/sqmEbPOD2EaW7tu5eM+Gx/+dFu7HRVp+5Nno9oo5eZ/XW8VXJYR/R4pV8la7I+fM3OnbIHnYh+sxt9rUlD+H/1OfF8t7i8OLOHkI42e+jbQB8J97PK7bd/l8OuNtVXyecsy8M2LujjllAqcwkc09aRvucFBvfpk=
*/