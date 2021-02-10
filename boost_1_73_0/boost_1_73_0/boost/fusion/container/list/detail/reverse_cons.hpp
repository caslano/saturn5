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
V2GUL7tV6TQlvzTkv8avb8R5u2zULxZ+SjdGgR0SWsZPpC+H0Nx/PwVEd8O4zbn/eJQruhoSo1jffmuqZnEZXkqoZKIThJbHoeQ50eN/3P6fUZPRMh5R5YrCa0vynSDjskZs/DdpilRrimdldbug2U+oPMuirq6o0DdUPgzrdKZfp6d2Z6U7pl65C4BWVAdjmbhSvtuxs5GuTUopfLWGSFJyh64rLhj+i7md1eK9FSqrzyDsvsGEQJVHdLk6eUgwam2DHFMIIDEZA0HrySCatmfzI/qmEuFOp6P6bWiqsQRFsKWsUtMMJ6rsywot21WxMKc25he2falxei91kQwHmmqlokdiu2UP0mILXdHdFYqeTpgFgYaK4mL/jETY3N9YSvWtNVVd/ci7kskWFFUTvIvS5frAwwRzCux8Obqaqo7n18PT6WA0ZHOBsEtTXY0uLpxx/3L0pa8Hz/g8ijlt+vkZKpMIb91AoFuVaQmZYB/8/zlG132a4nQKZPUvqnQjSIU8JvRViqTMQfGmqm15o/G4uE22MOycxJZUIW0ttZkx5tSv6nCmpQtA4Fn5ndb8dOnSRTMQx0rmXbJehLOoCTqlsyIJkIktQ210QtaPdK4zVj3PexeTPhqo52LCP6cMOcPbblT8vBPQOh1f
*/