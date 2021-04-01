/*!
@file
Forward declares `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INDEX_IF_HPP
#define BOOST_HANA_FWD_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` structure `xs` and a predicate `pred`,
    //! `index_if(xs, pred)` returns a `hana::optional` containing an `IntegralConstant`
    //! of the index of the first element that satisfies the predicate or nothing
    //! if no element satisfies the predicate.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! `Iterable` structure and returning whether `x` is the element being
    //! searched for. In the current version of the library, the predicate
    //! has to return an `IntegralConstant` holding a value that can be
    //! converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/index_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto index_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct index_if_impl : index_if_impl<S, when<true>> { };

    struct index_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr index_if_t index_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INDEX_IF_HPP


/* index_if.hpp
4uwsF/acoTPJXJ6ooZ8DhVmq8T1vFgqNYgwdg282W04QqaHp44gyGyM6LqLpjF1NXhgZnKWmk0OuFOl+F7WV5ko5Jd+vpgZMUGdJCjZHWULXBbNq2Ht/K8s0+V6FTN8HpyvvQhWVWKYgSmtlDC1X6DDK+1Ha4QAQV84ZLQrRsyrs/UbFz3/hCc1JrgF1o4WoFe3n+ro2W9u20jIwmBYiRcPid6+cxUwIPOCv4si1K/nR3zKAixw7MDXvF2qber5k8q+MQ9wmCxWq+nwQs0U33XHE5OagvwdS7eyylpmViC6AfLBIbJQ22x2j6QkHv0SrdYRZxG6rjUgg9qSRg+l+xrm3On4G5fmHekPTJpZXexh3FYhKUhrT63ni/sYqqTDlA3FjEGE57/RBz4BYZF3BLMzlXH2R3L1LC8wecSaRsLz8hAh/3GGjB7pr8L0s4222KbW+4si8Wgfnutx1BlBhiwp3orI2RKepJ2UeFK6MMYhw99O8l0v4H2nlbqbMpl2gtZZIKcoA9drUeq9TrZNHM1ixPZO0eXQJZpcGGNmjQbcIknuqHe7E0t5N7g==
*/