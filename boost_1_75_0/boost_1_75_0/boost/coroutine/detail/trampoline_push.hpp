
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
nJ9PAPD3sbS7q5ujvbSVuantu39B/NSVesm9B+fN31gRlWCl62Hm+3k8yUzvZd0Lejzu+MHx3Nt8rMgErtHplzrxtsEd878/vqpqxaZlj9WYq1//pSDex5cVMUuEm/A2LtbyxONdohQDYnbUrZgeHA3vs89QlrAWs6YpOJL0qMNUCN8upJdI9D1s8aU/ynY9bzvKHtr9LYVym8MB+T715SSWu/0U/Kk6xl04qoGDztVEur99oDp2UK9hgHSFaxZJMfm1OugNisEvVZb8MPIpZ4KsZBsZ0cN9ie+ZAC4UDJnEmbJbhJ1bbFcglZxYN/DrT4D4T2Col/Covvvb0vTmlz0dR2UgfXuiWjj99WFIquehuCMWyB6BLzjbP9A5par+RrU4/lWxL6a8M5q8WT1VplXaki10S9ZPyWTq67BExOvry+cvVwt9ZxfdnxxdJjUME9AHcdykpoH1WohUYvHwApDTdoEV6MzDbwN+mo36yy7QExkc3HCpfzYUvBUH0wsjWF3KA9Hv2mkkIwPFL2lP54gECdVyvlYEZGzauN70UK+lL1N4s7mIL5J6Wz1sFXScUA1pgaXImuoIEXiMv10XZnqAcJMzlee/ZTxYiFvlAJJCAn58ndmO7p+iQV0tjHQ0Nt25BHHuBgwCBjHCcUhyPtjJS8g8LIIwGRnpZN2Y6Jj9VCVioR/P3rg5ktZTX2LuKgxqhAPDu0KkTNsv
*/