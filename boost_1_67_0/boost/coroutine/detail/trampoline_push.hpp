
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
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
*/