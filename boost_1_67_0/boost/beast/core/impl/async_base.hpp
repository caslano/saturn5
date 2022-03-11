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
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
*/