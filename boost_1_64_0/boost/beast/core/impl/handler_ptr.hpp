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
ESQOmitRgfjBhGFha+uB1Gmb4/BUywyPjlgBfIPG4iM1zmN0wFay3QGnHmjDGXJGNnu2dhkmuyc4GGUxiyxQnQNXuZ6r/+QUo4Cdm2wocNTS6MOY7bxKhCsGn/x3EJ+zqNOMGBoeEQOVO3MQtJcCO+nQIrPWDbXUnJhROe2x8xTE5sQUspwRENjcSYSVIFOoS8HHcR0cl83MWhF84BawtkftFqhlmvWTCvOxTh+jhbG7RP9paAqGZA4vxrxnR5QwvLnU7+KmK6g1vbFlUqvYGKHDkGXsR4c1CxsrnH9b6NdlBeAsrsTvy72wNg6zLPVLufCCqmJIT2RCy/h6tyZhGN2G8/bbRCYgRWArY6+ZrhT+D3WMy0baW/1r4B6Inp5jFHAytcrJPLM57FQmKtvZOjFD7ppgxRVPG27G5mCOCKEur709eyPhvZ73ZtlQ6qDNsmHbVbdnv4+kkYRSlg37i+RyWXTK2lnj/3Sd9JTICPVbDX6AeStsiYSkEDa4/zwkjhj2BAUW5AudTNDeM74A8LMh20Ozkm1U0PKBowzHW7ejmD8JlP+2s+ThYg==
*/