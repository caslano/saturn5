//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_HANDLER_PTR_HPP
#define BOOST_BEAST_IMPL_HANDLER_PTR_HPP

#include <boost/asio/associated_allocator.hpp>
#include <boost/assert.hpp>
#include <memory>

namespace boost {
namespace beast {

template<class T, class Handler>
void
handler_ptr<T, Handler>::
clear()
{
    using A = typename detail::allocator_traits<
        net::associated_allocator_t<
            Handler>>::template rebind_alloc<T>;
    using alloc_traits =
        beast::detail::allocator_traits<A>;
    A alloc(
        net::get_associated_allocator(handler()));
    alloc_traits::destroy(alloc, t_);
    alloc_traits::deallocate(alloc, t_, 1);
    t_ = nullptr;
}

template<class T, class Handler>
handler_ptr<T, Handler>::
~handler_ptr()
{
    if(t_)
    {
        clear();
        h_.~Handler();
    }
}

template<class T, class Handler>
handler_ptr<T, Handler>::
handler_ptr(handler_ptr&& other)
    : t_(other.t_)
{
    if(other.t_)
    {
        ::new(static_cast<void*>(std::addressof(h_)))
            Handler(std::move(other.h_));
        other.h_.~Handler();
        other.t_ = nullptr;
    }
}

template<class T, class Handler>
template<class DeducedHandler, class... Args>
handler_ptr<T, Handler>::
handler_ptr(DeducedHandler&& h, Args&&... args)
{
    BOOST_STATIC_ASSERT(! std::is_array<T>::value);
    using A = typename detail::allocator_traits<
        net::associated_allocator_t<
            Handler>>::template rebind_alloc<T>;
    using alloc_traits =
        beast::detail::allocator_traits<A>;
    A alloc{net::get_associated_allocator(h)};
    bool destroy = false;
    auto deleter = [&alloc, &destroy](T* p)
    {
        if(destroy)
            alloc_traits::destroy(alloc, p);
        alloc_traits::deallocate(alloc, p, 1);
    };
    std::unique_ptr<T, decltype(deleter)> t{
        alloc_traits::allocate(alloc, 1), deleter};
    alloc_traits::construct(alloc, t.get(),
        static_cast<DeducedHandler const&>(h),
            std::forward<Args>(args)...);
    destroy = true;
    ::new(static_cast<void*>(std::addressof(h_)))
        Handler(std::forward<DeducedHandler>(h));
    t_ = t.release();
}

template<class T, class Handler>
auto
handler_ptr<T, Handler>::
release_handler() ->
    handler_type
{
    BOOST_ASSERT(t_);
    clear();
    auto deleter = [](Handler* h)
    {
        h->~Handler();
    };
    std::unique_ptr<
        Handler, decltype(deleter)> destroyer{
            std::addressof(h_), deleter};
    return std::move(h_);
}

template<class T, class Handler>
template<class... Args>
void
handler_ptr<T, Handler>::
invoke(Args&&... args)
{
    BOOST_ASSERT(t_);
    clear();
    auto deleter = [](Handler* h)
    {
        boost::ignore_unused(h); // fix #1119
        h->~Handler();
    };
    std::unique_ptr<
        Handler, decltype(deleter)> destroyer{
            std::addressof(h_), deleter};
    h_(std::forward<Args>(args)...);
}

} // beast
} // boost

#endif

/* handler_ptr.hpp
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
*/