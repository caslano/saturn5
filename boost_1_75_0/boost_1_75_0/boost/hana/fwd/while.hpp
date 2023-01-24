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
AAn3c3OWJht+ACKgym0+wc2X9aY3YrWVzHatlO+avCsTXnFyuSKXg7tO5CzxTNc68VXyU2zQDg+TqACcq8vcn88p88Zf/gAWrhhgOMT/2wUsidSGKCNMm1cf/F2hR/IyISjXSZauvXXpytEwhQ86mNcBwolEU922/IS9yKn1BiEi90a+FxMi06RfPc1PQxrmK62d6JhUnkA4nFkuMGKxbL4ZEzHhkaJQlnCnGNSEsnwcuZB7Meun8NKVYhvD3cLEM2jk//dR9dJP5YKIOYp0ulxz9Jc0DCatNPZh/vxEMuB1Tpf8Mdpg6zaItmkHM/SM5Rrj6HL7d/LT0ydw2SnWlZbpuXKeyDhw6d8Wu8M7f7Ub2ZwDqaGiE44uL2Gd2lvVzFzL7Q5Bg6ta2+DayNY29KRlQYXYU3BPpF3wNeRVlIci9P1ZhIYyzKPn7YHQyHZBs4ZBJoOE69HBdLtYLvc53vbE6lt6BPLbtybx/mKX09evEWX856ePZ6/O/vLpYVJTB+27PUpqatPJ5J9mEaZnaCsUOG+weZiTshCZyaJKdvxjlScRcU2xzp/keQJP17/OyGMfyHvSeRWNbo6/oWlWMrXB6NNQCfdE1zrjeRfw68oNNPBkisyjCC2x7p3k7ppAQdEYbblNNqcjy3p6J2Ub8lzMszCh9lO+lm1OziSlZvxjpwza58TuNKFHXLUvjeqE7V3VEdw946dz08sr
*/