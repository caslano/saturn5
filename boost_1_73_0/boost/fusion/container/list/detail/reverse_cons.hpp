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
LdhY1Ao2vrcSG2c3sbGutrgkHGjjnBZsnN0KNs5NWcn9sYmNM2prV3Ku57dg48WrYGN8rNTA9iu5PzaxcaZc2OwKvke2YOfCVbCzrb0jzWzvEr7R99OufveYbTotu/SDqzbIGr7AviP1vyPdKf7bru2uHk1Bh2ljGKPjmsbCNeBuMAvuDrPhOJir2/H8FjaT336a3zTNr1rzi2h+VZof2ya/hmbyO0zzm635HaH5Han5HQ5z
*/