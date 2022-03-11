//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/allocator.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/assert.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/exchange.hpp>
#include <utility>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------

class saved_handler::base
{
protected:
    ~base() = default;

public:
    base() = default;
    virtual void destroy() = 0;
    virtual void invoke() = 0;
};

//------------------------------------------------------------------------------

template<class Handler, class Alloc>
class saved_handler::impl final : public base
{
    using alloc_type = typename
        beast::detail::allocator_traits<
            Alloc>::template rebind_alloc<impl>;

    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;

    struct ebo_pair : boost::empty_value<alloc_type>
    {
        Handler h;

        template<class Handler_>
        ebo_pair(
            alloc_type const& a,
            Handler_&& h_)
            : boost::empty_value<alloc_type>(
                boost::empty_init_t{}, a)
            , h(std::forward<Handler_>(h_))
        {
        }
    };

    ebo_pair v_;
    net::executor_work_guard<
        net::associated_executor_t<Handler>> wg2_;

public:
    template<class Handler_>
    impl(alloc_type const& a, Handler_&& h)
        : v_(a, std::forward<Handler_>(h))
        , wg2_(net::get_associated_executor(v_.h))
    {
    }

    void
    destroy() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
    }

    void
    invoke() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
        v.h();
    }
};

//------------------------------------------------------------------------------

template<class Handler, class Allocator>
void
saved_handler::
emplace(Handler&& handler, Allocator const& alloc)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    using handler_type =
        typename std::decay<Handler>::type;
    using alloc_type = typename
        detail::allocator_traits<Allocator>::
            template rebind_alloc<impl<
                handler_type, Allocator>>;
    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;
    struct storage
    {
        alloc_type a;
        impl<Handler, Allocator>* p;

        explicit
        storage(Allocator const& a_)
            : a(a_)
            , p(alloc_traits::allocate(a, 1))
        {
        }

        ~storage()
        {
            if(p)
                alloc_traits::deallocate(a, p, 1);
        }
    };
    storage s(alloc);
    alloc_traits::construct(s.a, s.p,
        s.a, std::forward<Handler>(handler));
    p_ = boost::exchange(s.p, nullptr);
}

template<class Handler>
void
saved_handler::
emplace(Handler&& handler)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    emplace(
        std::forward<Handler>(handler),
        net::get_associated_allocator(handler));
}

} // beast
} // boost

#endif

/* saved_handler.hpp
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
*/