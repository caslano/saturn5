
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

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
void trampoline_pull( context::detail::transfer_t t)
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

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

/* trampoline_pull.hpp
HJ6H48i5jOOpCxfmFtm7IWJjRn/6V1PzzHPHtuP0kQMYZ7qPPWV530wO4B8HXhrETGyNgQMeBhh8jLHDXfDV35CjtuYAsIx3h6+DbN21P7ZApo2PmWGrEbRqaJkApGiSR0n4GU5PTXzD9mVq169txSetcWGno2qBLfRL7J0d6D8s6ewU9gZdPbCNSbRdcWK/n0K/mRt0Kcdt6EoyrvN+7wHqZ/UBr55rszmpzIlvPvR3HuAGLa/vTnOhyKRck42CtKSE16vnErfTnVjfHS9ntvn+Fz8Y+x+DcRDPHd9iuLZZxiSg8KigeFy9P/IaP81G8fVsAl/88fXImVGN/wUUdMrYiF40GoE/jkI8wz7OXooOPXS+Cz3nX1BLAwQKAAAACAAtZ0pSKzF0S/8DAAAvCQAANAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfRk5NQVRDSF9EQVRBLjNVVAUAAbZIJGCtVX9vo0YQ/Z9PMXKlyo44HF8qpemlp3L+0dAQsAy+1JIltIYlbLtmEbsksZp+984uuG7SpOdKR2Tveph58/bN7MRZ9+Dkqz2Wo+Hgi09iPgk+uO6D5rX4jabq9YAkeYL2DwPXuB6RagiHqKdkAEdFPUHfRCVdrku9
*/