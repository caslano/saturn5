
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
huU68l8dO61CaJSm7ZKvft75F1/tICY0GuClF4SW9VNSGJYR4It0E81FfMNah2T1r4FM7UM+nyMOs+y2VkwBapOuLUnak2kGbAdUXyvG5SVI1gzUl39AGwfDhHRrJxT+wq2OrfUm6R4mLVUV1vtwuMXfM0FQIOFe3Q59A1OG+tQdr7/O30fSvppMix6zAyZXb/1D5TGRf3msokfYNZmGpc/mzhonK1WIP03fjGbvclnjNQvKyj+jbScWvXJRBU9InZ9C++PEt+MajjhMnBLTVv0okE+UKSqiVmIG8vka/51BMAYsESWa7nqpokxIAytznJN9rElYsduvOslyTQNPv9MmkFW+PeqxCf33MJdIZUg5oWD+1jj1602WOHNOofvehiTfZhCpLRqyJhby7WVUKrlZ0uLg9IcJLj3MUc4EwXii0jRr3mFhYG5Gnvsz0rSZJYzDyPjFSzI1xkF0tzz8WzWWuD+zxngJy4dI66SLbDJRwQwA10UjMb4EjKiPhNw7ccsvULuczHoxNrkYrSI8ENycLcgmsOwB0yQZpFNWy8zOi3nPPGEUTqcgAA==
*/