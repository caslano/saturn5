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
A5r7z3gtkx39mFQBtIC+albyFdL4p/BG4ZzysI4e0sCHEeBnX0PNa36yaq+Lz4sDutDn8dofiS6bAnL/g4uoeoQPh7qrQ3jgH2NlVKW4mUvkswR9kLLEW2jLgqYMivEFSs7cB1sB4CTX5ncFIG6libtx89TOydbZebvOYiNSKT2dD5eYgWGjOCSyoOBYlhpHiutZkpn4LOKbycdwAyhJR6cNn8WgmbGnzSj+ZGP+/Gz3c862Q1BZJ2yngTxQmuMxn2mjeCPfzmoBDvUG1XsIJYHWIIe5+Zs93BTBUqOkPzGVdMvwCUq6j0MZrU2yAOU4I8nX9krvx/GmarjMhRvDverHlSojrQsTA52NXZ+lKv09z8p7XmKHqyerpi/m+2NH626kX8zzadfqLTK7QZgnUjzRR6ROp21knv1qD2neFxT1TutkQmkWAiazi35fjSbkyjPwpYmeN1uUP27vwiRGVETuR5GXtFDjVoxcWlbWa1pWltfVLEB4aBdwyq4ty1SFelxXxA3AI/p6Y26v5x8MQeu4McbDr3crM/kCd/cL5No6TaVbP6e6So92r7l38CDehTugiJIg8uqqrifcCftPhKhmmbDtaMxOUhspZCfkSC/xturl6kmbWjHSTS5d4Lye0ZHhJknctcewIgdWM7L26BgotypnrjS3UeTFv3G7NmuRROijOzB5m3t9+SVlU3dtvX5BQy5dh9bBcfX4
*/