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
VyDKfgiO92xTVbn/S0WyQE/gZl1WwsVaVDIbDRRzLgU8N2NUdmyMgQRDVr5kTAXOrA6IqSXexsl2P6QRo+ZlMUKcItlbZbiwelI/8L5sro4/0blifbW0nP521PLMTm1UNLCN/WqmuhrNIBohmJgRFHEdne6PGzi0AaHClI0xZxRZKqyVQhrsatkT7jOG+LSBeT78BLgaqBLY5qg8HZ7nlo3MUfapATkQtQ/5HX6QpikCiz+AbXdIyd0n3QnoMeiV4vNoyyq3ScpZqJl4bcptZmxMTeIisUKk2t2U+ICLsas19IxjAbIGHg5SVixyz6dPphIQKqGvioG7YBg/cIJnI1GT/pMnKquHFxCF9JnNuboYcI5VzRlN+Us56qao0uwJCFJ3KoxC+H2xAz/SBt7NReSzL2rzxd6XXFOThmrdP5RsW1s68fJliDs8JQn3ReQC/k/3aWuhkaTQOxjon56Yfun2Qze7RchzwqcZTGsUaOgTl//mEJ7uIa+ZwlwyNyvMPd7RdxPzPPnP99+su/nXiSjP8S6kWZIWk9KWBt4U0VA1tHvl66IguEvYFg==
*/