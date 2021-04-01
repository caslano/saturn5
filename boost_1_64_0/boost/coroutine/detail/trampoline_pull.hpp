
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
qC12wr3PjAOGoU6nWCnxipvpFUi1LDZqz5eUiewKnKER5sxxKuoQt0AgHnOe2mKdmgwqt2z2vUV91aRfrIHIKSVWYhN9TK1jqiIY+oBsyYglwfi7jVvD9W4HElEvvCW1Ih4eDwcg8Y+f+IFbEZe7MriP5sqW7nPskRMq+NyOMAjqoaQoanZrTgsRzO1c2WZXOtJz6D5DlTlKOcxcDCa9SPI13K43lN19pzc2sgZhCitTFN7pVF3D9EHTT2N8x4RJwxbLwNLxePqjl/nie+hNy02A+rQFta0XTkvkX4rqoaIrFnqLX+L+7KgPlOCGsvjnv2u/iqHNHIy5ylWpCnsUzM9gGXQBM8I5CVgMPkYhXezj4FRanfblznL25SfWAxTpNTro0F6KBYeBdt/yPBYpeDtusB/vm9BCauS9JPSX9V3oYA09JGpzttJvMyGDOJgNs5j5mYEyxigTiZAoTs4Yv3X9sHVtK8ioRTqn603eC0WXfhzW51nasXsWmvin6bbkQVNZ0nohYFmG892vLDqU0VZVOIPpgvjeSbG+Ey6+hKXA/T8sznmKF/qg1g==
*/