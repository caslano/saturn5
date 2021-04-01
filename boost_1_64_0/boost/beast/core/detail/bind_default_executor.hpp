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
rYlnX65agxyi+WOp26MyitSHhyamk5A0n7bP/3UWWsteZ2IdgEdf2VpqwWc32m+tMvHubGvWgQ15hOFjR3VBjwQ6aPLOiahdsRAnS03vRvkXio8WTtlPPDt5Xrel6+5tVtzo2V5LsSnGHwx9xqTc5iBTbzyCJk++UtOT4kbihOpvgKuR5+zKacOXrxBfo7T31fvwpZftwXfR3S1aaAvaRh3ljcZErNEGpC2iGJ7NTwUUK1/44J5QQQKhIk/elVANZ8IWGfILzqOsfDqMfDk3YcQa6+6tKXEJrii6rwTMjCNy1pGkpVD6zKPcOtmij+EoH0Ko3qMFBTtRolsmSk0XL4Ye3lkTSYgzH+g6e5Fe2PfZr0Ha6gQ28UYNdzq3qTE1jpJQllfrdd5D/Mqg81Gl+fxziy1xF803lg4lDSfdH90fJeK3TimrY7rttc/MlNeYi8is/Ie6+1+KSkqwjWVE6lIAA07NACBzebGdHlcYhcdyQeysQLQdDRYSJazSKjd6Ozi+vAGAiKjQdcGVN1QvoxW1WZy4LT3d0FsDZpPmuoBvhzg1LmWB55MVSA==
*/