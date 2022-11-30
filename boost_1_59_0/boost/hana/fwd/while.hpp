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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr while_t while_{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_WHILE_HPP

/* while.hpp
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
*/