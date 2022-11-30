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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr unfold_left_t<S> unfold_left{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_UNFOLD_LEFT_HPP

/* unfold_left.hpp
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
*/