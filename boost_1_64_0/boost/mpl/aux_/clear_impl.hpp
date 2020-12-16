
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
T0z9Y3w+V1pX+xkiR4cp9fcncDl/H/pHpfgSKVz82r5WLwa8jbaS7ERWkoJ0nV+QvhPgVbCafLwhLzh6lk/PzGfXqBXiDFyFPf4Q9VwDgW6RS/APegkm0n3B/GqrXILYrjL8E+JOPv6JFqqb5gnZw33/UpL1s/4IevnB54qe9v0sBD3d0gX4n18E609wpQtHLxs5q9LL3Y3lPOrwryGB9ZD2qcZBVLCnI1jj9WFjFVeMc+oXO9SLo/oObNqpIJPGgnRTwncfIzyLBliARBXpWSkvyu/q86JUVLHWS3JR5lB4ZJPNYf/2okXeMo8zx/0JnjF5K4/RpOrX2+2kCuZ3JlHsAzZSBbK07S1NqpSEwbzjBfuhTsTjQhvxeJ6JxzMfMPGYyXa3zMQPUm2Z6gzc6xdBItUgXd7ItmHtw/pwIxugERCATogZPJ/iPgH3EpT6o2QeG8SC2k/s+2prw8bLWzoaUP8ja+eN/0zuvKKf+84T++FtIqhksPZtGP7BvO2Qtn/9JBT/cbV4b35RFi7/ygMq/wcfh8o/U7w3V6j8Yex/qJEa3XAWm6dp1g8+fnUC5Lgm2OVAfcT4dwGImFLfgtQnBVecjItz7hVcTA/9IjvH9G0ghpswjxzgDTlBS06Qz4psm1/ee5rf7S1YguGb7Py0kTaawg0+j43mEjxonbxr8L+TmGgUDJ02msJehmbgI71ldAhRAXmc7YUjsjQsoKuIOAyH4RnyzfgTTNfxrpTeScPJYZqvNaccw7DyA1FAsvZ8Jf128EsvlSB2JlqGLdK8gWWuGQS93a/o33OL1evhq49t6+EtNtlTRMdN/0ZYDwtj9LTfZ05YZ0270qVODDnnL+k5TxRzPvZV+5ybzx6H1BHTTPQAWuAyLq4dHqpZxPpDwaV8OQKxBiU7A2Op/YsOFEn7jAtxiyQCziGGidrqI+pT9Yhaw2cTgLsd1QHurlzfcFXfRRI/vA7jh18BnwoOZuq1VNa1ZT3VRwqvVN9XH1XqX8/yKv27qPzM9S9H1ZfNqKtZ4+B8MwKam37PKRHQDTA176p/X4XW8S03kb+YOCpx7qUp6wK8VrvyGL8/nWaHx7MNOKqLZ7srKRye7S1LwuHZFjiqgWebAv+3P+r7aEgxfiiEWxErVO/5/YozC8VYYRZ61LMQi5/BbbAMOEPaRns6Eoi4LewaYAsxhrGqqKss4oFoS6rgUirAtKy5r1IFbOICmI0pJWZnmeKgnIGXhdgPzPkr6inQa+sFnIF5/uvOEpCxbby74/5/rKq+BIIsPQknYoJBWndx76m1NuyL97W0GiCtY15R2BdVQFp/p1MCpPUKpAyCWw0F0npQ5wJIq0vlOqhyHbSDtJYFg7TyytEo1Gl1w+GNfqxrARLjc2tlLfs1SOviIJDW2+MkSGsPonKRQFrLaooa6Y5j1EiSQpJoL+sCDhnuZrQs2gCMmRXwKlFaAhJAq1lKX0m8BwrowWmflymu3MhVJHI1pElFLnhrgrqQKZL26hHLvQzLvQz75WCC5eCDMKkSM8T8MKHyQO6TA3kqeCAzcZtVcY0BqioGktAnwZhAop91Q0jUybKaoU7G+d+PZWxU/2W0BgB+uRjgl0uIsETCiC2rKSzpHRZGbP4jog7BONwOFcWwIOjQn7wIYmN5Eej9acbY1yGdl0mPCsGJ7qU4VwkTtQBFmKTRxjVIpcf6IP9BFYQkq6luOk4g0l4opLAzNBc9JU6tbiB4p9sx3cOCwGF/8ix8KsFhQbw0udIdI/6CBqnQPmwKOVb5fWanQfOjcqjT1ve9GqZmuvkKX6SEquFxOjMT3VRhxOZqeFhLzHhBbNBeqv2iEjNqeNjFDA8rCKc=
*/