/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_REVERSE_CONS_HPP_INCLUDED)
#define BOOST_FUSION_REVERSE_CONS_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>

namespace boost { namespace fusion { namespace detail
{
    ////////////////////////////////////////////////////////////////////////////
    template<typename Cons, typename State = nil_>
    struct reverse_cons;

    template<typename Car, typename Cdr, typename State>
    struct reverse_cons<cons<Car, Cdr>, State>
    {
        typedef reverse_cons<Cdr, cons<Car, State> > impl;
        typedef typename impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(cons<Car, Cdr> const &cons, State const &state = State())
        {
            typedef fusion::cons<Car, State> cdr_type;
            return impl::call(cons.cdr, cdr_type(cons.car, state));
        }
    };

    template<typename State>
    struct reverse_cons<nil_, State>
    {
        typedef State type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static State const &call(nil_ const &, State const &state = State())
        {
            return state;
        }
    };
}}}

#endif

/* reverse_cons.hpp
I6Md4rrHj4qQ2vaGZSwp3NN4UsNsC+vsCWvjTNXhpBfReNvBddkN7jTs0PaC6zMOVV+7wPqxqVgkzzlGhbjb/j0ID8JOUe5jVjDKNW4VF6W36Wu059thlTUuZTnLWc5ylvt3u1bIlMPb/89OdVj/a3Lff5au7+8rff8ucBj8kzbuVYq9uVe0vv+FpCs9f0ffvwza6uj7F+n6/pVbjH3/cpO+/xb9ulRlmZn4V8IZJmtTdzay769bR5lGD97jeECC23hACZ99ZDxgxmZrPMAaD/hvjQfYJir+hf7XDl/YvmLFuHYlF119zZjzGjceENxC3g3yzrAjfvwfcIjxAG8YDbvDy2APaIc+cD7sCQthL7gEngTvhb5wLewNH4Unw3dgH/gB7Av3wVPgz7AfPF43DjAA+kJ/2A8OhGfCQTAcDoaXwEAYD4fAJDgUZsFhMAcGwYfhcPgoPA3uhCPgBzAY1sDT4T54JvwVhsA/4Uhr3MAaN7DGDY7IuEG+NW5gOctZznKWO0LuSPT/kxPTmqX/n63r/8dKu32ynL8+EVk4gPZ/hav/T7pq/78he09L69ofLH4JMMfpR+ztDX3nVLXPPFT0TGkp+y9ljcJTcBaN+kKjnmc797otFaU8jVHkyxiFokeRib7F8IETNNvu2rqFaapf8nSbXFfmzAN+aeJXruU1daZ+vYLYTZ8xabrDr1LLa4biqY1HMPYg++9NykTGEYpaeupX//vGF8z72w0fR/inxgv+r+MCQ9Rxgc+Oj7vqxrQnVnZ6yuejwbetesjTeFDjxguibPIukXdMqJtt3lA5JzsMBsFweCaMgJfBSDgRjtFsLMszL++CUDcby51l/KEbHAW7w3NhD5gNfeBs2AveBk+Cy6AvfBT2hk/APvAL6Ae/hafALrLOoCccAEdBf7gYDoRr4SD4CBwMH4eB8Ck4BEb8j/r/R7Lf79bfb/a+vod+/hHt4/9T/fvm6NsfqX79cvr1ZVbf3nKWs5zlLPcvckeg/8/FzTP/n1mP/n/CC1q/+nzS/cf7//nS/39S7AGVwhnKOgWjnlr/P86zjuq6hCtfMq5LSDDROcVkDMAu+xT0YwC5orN+DCBfrtOPARS41i1k4Sv9fYO9PTkTzGhzx7imAGtBctZckOm4gKf+5OHv5zdXf968/+l5vMO8n+95XMC8f+55fMR8vMBzf958HMFTv7351iM0tP9v3p/3NO7geVxpkjqOED+mxYGRkedELln2+vjdJ6767dDjArxjtHEBu9u4wGgZF4iAQTASngnHwMvgWDgRRsEfYI1N3gXyjiA+9cy83RKft9iT6Ab9YXd4BvSBYbAnjIa9YAY8Cc6AJ8N82AfeAvvC5fAUWA77wZehP3wXngp/gQGyP2EQ7AsHw35wKBwLh8EEOBxOgiPgTTAY3gzPgLfDEFgCR8JSOMoaR7DGEaxxhCaNI/it9rKFrrbGESxnOcv9zd6ZwEVRhQF8SQ27qQzNyDCoFBERpMBEUTww0RAxKa0F2UVIjhVQtJNKy0qLzG4rKis7LDIrKyu67Sa77Kbbbrut7PjP7LezM8MsN5Y179fH353mfe97x86+ed877GCH9oft8P5fVDhTef1v/9r/VN37/2h5/z8ROQBxI5PozGbcZtxTNrdcWX7Q8n2NzfPz04xnpWvjBF20d1/jfstrxa4IVSfpIonKXvwmu2bmlrMbvKvF52/33Vezy7i/vowvZEh6EyS9kNtN6RVWlLfmvG9/erIHuKqPa5Sxfnxjm6R/C9ITWYkcStwqU/p5xZ5m60DO+yZtw3nf8nmmuqYhkfQ2IUp9PyA2yZnf+rEHbU/iBrknQ/ab771aPpv2ba6Wffw=
*/