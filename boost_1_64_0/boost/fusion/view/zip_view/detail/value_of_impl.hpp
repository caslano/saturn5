/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_20060124_2147)
#define FUSION_VALUE_OF_IMPL_20060124_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion
{
    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_value_of
        {
            template<typename T>
            struct result;

            template<typename It>
            struct result<poly_value_of(It)>
                : mpl::eval_if<is_same<It, unused_type>,
                               mpl::identity<unused_type>,
                               result_of::value_of<It> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename It>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_of(It)>::type
            operator()(It&&) const;
#endif
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Iterator::iterators,
                    detail::poly_value_of>::type values;

                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
YMY8syo2t9FCwWoyk0ytF4W2EozfJ2oseKhPmYHZ859N+cMvaDlgCmbDHGv8i1YMVp2Zv6JzazSpoYH23ydfmTQYTQ7G53dRFemP5gZWlV/z6mwNWgCYA7PPc885oUWA8c9cS9+nfESLFs7SVrWjB9p0oa6P4nEYWpxQ1zwyZQ5aPJgRnQXsV8BStCTB7N+1aoS2VdivU5UPajS1YGvfLvVGSxfWPPAq0YxmBGbGbE+bZvfQCoS6g/dql9D8wKTMgk5/MUHTCHWrL3UdhCapYqD9Nzzrc9PRXMF4nekozT40bzC+347eh9ujKYU6r8gUOc1d2O+WXfl3mrtQd738XTOaH5iM2Sbbcl80lVDX+7yhJVqqsF8D90+0Xw6YMbOvrZQulLWwn33tb7Uoa6FuZbW1xylrYb8TueOWocmlBtr/fNr433QNuoHx6/P78GONKWswK1a30cUrBs0fzJHPYdCHlmihYGbMwlybvkSLFfY7UDLlKWUNxu8htVcENqE8wfRYnWWv2k5oauGczndX1aWswUyYbd14ejplDWbKzLHKsLuUNZgu//7TqW8RWqnQn7xg5Ea0MjA+v97TWg1GkxppZ/bVzmU5zQGM72ckuTiE5gCmYHU1N7npoAWA8R6CHx5pjxYExjM7IvVMpxmB8Wsi472iHs1BOEt+n0eT0eLB+Dut3T9X3tEcwCyYffvWagDNAcyGmfHCnY3Q7gnnfD3KOJvmYCS8FxSWh1PWwlkOO/ZZgKYw1q67uWd+IOUp2Ijmt2nu/mD8/llWEvKKshbqMr/5bKc8wfizuHvwE2O0CDAZvz4/NfmbNZgJs+sFN6gHFZg5M7Of3Y9S1mA8a5NZR3Mpa6HOaFHjpWiFYHzux59U/4ymwTo0l3/M0aQm2s/U+mXv/ClPMF4Xem9BFOUJxs851f6MC1oQmJzZperhsWixYPyc70YUF1AuQl1+f9ueaFvB+Bw6pyZOQEsHM2Z1uTtc3CgzoYeBb0oGUWZCXYN82Vu0UjAps8YZX6zRyoS6R0GhCZSnTLsus/pYOosCrCazvH6dzlGeQp2eR38ftECwOnx+33eko8ULdXNP5pugJYFVZzZZM1tGuYDVYjblS093NI2wpnPtQhs0ial273ffr7+BJgfj8wvpYEDndAPja37ZPHokmi+YNTOHc40z0ALArJh1HDKkIVoomBGzY/1vp6LFCjaznuFBygzMktmuw99UaKlC3cT9hrvR9oDx9+TCnrIZaFlC3ZXmU2gOeUIut8cFL0UrFupeu1vTOV8L+20eHHQerUyoK9txxw1Naqb9HNMb+qQATQHG64oOZa6mGYGZ8LOU2trTjIQ6vQXVF6P5g/HZtvlQKEULNBM+GzZ+vBAtQqgbGjTIDC0OzIJZ9wdJiWhJQt2rL2OboKnBrJlt+TxiG1qOUDf253dPtAKh7smXZRZopULdvbB8W5oDmA2zy09N+lLW5tp119p6hFDWYDyXUIM62WhKoW70DachaAFgVszC7g/4Fy0UjD/jInT79KCswfjPu0XfODu09UKd7Iq6HVoqmCurs34d/BMtTzhnio/vIbRCsKrMWtnbX0CTyLUz2/T2lCGaK1h1Zpfqf41D8weTMUtr/b4GWiBYVd5ftdYb0OKEuoLvKZfRVGA8l6beI73QcgTz6R93GE0DZsqs6PeeNOrPQrvu6yKzSWjeYDyzY//GzaC5C3XR65sMp/kJdS0kTm2oPzBPZp1+jIxAywIzYjZ5fhrV5Ql1C2u+zqAeLLXr+q7M/Y0mB6vLLPf3RHu09mD8OX3KP2glWgAYn9G9tK410WLBeJ4NTzb/+24KxnPJmhVhS/1ZCt+jpCe5oBUIdUc=
*/