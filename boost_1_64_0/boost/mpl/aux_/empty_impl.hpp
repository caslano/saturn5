
#ifndef BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'empty_impl' or the primary 'empty' template

template< typename Tag >
struct empty_impl
{
    template< typename Sequence > struct apply
        : is_same<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,empty_impl)

}}

#endif // BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
UdO/d409/XNR07frbk8/ntNHXf8TJf1wQ2rH+4tA64w9b6Z5YGwn5KtmiylBQB2pvtaUAIrKhXyfH3aPkqO242UHui4tCZz1HFDM0SMnPXjb5ahpxA0L/2yixMNo4ruYm3C3bwzVX3S3qn+4eX+eXXF7KTjlI3WVj4OHISVXZKg7KQtBjnZXWHupYms09l0te4jic+6umU22aO994P8ftPOnNwmC0Wf13j6FikEtBINaCHHguUqAWJhUkADtdyHLc8YrXfn8/MzVtFvny3OWhD/T5LwsyM1ZIKRSARz8C6gSwd6K5OYylXuRyEmQ8BmCqTX//DiyguHdlIjRySdzlUU4hgv5QUHvWnF5fRYThsiQXWI5LB5oeifLGpfl5iwT4zs1P3PxICqFmrpsoDnqdrwWz4yhJ0Rg6WUkFLsHDyk/tWgRnS2c9h5+7BuK0uUbc9kImXgRceREUv0fnqrgKa+bm7OaZB/m9Dgau+7Ewgcu842ivFiHc3gdHh2LiUL6xiK9hhBZTXxcnFSSj2AevtekmvDwZ/Jj+T9laXmk2dhlXRNb+rJUz/K5Zz8Y6qb4+/CWRlkuy9LoKbul0bMuZZRqvj9Lb48srwaJ+zJWqbSa+6ZWqno6V+2/zkE/u5HMhyWl/T5v7bEZeLSGBy6yAj9K5b5G5k5wSDcss31PmNNLB6wieogr63GS5Kcfs2OgYS2+dBnywzZoryh3jqqGjT5KkKrTsCAMuzS4ZlTqx2t3cUtmwAEa0rFHUbjbHqqqr/GEzjpRZZ3KWUUeBYXQZwgWqrFApYYK+LNb8TSQZjytnkOi9Q4/9w+Q5h4NjO49pWfyjc6fle2G9hfeGXw/2hn825zVS5//94Y6/+/qhfP/sXDn/180v9woZP73r8H9d2a4/PG9qtx/J0Q6r6ddU0X/GSm95p6IMA9hNYQzHDuO8if2DPJ/nBntvP5LjyD896jpe06peh9vMCn6ffibSZHv2xeNiGL/+2DI9+aGh6q2J3di9PaMjtKeb7PD47HCin5kyPfGuuImhCFlTbC2gPAiaRX8uSvLdramU6KLMZ8ymj/Eg3KuEA/xCjxGc2PobjABBtGASaMVj3EJ6FNdkWqgGaOMASj9L+zp+3F6bXVRg82t7/vDSUl+082QaE7qEqQDSDWWUgKu706fj+o7druqb6zxvH7X1Rx1fzDzhgj8sqHIuFRn7Ph6PcFAZJfn55z8ZiUgW9x5yex1lPuOoJB5/V3gl56+GK25bcRPIlrUP1yVAJXqhvKhIqsR5uwqFKzio8UH/lB17Hi+S2nalospIJALZnH2xmHeOHkY+59xEp9zBldjv1YabP49Ug0z6PZEheNZivNi/i3K1UBJXJvbsLTKEPyV5IWvjAdlCTTMR3C0UgWG7AVIYs2HzOJ/75Ht3/pLiV3ZoleVjiSC6+7XCS/C4s32Bv9/t8DP3Aa2wx2TI3KPRXjHbb4LjfvmtfYAAHUJIwUpriFeLIiYQA/eJ1xn54L0bQPzG4oHg8wCaqv2mKzA+wY0fHrLfEXvqydIryxPT78b+rEKiJRTco8ncZscWY0FbGKiuu3eDN25gjaaOoiSuFQIjIH0L4YqkZioX4knKfwkLrsdHeGqiLEuta0hUWtGaTi/UKgFUmBwV0vkQjl3ijciiBpfMLys3G1/kR0ZMbutcaND7jxjvtiDjzNz0fI2xdptogdo8bW2ltyreTd48i65hOeVJkZ6mgofmPMpEe4zfPm/l/WhhtTiNTa3En9nV7Mi1XW0PFUB72gGEK8u5ALOxSh7spsbd8qmw2dKtfyOETW7F52pD60HRRaC93eHsTY8ZjcNuUZl3hsDIQniz9Ak7XWInzQ=
*/