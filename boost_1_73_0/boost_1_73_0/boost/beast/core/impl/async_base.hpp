//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_IMPL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {

namespace detail {

template<class State, class Allocator>
struct allocate_stable_state final
    : stable_base
    , boost::empty_value<Allocator>
{
    State value;

    template<class... Args>
    explicit
    allocate_stable_state(
        Allocator const& alloc,
        Args&&... args)
        : boost::empty_value<Allocator>(
            boost::empty_init_t{}, alloc)
        , value{std::forward<Args>(args)...}
    {
    }

    void destroy() override
    {
        using A = typename allocator_traits<
            Allocator>::template rebind_alloc<
                allocate_stable_state>;

        A a(this->get());
        auto* p = this;
        p->~allocate_stable_state();
        a.deallocate(p, 1);
    }
};

} // detail

template<
    class Handler,
    class Executor1,
    class Allocator,
    class Function>
void asio_handler_invoke(
    Function&& f,
    async_base<Handler, Executor1, Allocator>* p)
{
    using net::asio_handler_invoke;
    asio_handler_invoke(f,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
void*
asio_handler_allocate(
    std::size_t size,
    async_base<Handler, Executor1, Allocator>* p)
{
    using net::asio_handler_allocate;
    return asio_handler_allocate(size,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
void
asio_handler_deallocate(
    void* mem, std::size_t size,
    async_base<Handler, Executor1, Allocator>* p)
{
    using net::asio_handler_deallocate;
    asio_handler_deallocate(mem, size,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
bool
asio_handler_is_continuation(
    async_base<Handler, Executor1, Allocator>* p)
{
    using net::asio_handler_is_continuation;
    return asio_handler_is_continuation(
        p->get_legacy_handler_pointer());
}

template<
    class State,
    class Handler,
    class Executor1,
    class Allocator,
    class... Args>
State&
allocate_stable(
    stable_async_base<
        Handler, Executor1, Allocator>& base,
    Args&&... args)
{
    using allocator_type = typename stable_async_base<
        Handler, Executor1, Allocator>::allocator_type;
    using state = detail::allocate_stable_state<
        State, allocator_type>;
    using A = typename detail::allocator_traits<
        allocator_type>::template rebind_alloc<state>;

    struct deleter
    {
        allocator_type alloc;
        state* ptr;

        ~deleter()
        {
            if(ptr)
            {
                A a(alloc);
                a.deallocate(ptr, 1);
            }
        }
    };

    A a(base.get_allocator());
    deleter d{base.get_allocator(), a.allocate(1)};
    ::new(static_cast<void*>(d.ptr))
        state(d.alloc, std::forward<Args>(args)...);
    d.ptr->next_ = base.list_;
    base.list_ = d.ptr;
    return boost::exchange(d.ptr, nullptr)->value;
}

} // beast
} // boost

#endif

/* async_base.hpp
Vk4mUB2UprcFh4jmiSLtqdyL8wiwA0yzEpMp4QFwwySTWlMNoChE0OqVD2GyUNDvPxcwt2JQVHkYReJOkp9bN6aAbQySXJKwV4kGFOXdS9qE4pj2wxy8Sa2RjKcIM8Z2IJeGo+OjV38U/szLYKsXpYOmi0xGpNVAzhMKOmAeuGcSwCMJ0QMv92giM1kRJPleBnkodkiIJUIJFsSiO8+/h5QI48YfwtiPFojW1yoPwuRw9qY2lGFr62MBImBtbKW6eTiX9dHNkQUwNw8216ZJFNVHyc90ZqkNc7y96vKf3U9cyL3w1yZMfJh8kzVcYZ1SlsXresBEP5ATRcONP+AqjKV4P37rEqRjSwkiDYg4ljHlYzgfzKiHHbJkPJVmBMRFOGGnW8IHCUkbhKVvo+TOi3htNmcIogw5nwOKsJDs7CdxjGoppMSGVfkqlZBD6K0KVxPoY33jNzieGdbqQAqSoiMf6O/p2kOOFZcvNx6RAbPy2QU89r3ocPTTPVBIR4BrEI4Gr/rXPdFh7CnnJCmEPW08ilLKU73vfrlhQBUyROhRFHDyAX6k0g8noV9Fp22bv4Buiq2TmNgtVpAAFEeiA0eim5K96Ez5upgCwyTZF1rr9kaj4cgd9//R+0YyW+I/J7FJdluEHeNJISzj
*/