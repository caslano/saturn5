
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
+q6cgKwADIQl1Iyrr+mZofGZ+OaZ2+ePjKZZxwIHLP8QuhI2mepQSUXVyJS4jgPy6OuOadg9NPHmlUeWVG6FlWi4l5AMCLNctY9Q3YXt5WrEa2jcsWpuVeMhefL9XyhbDZDRyM5ByZw/BWE3qb09+ZCZo75HR6ijmicOghYYvMpLHNeHzO6WQb03Kq6Z1j6mn5lVQYWsbAONombxfLR+3QnBxe6oM6tnhI9zjo2gRsdb0K2o3bKjb4keOuZY8E10Sccf80Rz+NO3vuHLFnYtTlOp9wdASogsZOijVsf+OPmLGT9tnphPn+YZDHeFJIye7SYo6l82KnXGjnxOinfWVttPwWeYxQs3vHlxPsreUR/jTZeZ51kdf60B9tY/lLGNoSTJBLbdtH4Z9KFoD5F0HQqfsTOmgpS8cmfNYN/30587/khIw0vhokKjS1zv8UFSh3MtmXM/VyBfDhYUzTfjuipANgkwk/WXzPpzVUW+oaR4bg6Lbutjy8dDTdas+LuMujf7k5PQqs3XfThAPO/B0tQ8WcJFNDfjaDmJJiWDTsvFCBsWl+MsGgjF3Ghp6qnOdoFlK1gc05Kn6+eXfYaS/SxOHttUoMYqlk8uSUpIp+7EVx6Oru9rrEcTYNOjapocsun+lPAyAaaceDFXyjegJUlRa3oFejIXuYZs9mVB3krM49bJIgJ80c3ddJdnotUIumNr/jDdD+xdCRCL
*/