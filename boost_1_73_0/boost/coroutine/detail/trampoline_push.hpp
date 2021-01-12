
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
sbN5r35RynGyp/3ss93gx5TB7sayt2PJTP/5Sdz6tjFTXgPkelfKtoWpvzpuW8BO5vTlGCpuW8XMYY8Uu6b7pT1G59jIE+eSp5rbqOpEHK172qCHwxoC34ZfE8bcyrI1QwiXPHO6YmPkNTJewi2a/kJ8AR1kj7Ausztb7VRn0g4JZ2ioDTnub2eg9yRs3Yv50K7LWsqgf9/WcpcyDUX3glBZN7K/gTxdLm5eD0fr4hI5vzlc
*/