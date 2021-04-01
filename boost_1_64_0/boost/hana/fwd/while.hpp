/*!
@file
Forward declares `boost::hana::while_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_WHILE_HPP
#define BOOST_HANA_FWD_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function to an initial state while some predicate is satisfied.
    //! @ingroup group-Logical
    //!
    //! This method is a natural extension of the `while` language construct
    //! to manipulate a state whose type may change from one iteration to
    //! another. However, note that having a state whose type changes from
    //! one iteration to the other is only possible as long as the predicate
    //! returns a `Logical` whose truth value is known at compile-time.
    //!
    //! Specifically, `while_(pred, state, f)` is equivalent to
    //! @code
    //!     f(...f(f(state)))
    //! @endcode
    //! where `f` is iterated as long as `pred(f(...))` is a true-valued
    //! `Logical`.
    //!
    //!
    //! @param pred
    //! A predicate called on the state or on the result of applying `f` a
    //! certain number of times to the state, and returning whether `f`
    //! should be applied one more time.
    //!
    //! @param state
    //! The initial state on which `f` is applied.
    //!
    //! @param f
    //! A function that is iterated on the initial state. Note that the
    //! return type of `f` may change from one iteration to the other,
    //! but only while `pred` returns a compile-time `Logical`. In other
    //! words, `decltype(f(stateN))` may differ from `decltype(f(stateN+1))`,
    //! but only if `pred(f(stateN))` returns a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto while_ = [](auto&& pred, auto&& state, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct while_impl : while_impl<L, when<true>> { };

    struct while_t {
        template <typename Pred, typename State, typename F>
        constexpr decltype(auto) operator()(Pred&& pred, State&& state, F&& f) const;
    };

    constexpr while_t while_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_WHILE_HPP

/* while.hpp
rEq3tsYunzrXfX970PTO1hMIuDsVW/drBuDbc7IUXIr+dpOQzWRn1Gon5AavgBanZ1HzFzuTnYjKzhcYh+tMSY1wy1yrXffJ7rkdM4eWoW5YdJOoRTrgfzVK1FpIQV3ANfYCAKq5NPLQbUcQrCAQnp+g+ErhJp3xKy4mFyIHSieg0rEbTp6YUVOiNKYfR644/gLtMmKDVtfjx/ELCJU4cyjQR8QKPuXC69l7F5M5ee/lpGeulBwnxLklJXbzTCaNF+pSLEvxHkc0tBHMmubK2OayKcrYL/emdQtz98rsFN4vf0MOfvDl+HRGDYe2y1CtpetCdjqM2RqtWDyE5S9wp4NHx/wpYun6WptAZfqLVu6XNeMWlwe3Dq8NR1gZswstAXI0EtFDHo1KWvguI89ZUZgmiaY2Oru3sTi6+8n8qRwTpTGoOYA883mHfu2di9cIrF+x5GN69bpVQz4D7RXyk4zbi1/DxYzhRQzAzOBHgIi5Z6dDxhZYaBahvd5EiQNaJIPr+nd5/zY5HIEy7ztwVQM3w9OIWsX5SVDpudIfrU3akD9FQoKzSfxlaQ==
*/