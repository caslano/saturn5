/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return ::boost::fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
j+e0uOiM+OxoZzuJkbKof5O6rU0OXZ+Sd7221bd19v/FtsE2jJO/Qa1v3XlRefYNrf7QNmjfF+d42Wc4shrbMg7Ftszvir1ccgvD3vk20NZdtmy/e757Wn/NIN/4e1L6mX7go/bDld8U+msD0YHSL9w5PJq/MEy9zim/JwLVbbglSX6TzErMzJD1r7k+EB0gdaWZXoZF6MYLlO2teB/cGGM5A2S/YtJ/PUcdN1Ypu67fs4+3veIer0r94yPYXmkXz5rUv+0nXUpCWa/b+BSUeN1G3Sbf91F/L0q9Fr8eEWyyXGHa+rPYt785Xiwry7SsMr/LnnP+9vM3+a3oJesgmyT526+QybwiuCZ8hLSW76nbmJdmXzCNJL/n1XG9ve3vMm/6vHO7n+Act5tjWSKdwwJA1rE6LBDU35jafeYGWVfd5NpFV1IH1lXMC7b8UgIT/tixvZ2PfvudzB+p+2nZhuOlb7Pi+XdS2oqa/x8/jldvW7YynJYyHJAy7CV1YdoLahkMx+wy3EeRdSptU45x2jKU8pwxx2xpg4b7Pc3lfo+UdTzJj7IWbteUVS1p6deX5FyAY5OznGHachryn9PCPvGDcl12CSr5R+xw5F/+Y+y8Fw3HWEN5ck3qLchQbw11+0MrBXAee4PN93WMK8c7RtXEQTAeg9V9KPs7Ga5uXwyTeejbFH8o3q67KevpJUc9/fFjY4CuXbteVzulDIVyjfgk3sK0HrulDBnKumLxU+JZVWVv05VctWn9eYY8E69eDzfE1WC4nH9oyzyhlbzDnuQtsVhaUOaYvbYyZwSm/LEy/1nnmtcwqiIGxJ/+jH15Y0A8VE0ZXruwVm5Sm4t9v3u5+64G6UOT/39iQ5yppwyvsvfXV8e/UHfyW9MtNb12p861WOyxEuS5CRxNCjHESsivSowBXI9e+CR641PYATdgD9yII3AT2t/RKM9HyHMTIcb32TNeHXwGG+Gz2B63oh8+hyG4TebXUimLzM9N5lcJ68v8HtbkWyDjRZvku5LxbsZVUv4nMABX4xhcg+NxrcwvxiLPG6BV5ueOkTK/F6Q+tmNn3IH+uBP74C4chi9iFL6ESbgbU3GP5LOFdFDyeUPy8cQ1ks8+WQ+vohcexlZ4RPI7ikH4GvbD4zgcX8dIPCH5n8Q0PIXT8Q2ci2/iMnwL1+DbuBXfwSN4Go/ju+r6kOcFsIPJ+mB3o45XMNf1eitUx5N789Ci5Plxn911vh9pxssrId8PNONZ1Xxdz28+KV/Gu0/G077Pva68R70+dsJG6Ide2BO9cSA2xTuxGUZjC0zClpiBrXA6tsZ52BYXYDspx5ZKcl9a7lcr5QhU2kklWa5KbE94Flvih9gBP8JA/Af2xos4GD/GKPwE52ARLsDP8F78HPPwC1yNX+Eu/Bo/wG/wH/gdXsdr6E1ZvsdW+BP2xp8xGn/BBPwNpyEHuvl/w0q4GSvjSayChVgNb2B1rKfsm7AHumEw1sRIvBmTsDZOwTr4CHrg4+iJO7AeHsD6+Ak2wE+xCf6IXvg7NsWm1K83tsdmOAyb43BsjZHYFqOxHaZge0xFX2R9sWDqfXLun9vXVzOlnqTddGa8RtgFW2BX7ID+GIABOBADcRJ2wyl4C1rxVpyFPfB+DMJ87InbMBj3YQiewP74Fg7AczgQlcKFohsOwpo4BD0xDOvjbdgCw3EwDscRGIFjcCRG4yiMx0hMxjFSD7kWub+OQ6Qeaivn+FIP/eT9KCHYAfujPw7C7RiG7+FteBaH48c4An/B27GKUh70xpHog6OwD0biAByD9lg+cs9c7qWHGGL5dJQ+bZ2wBXbGduiPczEQn8TuuAl74DYMwmPYC08=
*/