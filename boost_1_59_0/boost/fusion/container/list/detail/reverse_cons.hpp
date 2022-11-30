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
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
*/