
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/move/move.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/setup.hpp>
#include <boost/coroutine/detail/setup.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline_push( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);
    BOOST_ASSERT( 0 != param->data);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run( param->data);
}

template< typename Coro >
void trampoline_push_void( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_PUSH_H

/* trampoline_push.hpp
T5Ij0q01Sf011MHrRG/R0kZ28WNR7Wp2Vyjojwcwurj4Ht7B+9PRuQ0TUjLKIVK03ND6zobLzFh+KsjjoyPpRxuoAsKdZ4BxwSRIkasHUlPAPWcpLSXNgEjIqExrtsEfrARVUMgZpzAO5ysv+NmGh4KlRYezEw3IQjQ8g4LcU6hpStl9C1ORWoHIEQHxMyYVYjaKidLB9BQUrbeyg9EkCJcCyD1hnGwwHVFQKFXJH4bDtKk5nmSYiVQO070UTqG2L061QjZbsgNRKVACGklt0P42bEXGcr2iRGismg1nsrAPtDBhmQ1FDZJy3sFhKKOyPQKFqFPL1p5QIXum9CJFKXW2h0JsnzmirB1Q3tQlpkNZ0C8TKLwNTZnR2vgbIfZZOpWN5F8o2YF7BqJEVtBzI/CiHmyIZNKGWy++Cpcx3LqLhRvEKwhn4AarDu/aCybYGwyz1kAfq5pKZFED21ac0exZ8q960y0nvoLxcuGH8ziZBTduPL5KJm7swhn0RhfwS1Pq3v6uBz3ONrr4cO6cnTunaNC/EkrkLpFU6TLjBztKImh0BYF7M7VeRV6/g7SRCitUCVYqrbyAvNwSlRaQEs43JP3dYESrIJxHXmQ5ZW59w8qUNxmFS524bcTio2VypALtL/n09Rs4KbBF
*/