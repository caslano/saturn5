//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP
#define BOOST_BEAST_CORE_DETAIL_BIND_DEFAULT_EXECUTOR_HPP

#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/core/empty_value.hpp>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class Handler, class Executor>
class bind_default_executor_wrapper
    : private boost::empty_value<Executor>
{
    Handler h_;

public:
    template<class Handler_>
    bind_default_executor_wrapper(
        Handler_&& h,
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
        , h_(std::forward<Handler_>(h))
    {
    }

    template<class... Args>
    void
    operator()(Args&&... args)
    {
        h_(std::forward<Args>(args)...);
    }

    using allocator_type =
        net::associated_allocator_t<Handler>;

    allocator_type
    get_allocator() const noexcept
    {
        return net::get_associated_allocator(h_);
    }

    using executor_type =
        net::associated_executor_t<Handler, Executor>;

    executor_type
    get_executor() const noexcept
    {
        return net::get_associated_executor(
            h_, this->get());
    }

    template<class Function>
    void
    asio_handler_invoke(Function&& f,
        bind_default_executor_wrapper* p)
    {
        net::dispatch(p->get_executor(), std::move(f));
    }

    friend
    void* asio_handler_allocate(
        std::size_t size, bind_default_executor_wrapper* p)
    {
        using net::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(p->h_));
    }

    friend
    void asio_handler_deallocate(
        void* mem, std::size_t size,
            bind_default_executor_wrapper* p)
    {
        using net::asio_handler_deallocate;
        asio_handler_deallocate(mem, size,
            std::addressof(p->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_default_executor_wrapper* p)
    {
        using net::asio_handler_is_continuation;
        return asio_handler_is_continuation(
            std::addressof(p->h_));
    }
};

template<class Executor, class Handler>
auto
bind_default_executor(Executor const& ex, Handler&& h) ->
    bind_default_executor_wrapper<
        typename std::decay<Handler>::type,
        Executor>
{
    return bind_default_executor_wrapper<
        typename std::decay<Handler>::type, 
            Executor>(std::forward<Handler>(h), ex);
}

} // detail
} // beast
} // boost

#endif

/* bind_default_executor.hpp
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
*/