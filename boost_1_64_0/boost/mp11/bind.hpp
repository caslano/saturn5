#ifndef BOOST_MP11_BIND_HPP_INCLUDED
#define BOOST_MP11_BIND_HPP_INCLUDED

//  Copyright 2017, 2018 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/utility.hpp>
#include <cstddef>

namespace boost
{
namespace mp11
{

// mp_bind_front
template<template<class...> class F, class... T> struct mp_bind_front
{
    // the indirection through mp_defer works around the language inability
    // to expand U... into a fixed parameter list of an alias template

    template<class... U> using fn = typename mp_defer<F, T..., U...>::type;
};

template<class Q, class... T> using mp_bind_front_q = mp_bind_front<Q::template fn, T...>;

// mp_bind_back
template<template<class...> class F, class... T> struct mp_bind_back
{
    template<class... U> using fn = typename mp_defer<F, U..., T...>::type;
};

template<class Q, class... T> using mp_bind_back_q = mp_bind_back<Q::template fn, T...>;

// mp_arg
template<std::size_t I> struct mp_arg
{
    template<class... T> using fn = mp_at_c<mp_list<T...>, I>;
};

using _1 = mp_arg<0>;
using _2 = mp_arg<1>;
using _3 = mp_arg<2>;
using _4 = mp_arg<3>;
using _5 = mp_arg<4>;
using _6 = mp_arg<5>;
using _7 = mp_arg<6>;
using _8 = mp_arg<7>;
using _9 = mp_arg<8>;

// mp_bind
template<template<class...> class F, class... T> struct mp_bind;

namespace detail
{

template<class V, class... T> struct eval_bound_arg
{
    using type = V;
};

template<std::size_t I, class... T> struct eval_bound_arg<mp_arg<I>, T...>
{
    using type = typename mp_arg<I>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind<F, U...>, T...>
{
    using type = typename mp_bind<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_front<F, U...>, T...>
{
    using type = typename mp_bind_front<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_back<F, U...>, T...>
{
    using type = typename mp_bind_back<F, U...>::template fn<T...>;
};

} // namespace detail

template<template<class...> class F, class... T> struct mp_bind
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, == 1915 )
private:

    template<class... U> struct _f { using type = F<typename detail::eval_bound_arg<T, U...>::type...>; };

public:

    template<class... U> using fn = typename _f<U...>::type;

#else

    template<class... U> using fn = F<typename detail::eval_bound_arg<T, U...>::type...>;

#endif
};

template<class Q, class... T> using mp_bind_q = mp_bind<Q::template fn, T...>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_BIND_HPP_INCLUDED

/* bind.hpp
dsIlcqjr9eKQtsfjY6Rrx7xRb9KfkJH1vDisVQpzCNfyI6yg7iYRfcmqqIN0sUMHNua/l2r7zckK6k+nGEUvgeG2T/ii80xWUMNYiNTSwE3i3c4nwtUUxoYp0fj28P8Y+r430XcF2n9NNNG3G9CHb+NGAUj10qmbWtGKZ31cmTEfv6wfg9aWntcuMdPT22XQU4H2nxMT8utmwa/ryoiiFFZjHaQt1v9FDH3ZJvouA/oePTcBv2YKfn07WSq/muLWO3y0/+PiOH2RD8SggZCbDTz5lF3lkz2KmATdro+z7vgpQJdh470wEt+hx+iTFRsDN5mTjqlPMhFVwFzvwTRJgAWvFlVfi4yKfLx6PlEtn4eciWdYqJt5taiYz5ahM6kvw/77IsKbkKZTdZrqzJoJ9IEYepoeqpi5RQpZHz6nje2BtGmmV9NZtgkEnIZGfikIVUlQbMvAk1vFrPP4wEQRj2dQJeF3LmnjTBaF9Hw9vwMoP4ee3xLh+NmrTVLj+H5M4GKRllQ+9P/NZcDfEO5zjRItBYFL48q49xytjMiZiVRUzb7OyS5i4j10R9kGD9+tW3+3FGYY0SCsPNKKJxl7Ln38zIYeZ2qFis34IjTqxR+44wMXaXSlAM9w5eO4Gai50kPoE/vtpIMzcAxk0eBjvDVNvDXOUajmqq/sCB2mYuMbMbf3DRuD02GnIyGQZIabyjONlhfRQKUtsENOyZ/vJun2evfxZim28GE0pidPUWJmBKuVhLNbnBHsg+EfKAnRGINpYpq8RknYo7HQYoSPlMSdE4opixtGhbaei6cOb+aZ2B7fkoIXORUChdf9qIAWo0OL1cl+eICBB6gDRorFoavyA18bwKT5pZDK1IXnyHRcBx8ZnfpIxk5d+nhRdGGM/Laa5LdVl99FJvltNeTXZK54MsSLYf4diTEKZpoL844SMEpmhYd6WW7vSgDjyDnXWK/viRfo8phzTht5vNAkj2JgPCNZTVpZHs9Mgg5iUyUxOysJOmj43seohA4GDXSQ9ImjztDRQRRWbuY6u85Lxi4DG0N0kCrb7yAdHZzBRWJmKKL6wRE+duaLQxKGRiH5JHyGKBpsWSeh1gH0ixgc5COzWkiIc/iYAhfBbSEoNuqinBlGn6YTq+qjpS1HK1u6DPvX80z6Erb3fdLKtgbSubHnZbW1zD06COeerofVdmMPhGYTtDmvjk9p0wRszlnMc0y6Nc2Eeh8iFodzgpnYtHCWhXE6KuI6/dUT9flb8mocnsAO+kR6Z+PaqczamMrUnRlfmeIxRmUyGNk6cIsqY67Pa+dq9siTXAntkQ+0bo+8I9n/QH6aDUhqs+S7CC9dqpsl524gs+RPvk5ilnyNYZaMAOerYwyz5Nw4s+RLMVPU9NLK8vSDVefp5smRdGGdUKzbKT8qILUmwmDVKv2kFwfqC2zEmi2e+sDutJysVtG9A9knVJyj0dOk2aS6ysdqpk7hGaUUxngd2aSGySY1nMQmVRxFE2eTinXTf9CZoUz73g6zs1Oi/0LuZMCoN4CmFoFZWZrmCoxsPRKpMU0Lgny0lK+YjK695HMqfPDxwvxFP2wIrK3v1DMbv740/ALn1DhPMGjvwN0xpcEi3Q0cJ3CPHoC5h8+np5p586XEymPJ9LeOthkdhtYndcA5muN5KZ4XjR7qSsMfDzCe+YQ4PH1QnDgYOm6kF70N9F6hWUm7DS4erttcs2I/7R0vLXqoEb/2oH4jP6CFHmHmqzbmGYbQZduh5NCJyYTXrqVRrSDk4NZtfo+N60SjwD6+cZVASFQA5hvfMHAhYikdBMcW02JRs4f2EoNg/ERORVzUU6g0AfFhOL13sKyCcDTX+Oo=
*/