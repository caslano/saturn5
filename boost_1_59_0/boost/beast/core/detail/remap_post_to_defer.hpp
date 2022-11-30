//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP
#define BOOST_BEAST_DETAIL_REMAP_POST_TO_DEFER_HPP

#include <boost/asio/is_executor.hpp>
#include <boost/core/empty_value.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class Executor>
class remap_post_to_defer
    : private boost::empty_value<Executor>
{
    BOOST_STATIC_ASSERT(
        net::is_executor<Executor>::value);

    Executor const&
    ex() const noexcept
    {
        return this->get();
    }

public:
    remap_post_to_defer(
        remap_post_to_defer&&) = default;

    remap_post_to_defer(
        remap_post_to_defer const&) = default;

    explicit
    remap_post_to_defer(
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
    {
    }

    bool
    operator==(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() == other.ex();
    }

    bool
    operator!=(
        remap_post_to_defer const& other) const noexcept
    {
        return ex() != other.ex();
    }

    decltype(std::declval<Executor const&>().context())
    context() const noexcept
    {
        return ex().context();
    }

    void
    on_work_started() const noexcept
    {
        ex().on_work_started();
    }

    void
    on_work_finished() const noexcept
    {
        ex().on_work_finished();
    }

    template<class F, class A>
    void
    dispatch(F&& f, A const& a) const
    {
        ex().dispatch(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    post(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }

    template<class F, class A>
    void
    defer(F&& f, A const& a) const
    {
        ex().defer(std::forward<F>(f), a);
    }
};

} // detail
} // beast
} // boost

#endif

/* remap_post_to_defer.hpp
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
*/