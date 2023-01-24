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
fnYU9MFtz5L6o7lWqWNwLleUMnfhEXq2nmpNPSVX//XA1+hpwwyYrH8WArMr9jtF0cczRTPm3VukMAg6FbsV3ip7MrvVngcn5bFXHCGzDcFI0URxSaULdYVezmyAk2yGoMPe/sixSqlQ/6pFeULG+b7KyZrZqdNHZUEZMHW8QHK9g8FzmoTn7LLn6B/pinmix9AzNSpnlpEaAlrQrDh21FtmJCnVHzyl4WTtF4szw2kmxDkG0VWV4zJWeS3iMuWHbGiLtiATvlqVmkq7w+fvkcWyCdxBZUmYqAxf1vPDsxo+EbiG1fAOn8qyWsSJXrnfxeO/YD+RM1vQavBG8kG2dcWOZQ7FQlI57r8rob3mMUppJz8TFfKY/26TqsmuE32q9tw8lI/6+mGJ1sW1vze1WFZAckuAjcd5juCEtqxthpNAKs7sM5LdIMSEym8dJAG27i6eDjRMIltCrmj+5dlz+bSEeiQuzI92+OOzlBE62U8UWJMICXO3uAP2BursFbMH98s2lQeLwB+Uu/HuhqLFiDpu6F/2i7bYjywnewm25K9IfPAMAqtyqvxIO+E3A+17mrb5r3yf4N9Q/DC7pLCg7HohXb0Mb2fPutPaItdNtRFPr4rUOyzx18k7VyZsmMJ0JotFZgoeOgNBXcM87UoDvxDZyIJNBc6Sr58zIvIKI/KUhz3eIyIWJ1mv+c/lFaaKtK+78KWdd6XtIHdz
*/