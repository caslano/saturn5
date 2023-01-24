/*!
@file
Defines `boost::hana::always`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ALWAYS_HPP
#define BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return a constant function returning `x` regardless of the
    //! argument(s) it is invoked with.
    //!
    //! Specifically, `always(x)` is a function such that
    //! @code
    //!     always(x)(y...) == x
    //! @endcode
    //! for any `y...`. A copy of `x` is made and it is owned by the
    //! `always(x)` function. When `always(x)` is called, it will return
    //! a reference to the `x` it owns. This reference is valid as long
    //! as `always(x)` is in scope.
    //!
    //!
    //! ### Example
    //! @include example/functional/always.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto always = [](auto&& x) {
        return [perfect-capture](auto const& ...y) -> decltype(auto) {
            return forwarded(x);
        };
    };
#else
    template <typename T>
    struct _always {
        T val_;

        template <typename ...Args>
        constexpr T const& operator()(Args const& ...) const&
        { return val_; }

        template <typename ...Args>
        constexpr T& operator()(Args const& ...) &
        { return val_; }

        template <typename ...Args>
        constexpr T operator()(Args const& ...) &&
        { return std::move(val_); }
    };

    constexpr detail::create<_always> always{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

/* always.hpp
bTa2tvy3/6K1Lr2ttsO0sUugsWVUV+c4dZyQaQr4pvhW8j6KiG+lxd4uyG8iP74VI1SvcxhZ7TXThDcEaKA8nCql0HZbZT+0G87DRrUsZA+sPlxRUbMcdjdVxUaUqyoWzA8cCDmVgLOiBr0B6HYnwD54iUZtU5YBZaDNzW8B8kCbj17OtyJusU661PQUZlFoIeiXd5S2fIcVFqd9J6K4RrAdHrgBj0Tnd9Z7j+rWxpk1XSimHoJpT9/nCUvZ5LVWJv7c1RoVfw5sowZbQiPqwTNpryCjtanyYeBMktLKnOf6yvoU/qmE6zaD+DMXaUIDTnl/xFfbT+8tWQ6lrI/KXKUs4o5VQwpZzZpuHuMiSzndlxaUjgq5U7HeNiBqsAfU9rvIMmohSs7uYVhb4uCK91ChLfnZ43HnDgWJE8LqKwuxuQ5krbYL+PFkm3+gE72lRKSp5H+h/LT5ZNueGL/51W4KceAl6gy6lTYfG99V4Kvq15vmc7zrW06abrVeVnfGKJrrzhikmUpgqGuzQZpM3DqWP47DfAJgDpTTN/feBQZ1Zq4oeIzUaIkcZL7FXKQfHRgAK1/YcFj8XvgdgCk89CVHzbZg84CtyXWanWODA0/Go11OooSY2sSn6CQ1nU54xUEGlxiAdJYIu1rQ4e0VaP48Ce1UvP8zqnDLGSBigfj3s6io8Wr8ezdUqj2rLDFk2zrKfWXH8ZWHslPo
*/