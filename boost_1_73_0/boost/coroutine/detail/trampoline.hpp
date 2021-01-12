
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
fgLr2tjDTOjY11FZr9EJAasCM7AVbQqzqZj7T6/KymmKqSjZv/to/j/IZe0Pmayfuzdmjx7IX2FmYa7ArMRswOzEpPbkOxBmFKa0Z1zOKn7Ej/gRP+JH/Igf8SN+xI//teMXlf/PKSt3JHbzKhcA/Cz5f9kDMJP3v984cwcz8/Km5ebMJs1p2H/emO9/Yl8xBytZKzDArBWQ74NyjNbvNqN0ryQWTJl5KIS/c1XDYmleLt9p
*/