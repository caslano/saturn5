
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline( context::detail::transfer_t t)
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
void trampoline_void( context::detail::transfer_t t)
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

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

/* trampoline.hpp
GnJQrWT/PJsymxeE13d/90Xumbd2GsUhCU9KxkfIqUxf3bvCKLOWF4iKzCok6+Uwdoh49eIfosDAWu8AxzlcCQ0oU0aHEjy1OFnRq7k+Tn2Tw0Pw5d3Ye8MF52AN7gxBhL9qy89je00GgNVJ1IwNB/zx8w3kxwSXJG6TPDhMa0WwlKKDjZXbTkMnzFIw/M3xoVYZisA7GvdazTs1JT4DJJyLxarWWtl269afY/msbEgoaOYtGHhINZtgy9MZdegmX7yQR2EsS9QV8TE11Oarn6sn0TdEl+AkfvIhGl1siQx9r8G5EfgVPtv35bN8bc/vGbxOZmFG/k47qU46zAoUkCCd4WZpvCLNaUWS4ib/mXvzuQ2FFaMkHpLzxTqKu5nPxk0o3enFKqBFLxmIngK/Sutjicm4PASmWyCtNbwApa+Fz1KJ6Fh2M5cdFVLcxnkT3tJPuSoK9Mw1PYDTmZzWck6jmBgN+qJilqr2+XZXWqnbvYHb+JoEhNJ4lBgw9vcpxkqf0deSeuu837COinnceGOot0znz9vi6oT2k5Lj6Ffu2az+dbgFG6AHAQ==
*/