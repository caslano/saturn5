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
TBV2axHxMi9GcU7G3kgRQpgt05EMeYNsOZYBsTnDiAomkSFpMPgborAzsdwOIhGHpHkhVcN+oMlk4jtu+vTZIIDmXs4I91hG/NY4sSY0gZABArOcYxtAwpY85yRVxI2UnHvPsopFg7gKSRzfLaQBNm+Eg4lZCI98T5CGGcOGorIDw66BMoYxcHLkT8+gUoZ/9nJiqtDtRaO+02q39I6GupfHYPOu7yPRmrC3sWDF4s824ATmpg+OI7PRRrGivdw7UnwilC4iseesgHssNlZE24SqYmXJRTGyXKVJUEJ8YHGW774tvDu4qu/oqzp6V7L/4PkGUnO3gIJ6qfPuXgwPr5Ji023xGKvyQdpCyXXy3LhD5mH+UiXneHDgJMFY4PAPmWF03AUPkpk3FTZnYVHeN8NEmMYzpDerG3mBTSnEtv5tJjzYYtyqB/TnYTkgd3uevs37vuk+d+v15j0jTrABq0a4kJSdWLXAQcNv8BrrAuOEJ2+mNJ69zt87avQateeSiaRBC6aurTiZ0MKPG9ey2Cu0AwcH8Kqon/65fwotmnXODitEnzOuFJr3kRhmA98f+7PJ8J/BJ8dWTAqDhm4oeciRhpJYt1+6dw82yf8cu8pBZiN1r+asoNl7kNvB9HomKGd5qDZUzQ3eBBpE
*/