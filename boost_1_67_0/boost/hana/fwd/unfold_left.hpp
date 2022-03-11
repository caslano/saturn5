/*!
@file
Forward declares `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNFOLD_LEFT_HPP
#define BOOST_HANA_FWD_UNFOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Dual operation to `fold_left` for sequences.
    //! @ingroup group-Sequence
    //!
    //! While `fold_left` reduces a structure to a summary value from the left,
    //! `unfold_left` builds a sequence from a seed value and a function,
    //! starting from the left.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S`, an initial value `state` of tag `I`, an
    //! arbitrary Product `P` and a function \f$ f : I \to P(I, T) \f$,
    //! `unfold_left<S>` has the following signature:
    //! \f[
    //!     \mathtt{unfold\_left}_S : I \times (I \to P(I, T)) \to S(T)
    //! \f]
    //!
    //! @tparam S
    //! The tag of the sequence to build up.
    //!
    //! @param state
    //! An initial value to build the sequence from.
    //!
    //! @param f
    //! A function called as `f(state)`, where `state` is an initial value,
    //! and returning
    //! 1. `nothing` if it is done producing the sequence.
    //! 2. otherwise, `just(make<P>(state, x))`, where `state` is the new
    //!    initial value used in the next call to `f`, `x` is an element to
    //!    be appended to the resulting sequence, and `P` is an arbitrary
    //!    `Product`.
    //!
    //!
    //! Fun fact
    //! ---------
    //! In some cases, `unfold_left` can undo a `fold_left` operation:
    //! @code
    //!     unfold_left<S>(fold_left(xs, state, f), g) == xs
    //! @endcode
    //!
    //! if the following holds
    //! @code
    //!     g(f(x, y)) == just(make_pair(x, y))
    //!     g(state) == nothing
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/unfold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto unfold_left = [](auto&& state, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unfold_left_impl : unfold_left_impl<S, when<true>> { };

    template <typename S>
    struct unfold_left_t;

    template <typename S>
    constexpr unfold_left_t<S> unfold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNFOLD_LEFT_HPP

/* unfold_left.hpp
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
*/