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
L8PUwrf95+/kWCJsDs9pUamTsfAnzh3z+gcNNNJULsnNztaF9HjUY3tpKj9htWG6Pz+zb2Pd2B7QmplRtCJG5bdnZ6QddYGYBJKr96ofh0xIWl6ty0pIV3DUZYSk0ncNEuOkIX+nc7cANDdxxpI+8Sp+NqgdXUDxgdNlYIol3lD9zTTQviiBMMc7Eg3SGWhgSqvRSP8SWVoCnsHh12xSl31vcy1in9W+ob9rNDaxBUqS8vvvKxogmd+1JgxfrdpIstvmo9rctindP+7WHHfHkwqFLPwO3i4tRxqXYRLugE3chiRPIjFGg6CvA42oRr9wI/B05vOiA+vcO+7uciMWqlH7P1q4xVPnCZZ4U9dmCL4UO6JbxZ1/oVMwha/S8p/j2fBMHwFS3kpRd1+DrIHwwit2zGB/zHgoDxoW54IIyVECK1s4fg+ziSmq7ymuE6blBLax4DopFCUP/KG8zUNtQQPQvP1OP89GF7K+WlgEPH3uU4RTz9/SIUKctLjvWhGFkqkVLqJVYaWs1vuQUzBlLfqfKTZJYWOqurmS3OemGv1P018yzRJS0qSguA==
*/