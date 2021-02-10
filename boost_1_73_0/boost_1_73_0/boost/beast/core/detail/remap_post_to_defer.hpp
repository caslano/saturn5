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
ThE7CIJlECiJtrjIpEdScby2/33PUZLttBmCAlUQS6Lu7rnXh+zv/LirQzv05JWE/wQX7kHjozV/y8w/Lp0kn6n+g9YN7k+B9Gmt8jmJ6GmVz9QNKkmDss/PSfIU0A37xj991rxJ+BErUGPNIzNfWjUtPHWPInr15s0v9JJe777ejelYaCVLGnmpU2mnMe3nYeXXQtzf95w8jEl6EmWvMTUulCNnJn4hrCQ8lyqT2smchKNcusyqFC9Kky8kTVQp6ej84/Xp8H1Mi0JlBRtZmopcYaoyp0LcSbIyk+qutjEX1pOZQB3Gc+U8DFZeGd0DtiQv7cyxDYYXpTMk7oQqRQog4anwfu7e9vtZZUt4389N5vpZG36v8LNVJNdwYiaWZOaevKHKyZhYMqaZydWE70gIFudVWipXxGtvAKXzvrHkZFmyLegp6Wq3JY2a9MQsRnN4rDzfnNGOoRaFmT0QRB7ZyqSyGkDIA4RygzTHVOlc2iAcIm8hmpyGBP9vadb+5mQ0nKGtwYhOR1uUCqdcTFen49/PL8d0Nbi4GAzH13T+jgbDazb24XR4jNIrgFmS93MrHcAtqdm8VDJvMH/c1e/0d2j/+GR0dMjwo8IsHOEnRLuwCjnPRFmmIrtFnnTGHYEVTank0jUpW+jS
*/