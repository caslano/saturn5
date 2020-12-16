/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1340)
#define FUSION_CONVERT_IMPL_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::as_map<
                        result_of::size<Sequence>::value
                      , is_base_of<
                            associative_tag
                          , typename traits::category_of<Sequence>::type>::value
                    >
                gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
PoVI38n99JH//I77KJ75uJUPxd9FrmWUpMM/kXOwrdao16CzqMTnMZ6X4ijjwg9n9tH0+r0u2VdtcW5qLM7NcHjXYH2Mc2Cwvw4Ru9u6mHw/Mt9tvcDW96N2XII+oNCYXmnjt3DPs9Sv6k7QF6T5LZq7yncf5yXuu6igrIxJpU8bu9l893GenS8m3Kykvmf5GG2a1U2+/ZhEu3rXhtuljPGs9SN9XA9o9/BapV1JXVtmX5fcm5X+Xbq+zfcfa218Q6o5MflprHxEO4mPKEv+fDlS9I9GHucfbUH92mXNxbfzjiE9fS3VZISv7QyL6xi4qsLXsXoehm5g/R3K/AsNPiq10fIxyvjHld23KDczfYsymz7pjl2l/DzjwuS+RTn/QvVe/+qF6ng8XM5D0wbWvrqM+fa+ukTGgvHcP9Uj+IsfkQzkG6RaewYHdZaWl0/l/OOOnBy9r3tLX5v/ThkPP9THfeVUl+zLD58T7hmyrxiu101/blZM4d8R50r6+SHsYxxRV/BcLaXflvUIjptbNbsjx7vcN5Tncvj8vD1fPT9pF6nP4l2lr0ZsGGxspozTdORhbKkNHl85NU8uVW5B6nmwv1Zy4O2DQ32j6msRfUOQNPEhrBjMfrO+aQWlVd7E9Em/hPrYU23w6a52fLqOTzdJn24qZagn97IDVl9bOqx26HPPfPn7+YPXvK/3oDRt/5DPepw3s9e9Z+/nHvpW40W73h3d11szp92XuMLkSzxafL1j4dZwHDwIHgOnwmNhOZwIA3CS8V2iueLrlXqNPsFDxNd7KMyEo6VcDZIr5T6QchvBgJSbzSHp8AKYDefBHWAt3BVeCEfC+TAPXgRPg3WwCV4CX4L18E3YAN+GC+AquDBsv8w34MYW9ueLz7kApsDJUo76QvMF5hHBcqn8e66Uu1Psv1v68x64PbwXDof3wf1hC6yCD8AF8EF4GXwYXgMfgQ/Ax+Dj8HH4LnwKfgmfhr/AZ+Cf8FnjWsMXtPvEV5h8zzniq90Z5sBhcATcxfjN13n242Ur8RFnwYFwENwdDoZumA3L4VAYgNsZ6m3toN7hUu/uUu+eUu8IqXcvqXdfqXc/49rMteKbtmhvkfjap8C+sBgOgCXGdaWkfLZxHFjEALaC/aXcKKRNyh2JdOcf3eAIKfealHsdbg7fgNvDN+EB8C04Gr4d/oas/G0I54kdxm/Inij1BaR/TpL+qYbHwJPhDHgKnAWnw9lwhvF6nS/9ZNHOgTIuthB7M4zXq5T70eJ6XcohGfBKuA28Gu4Kl8E94TWwEF4Lp8HrYS28ET4Hb4Jvw2b4GbwZfgFvFf3LIcQe+ZsEZorudZA+8u/9Dce1yHFDbI7r2YX+n0jvTmqPT2Tx75GTundqnGLoqn9XrGL8qsTjFX76zhizOGvVPxe3aF617loZu2hdtebiF67W+GMYGcvW3jhG6UNdYo5l1DL2ViCrkT7HdXe5kWKkEXkKcR1P+5BJSABpQl5C2pCeeU6cw9mczdmczdmczdn+ufg/CIbmOyH+r+X/V1HHB3r8X681r6i0YEqlKxj3TxvoCud4D5O4//pB6PPY07W142eY47Ht9cQSLzLmkV9vWFOgi8R8a9DRouiojFtH72BMSuIweinF35wt+QD9JR7WDzkLva0zlDhMCSoLy/zR9YViYDOpA5+7xMBCP09WdNeJ7o0kzt0TOYfjUk+P0F1cUFkcp+5CdS04iamXiR+/GJnDcRlGXdK3haXeAl+VP2pMJeRbP0/Xp5cVnWocfxySLn6Q87VxY6HTU05gJ4Z3/TWdbjjLoFPbN4p90/V9RG3kuFxjbMUQp5uhH+dBoeldka7iS+G8ZMJSOE8=
*/