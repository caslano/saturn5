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
f+3VRa88uWR02KTXk/7e/NvzGz35P1j5P7qW8n/58tDk/4zlocn/hcvrV/4v9OT/XSL/e7L/rpH9/2XvOsCjKKLw3pEmSTQFQwiIQYNSJSJqsEYERQWNCIqKXkISSDQkZwrFGhUVe+zYYwM+a1RU7NixR0XFHhUVOyoqKpZ/3/03t7u3c7mYYL3lG/7MzrzZ997Mzs3OvHlTNC1xvXz/L1qM+RyE5QirYt//sSt2xa7Y9Xd9/w/viu9/8zu//2aGfAMNiH0D/WX+zf+ub5Su+uZo8UQ39nY7v20NAsbQPKvNfbyszmZDcJ7Jpj+PDfkQJiJwjOsc0/LMNf15a8sRvkBYhxDhXLWoz1Sbi2AdSy5HMLaxjhXdxohu56I5z0SL/hy04BlosSt2xa7YFbtiV+yKXbErdsWurr/+gu9/BJ//yPI5nT7/z/z+z7Gc8VfAz4QpHqz9AHcHDsBizepr1Tp/0T67H1AwvGifMQdzrXiWrBX7C4zQWjHz56m14B7XmfHtZR97L3lSSdX0msqy4D72fJa1QtJM0ULr+HsI7ZeGSftwppkOqX2hfe6FwK2wZtwdOATpN2SA/zTYFyBcz7/XIbyFYP69gPvam9vZ196k9rXHp/e7Xtao8spra2tqLXvYITvyBGTP4jo05MM9ysf7hcCHJS95F3lHpn8osmGNcLCs1at6GMu1+pVcq3/d5AX10HK9qgezBoZLZVh056HuWA/Mn4V/gXp4UuLPG9vj/1O5X/kY0SlloM5fkHwPGYPA0xyEHOg3HukDMwM69PcM4DXUZb5+fV70d8IN4fqTvfeiK/IMfWQF8hkN1McOQfsT7tvvT3uKXFP3yNN6g00fvpKysq19JfX1tTadSPHUSZAmXdILM8x0IaAdA9Ohie6QGVFjbHb0thcBeeR5ygYBz8A9eYbINIoyNXPP/VDKZJY/BzIZCzQy+abO8e2712hDLxtpN7b4sqiutPi+YHpfS3r9HH95IL3CY0+PExuPqXPqy+sM+rJwoYf3BpF1TPp+HpGBeTxBHxRKj4MzA3osaEePhS56HKv8RUAe3itS90QGuTcZcfCNe8K33CtW+YRXWx3kJYbXwTGDUWeR6mC/UXvr64C0rINeki4TtWxfTNfXAdP1dVAYRR0Uaupgn+zO1UGvdPZhXVgHLUnhdXCcudE4Uh3Uz66PUAek3Vh+MwakBd/x6pIZ1PM+Ko++HhrbqYfGKOqhUVMP4/9kPWSxHgaIfoMydb4ugv3s3A0MuXJYF+bN41EXSx11UYahSX251IauDkiTbtVPTWmoL2J6jtLJfp3sZykTnmGXaXL3cJkaIVObQ6bp5fUBgdiuKjPDZWprR6Y2h0wHdECmysz2ZdqFMlUlh8t0EmQyFrrLxJ8OnVykS9f9bjA9B3wpuUvq6v01dcxTwTKssk/qEtkDfHAMxXt8tkMnjSnhOpkLneRqdMKuXKcT0qVr+/HcKHSS69DJQZ3Uiep/o9RJXqpL20e5hTqdiFmktv2TLl3Jc/CflCdod9n6N645uq/9rf+1yLR4WVMrunLMqhurRjQNaX3hq1/P3lK3Rrn+1yJnBfZdXnfCno1f7X3XKWMnbPvCsMw1OrtLnX3oP88ec33bXWrsPcUec4nBb2B+Szci9DBtsPliZOFWHv2e7Eo7x31p33go/ZvMob+T42l3eTH9mCwG9qd/mC2A79JvSRtwEPBL+mn5GTiE/mKGArsDRwA3AuYDtwZuDxwJLADuDhxJu8wWg9+O/AYF//Idej3534V+YHalf5VC+lfZDYhgHGSWB5xMucYADwLuASwG7gmcARwLPAa4F/3fHAA8FzgReD7prwSOA95EPzm3AIs=
*/