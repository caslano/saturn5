/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09172005_1156)
#define FUSION_ADVANCE_IMPL_09172005_1156

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;

        template <>
        struct advance_impl<vector_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::vector vector;
                typedef vector_iterator<vector, index::value+N::value> type;

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

/* advance_impl.hpp
FBarcRcqceVvhqiu5w6RurEHK0zeMRip9B94Ru5VZQW+vI8rhLRjiRt+Ukk7O48WBMTzHGut6dfM06vaK+kVaQn6nF75Ce/pFXtJz+HevmL/00t+ySQ9Kc+mcu8/iBAm74NJUX4cqunZ78uyucu0zn4Y7mcyNtd9fop2Pz6npfI5K1c3xgAq85TWHYZ3PUp+dsmziB2o5OesPj/FkiFL3W1KgiQ9fZ7iJU8y3p20I9HlaY5Te+YSYfLOtHBMk2cZxRbP8kxsVLs8M1j24n4t/1m5ThsR6+7X4i5Pez3K0/3uOouMFbiEEE4oJhwN4XxTj1/lEWGqL+NyhHg+b3EoTXCy8nK1PB0JcZVnUUp2TZ5K1XwqUaTc3W1y0otpkuNRbiWSz/sJbQl9CJlsd+QBVz6z7rP7fxwOMZTb3JYyhqThmIuR9/t9Lmn/QdJ26NI2HnPFXtOX90GaPL9bYzLOYjjOkOWKdOU0W+bpnnXJ+JGp5MHzmDvepHbZZRO/6qA7//4fc3PrKLvP0PE/8Extc2NlftDZ5msyuv188Kcno462yRmdGXjW9mU/a9vWUpn/eqcnLGt3FL84ML7f4g/nXepYv2dt4Rb5vpfvyQjKpgG2JljkGYYsx/e09+WG6JZzXGd9o3TLlcpyg0yWi5Dlrlnk+0q+xyLk/bRXZLnJ8mxjCvbABOyDD2E0TsVYnIajMBFn4XRMxxmYhzOxCGfjUrThekzGCkzD/WjHk5iOb2EG/gwz8feYhU3l2VwnnIdRmI3xmIPTMRedmIfLMB8rsAB3oFNXThf3ey+n8bJcsUW+h3CJLNccs2W51jJWSxu8C0MwCtviEGyHI7E9jsNQnIIdMBnDMBs7YgF2xmIM1/Ip3y94v9f9Ke30ZLnPZTl9O70F8mxuMUZgCT6IS3AMLsWZ+DCuxlIZn3MZVuJyfB5X4AkswzdwJZ7DVfgjXC37bS3+Adfpj/ODsh1eyruaedUbm1nObWzm0zOnz1gueBN9Om9raDlPKF5s/hyq++H/zWdRcYf//c+j7Id9eyZVfFh9LlVx+H/n2VQkx9Y4QiahjFBJOEU4T7hCaLq5maX75v/t51Y3of5faXyf+WXV/9+uuw+PlPvw6XLvkUCIV+5zNnreh9sLHXXeoxnfsW/WVt/4m71K0pfvA8u9hDGkb93kmb4jn5++PtzfuH9jP67+xna43ykQrf2OL/a4r4qT+/Rpcp83mTCO5So3afd59kyH7+l2cW2nQ3vHdrTJPWqsyT2qPk+HJE93y3LdCdGst3K9No5hltOH8RRM8uT5ngC5R98rZf8U4U6WDd6g3VPmOHRdP3y5vwzySDNFyt79OdXjnfbXJP07GpBXDML3OpH+5pr0OfLSXWeCxfcx8DuxDo61LH2biY1qGdDoQH23QiRpf0ZYr/x+c6Un41Pq3i+QSonp783jXfNTsufI/tJvS1QTuT9vzPJYiMq2OMr125Keq9+WMyiTaduL09s8216cNWyb9I8x5Nf4PgoHidbct1bfIW0varZXtmtBforDxsbJewO0+HZeqMCyNe1rZJ0cu7KOCuxmcS9bM98qy8u6c7Ps0i5ES9OppVfFvKqWnudOubZtrLbWswteiWJTXt3AfNnvvMtD5te8zyPWsO+VeQkm7+Ao1uaRvO7dFPsU1f3OiyzUZSslX7JdjG+iHlNfcDxFUmav8PcRj9S8r6PUYx/Vfl/H8VvUHd9B7i/uwAnKNfDr+mOnIN1pc6Sn55M/OX7W1HH8DH3c8/gpNymLCsNxLdtndkzp9z8lVNOeq0mwKz7PjNT48bp9qeS49jil6js3gtT9Ju+TcFhCjcdzdlaaTZd+tGG/yf7V0nI=
*/